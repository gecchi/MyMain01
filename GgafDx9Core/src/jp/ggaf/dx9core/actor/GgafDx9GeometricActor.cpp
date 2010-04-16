#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9GeometricActor::GgafDx9GeometricActor(const char* prm_name,
                                             GgafDx9Checker* prm_pChecker) : GgafDx9BaseActor(prm_name) {
    _class_name = "GgafDx9GeometricActor";
    _isTransformed = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _x = _y = _z = 0.0f;

    _fBoundingSphereRadius = 0;
    _pChecker = prm_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);

    _offscreenkind = -1;
    _pFunc_calcWorldMatrix = NULL;
    _pActor_Base = NULL;


    _X_local  = 0;
    _Y_local  = 0;
    _Z_local  = 0;
    _RX_local = 0;
    _RY_local = 0;
    _RZ_local = 0;
    _X_final  = 0;
    _Y_final  = 0;
    _Z_final  = 0;
    _RX_final = 0;
    _RY_final = 0;
    _RZ_final = 0;


    _X_offset  = 0;
    _Y_offset  = 0;
    _Z_offset  = 0;
    _RX_offset = 0;
    _RY_offset = 0;
    _RZ_offset = 0;
    _is_local = false;
    _wasCalc_matInvWorldRotMv = false;

    _papSeCon = NEW GgafDx9SeConnection*[MAX_SE_PER_ACTOR];
    for (int i = 0; i < MAX_SE_PER_ACTOR; i++) {
        _papSeCon[i] = NULL;
    }
}


void GgafDx9GeometricActor::processPreJudgement() {
    _wasCalc_matInvWorldRotMv = false;

    if (_pActor_Base) {
        //土台あり時ローカル座標に一旦戻す
        chengeGeoLocal();
    }

    //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    //World変換行列（_matWorld）を更新
    if (_pFunc_calcWorldMatrix) {
        (*_pFunc_calcWorldMatrix)(this, _matWorldRotMv);
        //スケールを考慮
        if (_SX != LEN_UNIT || _SY != LEN_UNIT || _SZ != LEN_UNIT) {
           static float fRateScale = 1.0f * LEN_UNIT;
           float Sx = _SX / fRateScale;
           float Sy = _SY / fRateScale;
           float Sz = _SZ / fRateScale;

           _matWorld._11 = Sx * _matWorldRotMv._11;
           _matWorld._12 = Sx * _matWorldRotMv._12;
           _matWorld._13 = Sx * _matWorldRotMv._13;
           _matWorld._14 = _matWorldRotMv._14;

           _matWorld._21 = Sy * _matWorldRotMv._21;
           _matWorld._22 = Sy * _matWorldRotMv._22;
           _matWorld._23 = Sy * _matWorldRotMv._23;
           _matWorld._24 = _matWorldRotMv._24;

           _matWorld._31 = Sz * _matWorldRotMv._31;
           _matWorld._32 = Sz * _matWorldRotMv._32;
           _matWorld._33 = Sz * _matWorldRotMv._33;
           _matWorld._34 = _matWorldRotMv._34;

           _matWorld._41 = _matWorldRotMv._41;
           _matWorld._42 = _matWorldRotMv._42;
           _matWorld._43 = _matWorldRotMv._43;
           _matWorld._44 = _matWorldRotMv._44;
        } else {
           _matWorld = _matWorldRotMv;
        }
    }


    if (_pActor_Base) {
        //絶対座標に変換
        D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Base->_matWorldRotMv)); //合成
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_Base->_matWorldRotMv)); //合成
        chengeGeoFinal();
        //ワールド変換行列から飛行移動を取り出し最終的な座標とする
        _X = _matWorld._41*PX_UNIT*LEN_UNIT;
        _Y = _matWorld._42*PX_UNIT*LEN_UNIT;
        _Z = _matWorld._43*PX_UNIT*LEN_UNIT;
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;

    }

    //８分岐
    if (_pChecker) {
        _pChecker->updateHitArea();
    }

    //メンバー更新
    if (_isTransformed == false) {
        //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
//        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
//        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
//        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
        //視錐台
        _fDist_VpPlnTop    = GgafDx9Universe::_pCamera->_plnTop.a*_fX +
                             GgafDx9Universe::_pCamera->_plnTop.b*_fY +
                             GgafDx9Universe::_pCamera->_plnTop.c*_fZ +
                             GgafDx9Universe::_pCamera->_plnTop.d;

        _fDist_VpPlnBottom = GgafDx9Universe::_pCamera->_plnBottom.a*_fX +
                             GgafDx9Universe::_pCamera->_plnBottom.b*_fY +
                             GgafDx9Universe::_pCamera->_plnBottom.c*_fZ +
                             GgafDx9Universe::_pCamera->_plnBottom.d;

        _fDist_VpPlnLeft   = GgafDx9Universe::_pCamera->_plnLeft.a*_fX +
                             GgafDx9Universe::_pCamera->_plnLeft.b*_fY +
                             GgafDx9Universe::_pCamera->_plnLeft.c*_fZ +
                             GgafDx9Universe::_pCamera->_plnLeft.d;

        _fDist_VpPlnRight  = GgafDx9Universe::_pCamera->_plnRight.a*_fX +
                             GgafDx9Universe::_pCamera->_plnRight.b*_fY +
                             GgafDx9Universe::_pCamera->_plnRight.c*_fZ +
                             GgafDx9Universe::_pCamera->_plnRight.d;

        _fDist_VpPlnFront  = GgafDx9Universe::_pCamera->_plnFront.a*_fX +
                             GgafDx9Universe::_pCamera->_plnFront.b*_fY +
                             GgafDx9Universe::_pCamera->_plnFront.c*_fZ +
                             GgafDx9Universe::_pCamera->_plnFront.d;

        _fDist_VpPlnBack   = GgafDx9Universe::_pCamera->_plnBack.a*_fX +
                             GgafDx9Universe::_pCamera->_plnBack.b*_fY +
                             GgafDx9Universe::_pCamera->_plnBack.c*_fZ +
                             GgafDx9Universe::_pCamera->_plnBack.d;
        _offscreenkind = -1;
    }

}


