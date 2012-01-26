#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxGeometricActor::GgafDxGeometricActor(const char* prm_name,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) : GgafDxBaseActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafDxGeometricActor;
    _class_name = "GgafDxGeometricActor";
    _is2DActor = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _radius_bounding_sphere = 0;
    _rate_BoundingSphereRadius = 1.0f;
    _pChecker = prm_pChecker;
    _pKurokoA = NEW GgafDxKurokoA(this);
    _pKurokoB = NEW GgafDxKurokoB(this);
    _pSeTransmitter = NEW GgafDxSeTransmitter(this);
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
    _pFormation = NULL;

//    _X_offset  = 0;
//    _Y_offset  = 0;
//    _Z_offset  = 0;
//    _RX_offset = 0;
//    _RY_offset = 0;
//    _RZ_offset = 0;
    _is_local = false;
    _wasCalc_matInvWorldRotMv = false;
}


void GgafDxGeometricActor::processSettlementBehavior() {
    if (_is2DActor) {
        return;
    }

    _wasCalc_matInvWorldRotMv = false;

    if (_pActor_Base) {
        //土台あり時ローカル座標に一旦戻す
        changeGeoLocal();
    }

    //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
    _fX = CO2DX(_X);
    _fY = CO2DX(_Y);
    _fZ = CO2DX(_Z);
    //World変換行列（_matWorld）を更新
    if (_pFunc_calcRotMvWorldMatrix) {
        //回転×移動のみ計算し _matWorldRotMv に保持
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
        //スケールを考慮して、最終的な _matWorld を保持
        if (_SX != LEN_UNIT) {
            float Sx = SC2R(_SX);
            _matWorld._11 = Sx * _matWorldRotMv._11;
            _matWorld._12 = Sx * _matWorldRotMv._12;
            _matWorld._13 = Sx * _matWorldRotMv._13;
        } else {
            _matWorld._11 = _matWorldRotMv._11;
            _matWorld._12 = _matWorldRotMv._12;
            _matWorld._13 = _matWorldRotMv._13;
        }
        _matWorld._14 = _matWorldRotMv._14;

        if (_SY != LEN_UNIT) {
            float Sy = SC2R(_SY);
            _matWorld._21 = Sy * _matWorldRotMv._21;
            _matWorld._22 = Sy * _matWorldRotMv._22;
            _matWorld._23 = Sy * _matWorldRotMv._23;
        } else {
            _matWorld._21 = _matWorldRotMv._21;
            _matWorld._22 = _matWorldRotMv._22;
            _matWorld._23 = _matWorldRotMv._23;
        }
        _matWorld._24 = _matWorldRotMv._24;

        if (_SZ != LEN_UNIT) {
            float Sz = SC2R(_SZ);
            _matWorld._31 = Sz * _matWorldRotMv._31;
            _matWorld._32 = Sz * _matWorldRotMv._32;
            _matWorld._33 = Sz * _matWorldRotMv._33;
        } else {
            _matWorld._31 = _matWorldRotMv._31;
            _matWorld._32 = _matWorldRotMv._32;
            _matWorld._33 = _matWorldRotMv._33;
        }
        _matWorld._34 = _matWorldRotMv._34;

        _matWorld._41 = _matWorldRotMv._41;
        _matWorld._42 = _matWorldRotMv._42;
        _matWorld._43 = _matWorldRotMv._43;
        _matWorld._44 = _matWorldRotMv._44;
    }

    if (_pActor_Base) {
        //絶対座標に変換
        D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Base->_matWorldRotMv)); //合成
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_Base->_matWorldRotMv)); //合成
        changeGeoFinal();
        //ワールド変換行列から飛行移動を取り出し最終的な座標とする
        _X = DX2CO(_matWorld._41);
        _Y = DX2CO(_matWorld._42);
        _Z = DX2CO(_matWorld._43);
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;

        //TODO:絶対座標の_RX, _RY, _RZ に変換は保留

    }


    //８分木登録
    if (_pChecker) {
        _pChecker->_blown_sgn_vX = 0;
        _pChecker->_blown_sgn_vY = 0;
        _pChecker->_blown_sgn_vZ = 0;
        if (_can_hit_out_of_view == false && isOutOfView()) {
            //視野外当たり判定無効の場合は登録しない
        } else if (_can_hit_flg) {
            _pChecker->updateHitArea();
        }
    }
//    if (_is2DActor == false) {
        //メンバー更新
        GgafDxCamera* pCam = P_CAM;
        //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
    //        _fX = CO2DX(_X);
    //        _fY = CO2DX(_Y);
    //        _fZ = CO2DX(_Z);
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
//    }

}


