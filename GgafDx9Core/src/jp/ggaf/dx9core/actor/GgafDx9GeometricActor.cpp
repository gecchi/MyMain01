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

    _max_radius = 0;
    _pChecker = prm_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);

    _offscreenkind = -1;
    _pFunc_calcWorldMatrix = NULL;
}


void GgafDx9GeometricActor::processPreJudgement() {
    if (_isTransformed == false) {
        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);

        _fDistance_plnTop    = GgafDx9Universe::_pCamera->_plnTop.a*_fX +
                               GgafDx9Universe::_pCamera->_plnTop.b*_fY +
                               GgafDx9Universe::_pCamera->_plnTop.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnTop.d;

        _fDistance_plnBottom = GgafDx9Universe::_pCamera->_plnBottom.a*_fX +
                               GgafDx9Universe::_pCamera->_plnBottom.b*_fY +
                               GgafDx9Universe::_pCamera->_plnBottom.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnBottom.d;

        _fDistance_plnLeft   = GgafDx9Universe::_pCamera->_plnLeft.a*_fX +
                               GgafDx9Universe::_pCamera->_plnLeft.b*_fY +
                               GgafDx9Universe::_pCamera->_plnLeft.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnLeft.d;

        _fDistance_plnRight  = GgafDx9Universe::_pCamera->_plnRight.a*_fX +
                               GgafDx9Universe::_pCamera->_plnRight.b*_fY +
                               GgafDx9Universe::_pCamera->_plnRight.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnRight.d;

        _fDistance_plnFront  = GgafDx9Universe::_pCamera->_plnFront.a*_fX +
                               GgafDx9Universe::_pCamera->_plnFront.b*_fY +
                               GgafDx9Universe::_pCamera->_plnFront.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnFront.d;

        _fDistance_plnBack   = GgafDx9Universe::_pCamera->_plnBack.a*_fX +
                               GgafDx9Universe::_pCamera->_plnBack.b*_fY +
                               GgafDx9Universe::_pCamera->_plnBack.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnBack.d;
        _offscreenkind = -1;
    }
    if (_pChecker) {
        _pChecker->updateHitArea();
    }
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
        //一応_can_hit_flg を忘れずにfalseにすることによって、ここの引数にGgafDx9GeometricActorに
        //キャストできないポインタは来ないよう なっています。
        //万が一来たら・・・その時にまた考える。
        //何かおかしいとおもったらここが怪しいかもしれない。潜在的なバグの可能性あり。
        //TODO:考える。
        return _pChecker->isHit(((GgafDx9GeometricActor*)prm_pOtherActor)->_pChecker);
    }
}




int GgafDx9GeometricActor::isOffscreen() {
    //_TRACE_("name="<<getName()<<" _max_radius="<<_max_radius);
    if (_offscreenkind == -1) {
        if ( _fDistance_plnTop <= _max_radius) {
            if ( _fDistance_plnBottom <= _max_radius) {
                if ( _fDistance_plnLeft <= _max_radius) {
                    if ( _fDistance_plnRight <= _max_radius) {
                        if ( _fDistance_plnFront <= _max_radius) {
                            if ( _fDistance_plnBack <= _max_radius) {
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
                     if (GgafDx9Universe::_Z_goneFront < _Z) {
                          if (_Z < GgafDx9Universe::_Z_goneBack) {
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
    //if (_pChecker) {
    //    DELETE_IMPOSSIBLE_NULL(_pChecker);
    //}
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