GgafGroupActor* GgafDx9GeometricActor::addSubBone(actorkind prm_kind,
                                                  GgafDx9GeometricActor* prm_pGeoActor,
                                                  int prm_X_init_local,
                                                  int prm_Y_init_local,
                                                  int prm_Z_init_local,
                                                  int prm_RX_init_local,
                                                  int prm_RZ_init_local,
                                                  int prm_RY_init_local) {
    GgafGroupActor* pGroupActor = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_Base = this;
    prm_pGeoActor->chengeGeoLocal();
    prm_pGeoActor->_X = prm_X_init_local;
    prm_pGeoActor->_Y = prm_Y_init_local;
    prm_pGeoActor->_Z = prm_Z_init_local;
    prm_pGeoActor->_pMover->_angFace[AXIS_X]  = prm_RX_init_local;
    prm_pGeoActor->_pMover->_angFace[AXIS_Z]  = prm_RZ_init_local;
    prm_pGeoActor->_pMover->_angFace[AXIS_Y]  = prm_RY_init_local;
    prm_pGeoActor->_pMover->_angRzMv = prm_RZ_init_local;
    prm_pGeoActor->_pMover->_angRyMv = prm_RY_init_local;
    prm_pGeoActor->_RX = prm_RX_init_local;
    prm_pGeoActor->_RZ = prm_RZ_init_local;
    prm_pGeoActor->_RY = prm_RY_init_local;
    prm_pGeoActor->chengeGeoFinal();
    return pGroupActor;
}
GgafGroupActor* GgafDx9GeometricActor::addSubBone(GgafDx9GeometricActor* prm_pGeoActor,
                                                  int prm_X_init_local,
                                                  int prm_Y_init_local,
                                                  int prm_Z_init_local,
                                                  int prm_RX_init_local,
                                                  int prm_RZ_init_local,
                                                  int prm_RY_init_local) {
    return addSubBone(prm_pGeoActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND),
                      prm_pGeoActor,
                      prm_X_init_local,
                      prm_Y_init_local,
                      prm_Z_init_local,
                      prm_RX_init_local,
                      prm_RZ_init_local,
                      prm_RY_init_local);
}