GgafGroupHead* GgafDxGeometricActor::addSubBone(actorkind prm_kind,
                                                GgafDxGeometricActor* prm_pGeoActor,
                                                coord prm_X_init_local,
                                                coord prm_Y_init_local,
                                                coord prm_Z_init_local,
                                                coord prm_RX_init_local,
                                                coord prm_RZ_init_local,
                                                coord prm_RY_init_local) {
    GgafGroupHead* pGroupHead = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_Base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_X = prm_X_init_local;
    prm_pGeoActor->_Y = prm_Y_init_local;
    prm_pGeoActor->_Z = prm_Z_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_X]  = prm_RX_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Z]  = prm_RZ_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Y]  = prm_RY_init_local;
    prm_pGeoActor->_pKurokoA->_angRzMv = prm_RZ_init_local;
    prm_pGeoActor->_pKurokoA->_angRyMv = prm_RY_init_local;
    prm_pGeoActor->_RX = prm_RX_init_local;
    prm_pGeoActor->_RZ = prm_RZ_init_local;
    prm_pGeoActor->_RY = prm_RY_init_local;
    prm_pGeoActor->changeGeoFinal();
    return pGroupHead;
}
GgafGroupHead* GgafDxGeometricActor::addSubBone(GgafDxGeometricActor* prm_pGeoActor,
                                                  coord prm_X_init_local,
                                                  coord prm_Y_init_local,
                                                  coord prm_Z_init_local,
                                                  coord prm_RX_init_local,
                                                  coord prm_RZ_init_local,
                                                  coord prm_RY_init_local) {
    return addSubBone(prm_pGeoActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND),
                      prm_pGeoActor,
                      prm_X_init_local,
                      prm_Y_init_local,
                      prm_Z_init_local,
                      prm_RX_init_local,
                      prm_RZ_init_local,
                      prm_RY_init_local);
}

bool GgafDxGeometricActor::processHitChkLogic(GgafActor* prm_pOtherActor) {
    if (_obj_class & Obj_GgafDxGeometricActor) {
        if (_pChecker) {
            return _pChecker->isHit(((GgafDxGeometricActor*)prm_pOtherActor)->_pChecker);
        }
    }
    return false;

//        GgafDxGeometricActor* pOtherActor = dynamic_cast<GgafDxGeometricActor*> (prm_pOtherActor);
//        if (pOtherActor != NULL && pOtherActor->_pChecker) {
//            return _pChecker->isHit(pOtherActor->_pChecker);
//        } else {
//            _TRACE_("GgafDxGeometricActor::processHitChkLogic prm_pOtherActor("<<(prm_pOtherActor->getName())<<") is not GgafDxGeometricActor")
//            return false;
//        }
        //本来は↑のようにdynamic_castするのが汎用的かつ安全。しかし、速度UPのため（dynamic_castを省きたいがため）に、
        //GgafDxGeometricActorに決め打ちキャストしています。危険です。
        //座標を持たないアクターの_can_hit_flg を忘れずにfalseにすることによって、ここの引数にGgafDxGeometricActorに
        //キャストできないポインタは来ないハズである。
}


int GgafDxGeometricActor::isOutOfView() {
    //_TRACE_("name="<<getName()<<" _radius_bounding_sphere="<<_radius_bounding_sphere);
    dxcoord bound = _radius_bounding_sphere * _rate_BoundingSphereRadius*1.5;//1.2はやや境界球を大きくして、画面境界のチラツキを抑える
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

bool GgafDxGeometricActor::isOutOfUniverse() {
    if (GgafDxUniverse::_X_goneLeft < _X) {
        if (_X < GgafDxUniverse::_X_goneRight) {
            if (GgafDxUniverse::_Y_goneBottom < _Y) {
                if (_Y < GgafDxUniverse::_Y_goneTop) {
                    if (GgafDxUniverse::_Z_goneNear < _Z) {
                        if (_Z < GgafDxUniverse::_Z_goneFar) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GgafDxGeometricActor::locateAs(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
    _Z = prm_pGeoElem->_Z;
}

void GgafDxGeometricActor::rotateWith(GgafDxGeometricActor* prm_pActor) {
    _RX = prm_pActor->_RX;
    _RY = prm_pActor->_RY;
    _RZ = prm_pActor->_RZ;
}


void GgafDxGeometricActor::onEnded() {
    GgafDxBaseActor::onEnded();
    _pFormation = NULL;
}

GgafDxGeometricActor::~GgafDxGeometricActor() {
    DELETE_IMPOSSIBLE_NULL(_pKurokoA);
    DELETE_IMPOSSIBLE_NULL(_pKurokoB);
    DELETE_IMPOSSIBLE_NULL(_pSeTransmitter);
}


void GgafDxGeometricActor::dump() {
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
                                                                                                          "("<<(_frame_of_life_when_end==MAXDWORD ? 0 : _frame_of_life_when_end)<<")"<<
                                                                                                          ","<<
                                                                                                          _was_paused_flg<<
                                                                                                          _was_paused_flg_in_next_frame<<
                                                                                                          _will_mv_first_in_next_frame_flg<<
                                                                                                          _will_mv_last_in_next_frame_flg
                                                                                                          );

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
            if (pActor_tmp->getNext()) {
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

void GgafDxGeometricActor::dump(string prm_parent) {
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
                                                                                                     "("<<(_frame_of_life_when_end==MAXDWORD ? 0 : _frame_of_life_when_end)<<")"<<
                                                                                                     ","<<
                                                                                                     _was_paused_flg<<
                                                                                                     _was_paused_flg_in_next_frame<<
                                                                                                     _will_mv_first_in_next_frame_flg<<
                                                                                                     _will_mv_last_in_next_frame_flg
                                                                                                     );
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump(prm_parent + "｜");
            if (pActor_tmp->getNext()) {
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

