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
    _pActor_Foundation = NULL;


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
}


void GgafDx9GeometricActor::processPreJudgement() {
    if (_pActor_Foundation) {
        chengeGeoLocal();
    }


    //土台あり
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    //World変換行列（_matWorld）を更新
    if (_pFunc_calcWorldMatrix) {
        (*_pFunc_calcWorldMatrix)(this, _matWorld_RM);
        //スケールを考慮
        if (_SX != LEN_UNIT || _SY != LEN_UNIT || _SZ != LEN_UNIT) {
           static float fRateScale = 1.0f * LEN_UNIT;
           float Sx = _SX / fRateScale;
           float Sy = _SY / fRateScale;
           float Sz = _SZ / fRateScale;

           _matWorld._11 = Sx * _matWorld_RM._11;
           _matWorld._12 = Sx * _matWorld_RM._12;
           _matWorld._13 = Sx * _matWorld_RM._13;
           _matWorld._14 = _matWorld_RM._14;

           _matWorld._21 = Sy * _matWorld_RM._21;
           _matWorld._22 = Sy * _matWorld_RM._22;
           _matWorld._23 = Sy * _matWorld_RM._23;
           _matWorld._24 = _matWorld_RM._24;

           _matWorld._31 = Sz * _matWorld_RM._31;
           _matWorld._32 = Sz * _matWorld_RM._32;
           _matWorld._33 = Sz * _matWorld_RM._33;
           _matWorld._34 = _matWorld_RM._34;

           _matWorld._41 = _matWorld_RM._41;
           _matWorld._42 = _matWorld_RM._42;
           _matWorld._43 = _matWorld_RM._43;
           _matWorld._44 = _matWorld_RM._44;
        } else {
           _matWorld = _matWorld_RM;
        }
    }

    if (_pActor_Foundation) {
        D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Foundation->_matWorld_RM)); //合成
        D3DXMatrixMultiply(&_matWorld_RM, &_matWorld_RM, &(_pActor_Foundation->_matWorld_RM)); //合成
        chengeGeoFinal();
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











//
//
//    if (_isTransformed == false) {
//        //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
//        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
//        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
//        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
//    }
//    //World変換行列（_matWorld）を更新
//    if (_pFunc_calcWorldMatrix) {
//        (*_pFunc_calcWorldMatrix)(this, _matWorld_RM);
//        //スケールを考慮
//        if (_SX != LEN_UNIT || _SY != LEN_UNIT || _SZ != LEN_UNIT) {
//           static float fRateScale = 1.0f * LEN_UNIT;
//           float Sx = _SX / fRateScale;
//           float Sy = _SY / fRateScale;
//           float Sz = _SZ / fRateScale;
//
//           _matWorld._11 = Sx * _matWorld_RM._11;
//           _matWorld._12 = Sx * _matWorld_RM._12;
//           _matWorld._13 = Sx * _matWorld_RM._13;
//           _matWorld._14 = _matWorld_RM._14;
//
//           _matWorld._21 = Sy * _matWorld_RM._21;
//           _matWorld._22 = Sy * _matWorld_RM._22;
//           _matWorld._23 = Sy * _matWorld_RM._23;
//           _matWorld._24 = _matWorld_RM._24;
//
//           _matWorld._31 = Sz * _matWorld_RM._31;
//           _matWorld._32 = Sz * _matWorld_RM._32;
//           _matWorld._33 = Sz * _matWorld_RM._33;
//           _matWorld._34 = _matWorld_RM._34;
//
//           _matWorld._41 = _matWorld_RM._41;
//           _matWorld._42 = _matWorld_RM._42;
//           _matWorld._43 = _matWorld_RM._43;
//           _matWorld._44 = _matWorld_RM._44;
//        } else {
//           _matWorld = _matWorld_RM;
//        }
//        if (_pActor_Foundation) {
//            D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Foundation->_matWorld_RM)); //合成
//            D3DXMatrixMultiply(&_matWorld_RM, &_matWorld_RM, &(_pActor_Foundation->_matWorld_RM)); //合成
//
//            _X_local = _X;
//            _Y_local = _Y;
//            _Z_local = _Z;
////            _X = _matWorld_RM._11*_X_local + _matWorld_RM._21*_Y_local + _matWorld_RM._31*_Z_local;
////            _Y = _matWorld_RM._12*_X_local + _matWorld_RM._22*_Y_local + _matWorld_RM._32*_Z_local;
////            _Z = _matWorld_RM._13*_X_local + _matWorld_RM._23*_Y_local + _matWorld_RM._33*_Z_local;
//            _X = _matWorld._41*PX_UNIT*LEN_UNIT;
//            _Y = _matWorld._42*PX_UNIT*LEN_UNIT;
//            _Z = _matWorld._43*PX_UNIT*LEN_UNIT;
//
//            _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
//            _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
//            _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
//            _X_final = _X;
//            _Y_final = _Y;
//            _Z_final = _Z;
//
//        } else {
//
//
//        }
//    }
//
//
//
//
//
//
//
//