bool GgafDx9GeometricActor::processHitChkLogic(GgafActor* prm_pOtherActor) {
    if (_pChecker == NULL || _actor_class != MAINACTOR) {
        return false;
    } else {
//        GgafDx9GeometricActor* pOtherActor = dynamic_cast<GgafDx9GeometricActor*> (prm_pOtherActor);
//        if (pOtherActor != NULL && pOtherActor->_pChecker != NULL) {
//            return _pChecker->isHit(pOtherActor->_pChecker);
//        } else {
//            _TRACE_("GgafDx9GeometricActor::processHitChkLogic prm_pOtherActor("<<(prm_pOtherActor->getName())<<") is not GgafDx9GeometricActor")
//            return false;
//        }

        //本来は↑のようにdynamic_castするのが汎用的かつ安全。しかし、速度UPのため（dynamic_castを省きたいがため）に、
        //GgafDx9GeometricActorに決め打ちキャストしています。危険です。
        //座標を持たないアクターの_can_hit_flg を忘れずにfalseにすることによって、ここの引数にGgafDx9GeometricActorに
        //キャストできないポインタは来ないハズである。
        //もし、万が一来たら・・・たぶん落ちる。その時にまた考える。
        //TODO:考える。
        return _pChecker->isHit(((GgafDx9GeometricActor*)prm_pOtherActor)->_pChecker);
    }
}


int GgafDx9GeometricActor::isOffscreen() {
    //_TRACE_("name="<<getName()<<" _fBoundingSphereRadius="<<_fBoundingSphereRadius);
    if (_offscreenkind == -1) {
        if (_fDist_VpPlnTop <= _fBoundingSphereRadius) {
            if (_fDist_VpPlnBottom <= _fBoundingSphereRadius) {
                if (_fDist_VpPlnLeft <= _fBoundingSphereRadius) {
                    if (_fDist_VpPlnRight <= _fBoundingSphereRadius) {
                        if (_fDist_VpPlnFront <= _fBoundingSphereRadius) {
                            if (_fDist_VpPlnBack <= _fBoundingSphereRadius) {
                                //Viewport範囲内
                                _offscreenkind = 0;
                            } else {
                                //奥平面より奥で範囲外
                                _offscreenkind = 6;
                            }
                        } else {
                            //手前平面より手前で範囲外
                            _offscreenkind = 5;
                        }
                    } else {
                        //右平面より右で範囲外
                        _offscreenkind = 4;
                    }
                } else {
                    //左平面より左で範囲外
                    _offscreenkind = 3;
                }
            } else {
                //下平面より下で範囲外
                _offscreenkind = 2;
            }
        } else {
            //上平面より上で範囲外
            _offscreenkind = 1;
        }
        //return (pCAM->canView(this) > 0);
    }
    return _offscreenkind;
}

