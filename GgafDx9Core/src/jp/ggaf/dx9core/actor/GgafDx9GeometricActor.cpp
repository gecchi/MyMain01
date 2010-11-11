#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9GeometricActor::GgafDx9GeometricActor(const char* prm_name,
                                             GgafDx9Checker* prm_pChecker) : GgafDx9BaseActor(prm_name) {
    _obj_class |= Obj_GgafDx9GeometricActor;
    _class_name = "GgafDx9GeometricActor";
    _isTransformed = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _x = _y = _z = 0.0f;

    _fBoundingSphereRadius = 0;
    _fRate_BoundingSphereRadius = 1.0f;
    _pChecker = prm_pChecker;
    _pMover = NEW GgafDx9GeometricMover(this);
    _pSeTransmitter = NEW GgafDx9SeTransmitter(this);

    _offscreenkind = -1;
    _pFunc_calcRotMvWorldMatrix = NULL;
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

}


void GgafDx9GeometricActor::processSettlementBehavior() {
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
    if (_pFunc_calcRotMvWorldMatrix) {
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
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

        //TODO:絶対座標の_RX, _RY, _RZ に変換は保留

    }

    //８分木登録
    if (_pChecker) {
        _pChecker->updateHitArea();
    }

    //メンバー更新
    if (_isTransformed == false) {
        GgafDx9Camera* pCam = P_CAM;
        //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
//        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
//        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
//        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
        //視錐台
        _fDist_VpPlnTop    = pCam->_plnTop.a*_fX +
                             pCam->_plnTop.b*_fY +
                             pCam->_plnTop.c*_fZ +
                             pCam->_plnTop.d;

        _fDist_VpPlnBottom = pCam->_plnBottom.a*_fX +
                             pCam->_plnBottom.b*_fY +
                             pCam->_plnBottom.c*_fZ +
                             pCam->_plnBottom.d;

        _fDist_VpPlnLeft   = pCam->_plnLeft.a*_fX +
                             pCam->_plnLeft.b*_fY +
                             pCam->_plnLeft.c*_fZ +
                             pCam->_plnLeft.d;

        _fDist_VpPlnRight  = pCam->_plnRight.a*_fX +
                             pCam->_plnRight.b*_fY +
                             pCam->_plnRight.c*_fZ +
                             pCam->_plnRight.d;

        _fDist_VpPlnFront  = pCam->_plnFront.a*_fX +
                             pCam->_plnFront.b*_fY +
                             pCam->_plnFront.c*_fZ +
                             pCam->_plnFront.d;

        _fDist_VpPlnBack   = pCam->_plnBack.a*_fX +
                             pCam->_plnBack.b*_fY +
                             pCam->_plnBack.c*_fZ +
                             pCam->_plnBack.d;
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
    if (_obj_class & Obj_GgafDx9GeometricActor) {
        if (_pChecker) {
            return _pChecker->isHit(((GgafDx9GeometricActor*)prm_pOtherActor)->_pChecker);
        }
    }
    return false;

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
}


int GgafDx9GeometricActor::isOutOfView() {
    //_TRACE_("name="<<getName()<<" _fBoundingSphereRadius="<<_fBoundingSphereRadius);
    float bound = _fBoundingSphereRadius * _fRate_BoundingSphereRadius;
    if (_offscreenkind == -1) {
        if (_fDist_VpPlnTop <= bound) {
            if (_fDist_VpPlnBottom <= bound) {
                if (_fDist_VpPlnLeft <= bound) {
                    if (_fDist_VpPlnRight <= bound) {
                        if (_fDist_VpPlnFront <= bound) {
                            if (_fDist_VpPlnBack <= bound) {
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
    }
    return _offscreenkind;
}

bool GgafDx9GeometricActor::isOutOfUniverse() {
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

GgafDx9GeometricActor::~GgafDx9GeometricActor() {
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pSeTransmitter);
}


void GgafDx9GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_frame_of_behaving_since_onActive<<
                                                                                                          "/"<<
                                                                                                          _frame_of_behaving<<
                                                                                                          "/"<<
                                                                                                          _frame_of_life<<
                                                                                                          ","<<
                                                                                                          _was_initialize_flg<<
                                                                                                          ","<<
                                                                                                          _can_live_flg<<
                                                                                                          _is_active_flg<<
                                                                                                          ","<<
                                                                                                          _will_activate_after_flg<<
                                                                                                          "("<<_frame_of_life_when_activation<<")"<<
                                                                                                          _on_change_to_active_flg<<
                                                                                                          ","<<
                                                                                                          _will_inactivate_after_flg<<
                                                                                                          "("<<_frame_of_life_when_inactivation<<")"<<
                                                                                                          _on_change_to_inactive_flg<<
                                                                                                          ","<<
                                                                                                          _will_end_after_flg<<
                                                                                                          "("<<_frame_of_life_when_end<<")"<<
                                                                                                          ","<<
                                                                                                          _progress<<
                                                                                                          "("<<_progress_nextframe<<")"<<
                                                                                                          ","<<
                                                                                                          _was_paused_flg<<
                                                                                                          _was_paused_flg_in_next_frame<<
                                                                                                          _will_mv_first_in_next_frame_flg<<
                                                                                                          _will_mv_last_in_next_frame_flg
                                                                                                          );

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
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_frame_of_behaving_since_onActive<<
                                                                                                     "/"<<
                                                                                                     _frame_of_behaving<<
                                                                                                     "/"<<
                                                                                                     _frame_of_life<<
                                                                                                     ","<<
                                                                                                     _was_initialize_flg<<
                                                                                                     ","<<
                                                                                                     _can_live_flg<<
                                                                                                     _is_active_flg<<
                                                                                                     ","<<
                                                                                                     _will_activate_after_flg<<
                                                                                                     "("<<_frame_of_life_when_activation<<")"<<
                                                                                                     _on_change_to_active_flg<<
                                                                                                     ","<<
                                                                                                     _will_inactivate_after_flg<<
                                                                                                     "("<<_frame_of_life_when_inactivation<<")"<<
                                                                                                     _on_change_to_inactive_flg<<
                                                                                                     ","<<
                                                                                                     _will_end_after_flg<<
                                                                                                     "("<<_frame_of_life_when_end<<")"<<
                                                                                                     ","<<
                                                                                                     _progress<<
                                                                                                     "("<<_progress_nextframe<<")"<<
                                                                                                     ","<<
                                                                                                     _was_paused_flg<<
                                                                                                     _was_paused_flg_in_next_frame<<
                                                                                                     _will_mv_first_in_next_frame_flg<<
                                                                                                     _will_mv_last_in_next_frame_flg
                                                                                                     );
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