//        if (_pActor_Foundation) {
//            //土台がある場合
//            D3DXMATRIX matRM;
//            (*_pFunc_calcWorldMatrix)(this, matRM);
//            D3DXMatrixMultiply(&_matWorld_RM, &matRM, &(_pActor_Foundation->_matWorld_RM)); //合成
////            _X_local = _X;
////            _Y_local = _Y;
////            _Z_local = _Z;
////
////            _X = _matWorld_RM._11*_X_local + _matWorld_RM._21*_Y_local + _matWorld_RM._31*_Z_local;
////            _Y = _matWorld_RM._12*_X_local + _matWorld_RM._22*_Y_local + _matWorld_RM._32*_Z_local;
////            _Z = _matWorld_RM._13*_X_local + _matWorld_RM._23*_Y_local + _matWorld_RM._33*_Z_local;
//
////            _X = _matWorld_RM._14*PX_UNIT*LEN_UNIT;
////            _Y = _matWorld_RM._24*PX_UNIT*LEN_UNIT;
////            _Z = _matWorld_RM._34*PX_UNIT*LEN_UNIT;
//        } else {
//            //土台が無い場合
//            (*_pFunc_calcWorldMatrix)(this, _matWorld_RM);
//        }
//
//        //スケールを考慮
//        if (_SX != LEN_UNIT || _SY != LEN_UNIT || _SZ != LEN_UNIT) {
//           static float fRateScale = 1.0f * LEN_UNIT;
//           float Sx = _SX / fRateScale;
//           float Sy = _SY / fRateScale;
//           float Sz = _SZ / fRateScale;
//
//           _matWorld._11 = Sx * _matWorld_RM._11;
//           _matWorld._12 = Sx * _matWorld_RM._12;
//           _matWorld._13 = Sx * _matWorld_RM._13;
//           _matWorld._14 = _matWorld_RM._14;
//
//           _matWorld._21 = Sy * _matWorld_RM._21;
//           _matWorld._22 = Sy * _matWorld_RM._22;
//           _matWorld._23 = Sy * _matWorld_RM._23;
//           _matWorld._24 = _matWorld_RM._24;
//
//           _matWorld._31 = Sz * _matWorld_RM._31;
//           _matWorld._32 = Sz * _matWorld_RM._32;
//           _matWorld._33 = Sz * _matWorld_RM._33;
//           _matWorld._34 = _matWorld_RM._34;
//
//           _matWorld._41 = _matWorld_RM._41;
//           _matWorld._42 = _matWorld_RM._42;
//           _matWorld._43 = _matWorld_RM._43;
//           _matWorld._44 = _matWorld_RM._44;
//        } else {
//           _matWorld = _matWorld_RM;
//        }
//    }

//    if (_pFunc_calcWorldMatrix) {
//        if (_pActor_Foundation) {
////            _X_local = _X;
////            _Y_local = _Y;
////            _Z_local = _Z;
////            _X = _matWorld_RM._11*_X_local + _matWorld_RM._21*_Y_local + _matWorld_RM._31*_Z_local;
////            _Y = _matWorld_RM._12*_X_local + _matWorld_RM._22*_Y_local + _matWorld_RM._32*_Z_local;
////            _Z = _matWorld_RM._13*_X_local + _matWorld_RM._23*_Y_local + _matWorld_RM._33*_Z_local;
////            _X_final = _X;
////            _Y_final = _Y;
////            _Z_final = _Z;
//        }
//    }
//
//
//    //８分木に登録
//
//
//    if (_pFunc_calcWorldMatrix) {
//        if (_pActor_Foundation) {
//            _X = _X_local;
//            _Y = _Y_local;
//            _Z = _Z_local;
//        }
//    }
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
        if ( _fDist_VpPlnTop <= _fBoundingSphereRadius) {
            if ( _fDist_VpPlnBottom <= _fBoundingSphereRadius) {
                if ( _fDist_VpPlnLeft <= _fBoundingSphereRadius) {
                    if ( _fDist_VpPlnRight <= _fBoundingSphereRadius) {
                        if ( _fDist_VpPlnFront <= _fBoundingSphereRadius) {
                            if ( _fDist_VpPlnBack <= _fBoundingSphereRadius) {
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


GgafDx9GeometricActor::~GgafDx9GeometricActor() {
    DELETE_IMPOSSIBLE_NULL(_pMover);
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