bool GgafDx9GeometricActor::isOutOfGameSpace() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        if (_X < GgafDx9Universe::_X_goneRight) {
            if (GgafDx9Universe::_Y_goneBottom < _Y) {
                if (_Y < GgafDx9Universe::_Y_goneTop) {
                    if (GgafDx9Universe::_Z_goneNear < _Z) {
                        if (_Z < GgafDx9Universe::_Z_goneFar) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}


void GgafDx9GeometricActor::prepareSe(int prm_id, const char* prm_se_name, int prm_cannel) {
    if (prm_id < 0 || prm_id >= MAX_SE_PER_ACTOR) {
        throwGgafCriticalException("GgafDx9GeometricActor::prepareSe() IDが範囲外です。0~"<<(MAX_SE_PER_ACTOR-1)<<"でお願いします。prm_id="<<prm_id);
    }
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _papSeCon[prm_id] = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect(idstr);
}

void GgafDx9GeometricActor::playSe(int prm_id) {
    if (prm_id < 0 || prm_id >= MAX_SE_PER_ACTOR) {
        throwGgafCriticalException("GgafDx9GeometricActor::playSe() IDが範囲外です。0~"<<(MAX_SE_PER_ACTOR-1)<<"でお願いします。prm_id="<<prm_id);
    }
    GgafDx9Universe* pUniverse = (GgafDx9Universe*)(GgafGod::_pGod->_pUniverse);
    pUniverse->registSe(_papSeCon[prm_id]->view(), DSBVOLUME_MAX, DSBPAN_CENTER, 0, 1.0);
}
void GgafDx9GeometricActor::playSe3D(int prm_id) {
    if (prm_id < 0 || prm_id >= MAX_SE_PER_ACTOR) {
        throwGgafCriticalException("GgafDx9GeometricActor::playSe3D() IDが範囲外です。0~"<<(MAX_SE_PER_ACTOR-1)<<"でお願いします。prm_id="<<prm_id);
    }
    GgafDx9Universe* pUniverse = (GgafDx9Universe*)(GgafGod::_pGod->_pUniverse);


    //    /** [r]視錐台上面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnTop;
    //    /** [r]視錐台下面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnBottom;
    //    /** [r]視錐台左面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnLeft;
    //    /** [r]視錐台右面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnRight;
    //    /** [r]視錐台手前面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnFront;
    //    /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnBack;
    //#define DSBPAN_LEFT                 -10000
    //#define DSBPAN_CENTER               0
    //#define DSBPAN_RIGHT                10000
    //
    //#define DSBVOLUME_MIN               -10000
    //#define DSBVOLUME_MAX               0
    //    int GgafDx9Sound::_master_volume_rate = 100;
    //    int GgafDx9Sound::_bgm_volume_rate = 100;
    //    int GgafDx9Sound::_se_volume_rate = 100;

    //    /** カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0 */
    //    float _zn;
    //    /** カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn  */
    //    float _zf;

    //    まず、同じバッファの音が同時再生できなかった問題は、DuplicateSoundBuffer()関数を使ってバッファの外枠のみのコピーを作っておくことで解決です。例えば、これで8個作っておくと同じバッファの音が8個まで同時再生できます。
    //    ただ、小さな破片は1秒間に数百個も爆発したりするので、さすがに100個くらい同時再生しようとすると音が途切れます…。
    //
    //    後は、再生直前に
    //
    //        lpDSBuf->SetVolume(LONG); //音量設定 減衰するdb 0～-10000
    //        lpDSBuf->SetPan(LONG); //パン設定 -10000～+10000
    //        lpDSBuf->SetFrequency(DWORD); //再生周波数設定
    //
    //    _dwDefaultFrequency
    //    こういう設定が出来ることが分かりました。最後の再生周波数設定は、例えばサンプリングレート44.1KHzのバッファの場合はここへ44100を指定すると通常通りの再生になり、22050を指定すると半分の速度（音程も半分）で再生されるという具合です。
    //    これ、敵の爆破した位置に合わせて設定してやるとすごく立体的でリアル。とくに、遠くの爆発は再生周波数下げるようにすると、爆発音がくぐもった音になってまるで映画みたい。最初は遊び心でいじってたけど、ここまで上手くハマるとは思わなかったな。
    //
    //    ただ、注意点もあって、バッファ初期化時にDSBUFFERDESC構造体の設定で、
    //
    //        DSBufferDesc.dwFlags = DSBCAPS_LOCDEFER | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
    //
    //    のようなフラグを設定して、各パラメータをコントロールすることを伝えておく必要がある。MSDN見ても、SetVolume()の解説のところなんかにこのフラグの事が書いて無くて、しばらくネットを探し回ってしまった。あと、SetVolumeの値もMSDNだと正の値だと書いてあるけど、実際は負の値を入れないといけない。MSDNってどっか抜けてる…？？
    static const int VOLUME_MAX_3D = DSBVOLUME_MAX;
    static const int VOLUME_MIN_3D = DSBVOLUME_MIN + ((DSBVOLUME_MAX - DSBVOLUME_MIN)*0.7);
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;

    //距離計算
    //遅延なし、音量100％の場所をpCAMの場所とする
    //自身とpCAMの距離
    int DX = (pCAM->_X - _X) / LEN_UNIT;
    int DY = (pCAM->_Y - _Y) / LEN_UNIT;
    int DZ = (pCAM->_Z - _Z) / LEN_UNIT;
    double d = GgafUtil::sqrt_fast(double(DX*DX + DY*DY + DZ*DZ));
    LONG vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCAM->_zf*PX_UNIT))) * VOLUME_RANGE_3D);

    int delay = (d / (pCAM->_zf*PX_UNIT))*GGAF_SAYONARA_DELAY-10; //10フレーム底上げ
