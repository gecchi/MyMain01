#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9GeometricActor::GgafDx9GeometricActor(const char* prm_name,
                                             GgafDx9Checker* prm_pChecker) : GgafDx9BaseActor(prm_name) {
    _actor_class |= Obj_GgafDx9GeometricActor;
    _class_name = "GgafDx9GeometricActor";
    _isTransformed = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _x = _y = _z = 0.0f;

    _fBoundingSphereRadius = 0;
    _pChecker = prm_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);
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
        //�y�䂠�莞���[�J�����W�Ɉ�U�߂�
        chengeGeoLocal();
    }

    //DirectX�̒P�ʂɍ��W��ϊ����Ă����iWorld�ϊ��s��쐬���ɂ��g�p����܂��j
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    //World�ϊ��s��i_matWorld�j���X�V
    if (_pFunc_calcRotMvWorldMatrix) {
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
        //�X�P�[�����l��
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
        //��΍��W�ɕϊ�
        D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Base->_matWorldRotMv)); //����
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_Base->_matWorldRotMv)); //����
        chengeGeoFinal();
        //���[���h�ϊ��s�񂩂��s�ړ������o���ŏI�I�ȍ��W�Ƃ���
        _X = _matWorld._41*PX_UNIT*LEN_UNIT;
        _Y = _matWorld._42*PX_UNIT*LEN_UNIT;
        _Z = _matWorld._43*PX_UNIT*LEN_UNIT;
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;

        //TODO:��΍��W��_RX, _RY, _RZ �ɕϊ��͕ۗ�

    }

    //�W���ؓo�^
    if (_pChecker) {
        _pChecker->updateHitArea();
    }

    //�����o�[�X�V
    if (_isTransformed == false) {
        //DirectX�̒P�ʂɍ��W��ϊ����Ă����iWorld�ϊ��s��쐬���ɂ��g�p����܂��j
//        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
//        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
//        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
        //������
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
    if (_actor_class & Obj_GgafDx9GeometricActor) {
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
        //�{���́��̂悤��dynamic_cast����̂��ėp�I�����S�B�������A���xUP�̂��߁idynamic_cast���Ȃ����������߁j�ɁA
        //GgafDx9GeometricActor�Ɍ��ߑł��L���X�g���Ă��܂��B�댯�ł��B
        //���W�������Ȃ��A�N�^�[��_can_hit_flg ��Y�ꂸ��false�ɂ��邱�Ƃɂ���āA�����̈�����GgafDx9GeometricActor��
        //�L���X�g�ł��Ȃ��|�C���^�͗��Ȃ��n�Y�ł���B
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
                                //Viewport�͈͓�
                                _offscreenkind = 0;
                            } else {
                                //�����ʂ�艜�Ŕ͈͊O
                                _offscreenkind = 6;
                            }
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreenkind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreenkind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreenkind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreenkind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
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
    DELETE_IMPOSSIBLE_NULL(_pSeTransmitter);
}


void GgafDx9GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_frame_of_behaving<<","<<_can_hit_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_flg<<"("<<_frame_of_life_when_activation<<")");

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t�b");
            if (pActor_tmp->getNext() != NULL) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��NULL���Ă܂�");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_("\t\t\t\t\t\t\t\t����");
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
            pActor_tmp->dump(prm_parent + "�b");
            if (pActor_tmp->getNext() != NULL) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��NULL���Ă܂�");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_(prm_parent+"����");
                break;
            }
        }
    }
}