//    _TRACE_(getName()<<" : d = "<< d <<", (pCAM->_zf*PX_UNIT)="<<(pCAM->_zf*PX_UNIT));
//    _TRACE_(getName()<<" : (d / (pCAM->_zf*PX_UNIT)) = "<< (d / (pCAM->_zf*PX_UNIT)) <<", delay="<<delay);
//    _TRACE_(getName()<<" : d = "<< d <<", vol="<<vol);
//    _TRACE_(getName()<<" : DX = "<< DX <<", DY="<<DY<<", DZ="<<DZ);
//    _TRACE_(getName()<<" : pCAM->_zf = "<< pCAM->_zf <<", (1.0 - (d / pCAM->_zf))="<<(1.0 - (d / pCAM->_zf)));
//    _TRACE_(getName()<<"(DSBVOLUME_MAX - DSBVOLUME_MIN)="<<(DSBVOLUME_MAX - DSBVOLUME_MIN));


    float fDist_VpVerticalCenter  =
         GgafDx9Universe::_pCamera->_plnVerticalCenter.a*_fX +
         GgafDx9Universe::_pCamera->_plnVerticalCenter.b*_fY +
         GgafDx9Universe::_pCamera->_plnVerticalCenter.c*_fZ +
         GgafDx9Universe::_pCamera->_plnVerticalCenter.d;

    angle ang = GgafDx9Util::getAngle2D(fDist_VpVerticalCenter, -_fDist_VpPlnFront );

    LONG pan = GgafDx9Util::COS[ang/ANGLE_RATE] * DSBPAN_RIGHT;
//    _TRACE_(getName()<<" : ang = "<< ang <<", pan="<<pan);
    if (VOLUME_MAX_3D < vol) {
        vol = VOLUME_MAX_3D;
    } else if (VOLUME_MIN_3D > vol) {
        vol = VOLUME_MIN_3D;
    }
    if (delay < 0) {
        delay = 0;
    } else if (delay > GGAF_SAYONARA_DELAY) {
        delay = GGAF_SAYONARA_DELAY;
    }
//    _TRACE_("delay="<<delay);
    pUniverse->registSe(_papSeCon[prm_id]->view(), vol, pan, delay, 1.0); // + (GgafDx9Se::VOLUME_RANGE / 6) は音量底上げ
    //真ん中からの距離
   //                float dPlnLeft = abs(_fDist_VpPlnLeft);
   //                float dPlnRight = abs(_fDist_VpPlnRight);
   //                if (dPlnLeft < dPlnRight) {
   //                    //sinθ = dPlnLeft/d;
   //                    //θ = asin(dPlnLeft/d)
   //                    //X = (_rad_half_fovY - θ)
   //                    //tan X = 距離 / d
   //                    //d * tan X = 距離
   //                    //d * tan (_rad_half_fovY - θ) = 距離
   //                    //d * tan (_rad_half_fovY - asin(dPlnLeft/d)) = 距離
   //                    //本当にこうしなければいけない？



   // _papSe[prm_id]->play();
}

GgafDx9GeometricActor::~GgafDx9GeometricActor() {
    DELETE_IMPOSSIBLE_NULL(_pMover);
    for (int i = 0; i < MAX_SE_PER_ACTOR; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSeCon);
}


void GgafDx9GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_frame_of_behaving<<","<<_can_hit_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_flg<<"("<<_frame_of_life_when_activation<<")");

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
            if (pActor_tmp->getNext() != NULL) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLってます");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_("\t\t\t\t\t\t\t\t└─");
                break;
            }
        }
    }
}

void GgafDx9GeometricActor::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_frame_of_behaving<<","<<_can_hit_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_flg<<"("<<_frame_of_life_when_activation<<")");
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "｜");
            if (pActor_tmp->getNext() != NULL) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLってます");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_(prm_parent+"└─");
                break;
            }
        }
    }
}

