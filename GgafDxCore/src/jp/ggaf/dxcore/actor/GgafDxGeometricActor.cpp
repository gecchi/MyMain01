#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeometricActor::GgafDxGeometricActor(const char* prm_name,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) : GgafDxBaseActor(prm_name, prm_pStat),
_pKurokoA(new GgafDxKurokoA(this)),
_pKurokoB(new GgafDxKurokoB(this)),
_pSeTx(new GgafDxSeTransmitterForActor(this)) {

    _obj_class |= Obj_GgafDxGeometricActor;
    _class_name = "GgafDxGeometricActor";
    _is_2D = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    _bounding_sphere_radius = 0;
    _rate_of_bounding_sphere_radius = 1.0f;
    _pChecker = prm_pChecker;

    _offscreen_kind = -1;
    _pFunc_calcRotMvWorldMatrix = nullptr;
    _pActor_Base = nullptr;
    _dest_from_vppln_top = 0;
    _dest_from_vppln_bottom = 0;
    _dest_from_vppln_left = 0;
    _dest_from_vppln_right = 0;
    _dest_from_vppln_front = 0;
    _dest_from_vppln_back = 0;
    _X_local  = _X;
    _Y_local  = _Y;
    _Z_local  = _Z;
    _RX_local = _RX;
    _RY_local = _RY;
    _RZ_local = _RZ;
    _X_final  = _X;
    _Y_final  = _Y;
    _Z_final  = _Z;
    _RX_final = _RX;
    _RY_final = _RY;
    _RZ_final = _RZ;
    _pFormation = nullptr;

    _is_local = false;
    _was_calculated_matInvWorldRotMv = false;
}


void GgafDxGeometricActor::processSettlementBehavior() {
    if (_is_2D) {
        return;
    }

    _was_calculated_matInvWorldRotMv = false; //�t�s�񖢌v�Z�Ƀ��Z�b�g

    if (_pActor_Base) {
        //�y�䂠�莞���[�J�����W�Ɉ�U�߂�
        changeGeoLocal();
    }

    //DirectX�̒P�ʂɍ��W��ϊ����Ă����iWorld�ϊ��s��쐬���ɂ��g�p����܂��j
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    //World�ϊ��s��i_matWorld�j���X�V
    if (_pFunc_calcRotMvWorldMatrix) {
        //��]�~�ړ��̂݌v�Z�� _matWorldRotMv �ɕێ�
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
        //��]�~�ړ� �̑O�� �X�P�[�����l�����āA
        //�ŏI�I�� _matWorld  �s��(�g��~��]�~�ړ�)��ێ�
        if (_SX != LEN_UNIT) {
            float Sx = SC_R(_SX);
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
            float Sy = SC_R(_SY);
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
            float Sz = SC_R(_SZ);
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

    //�f�t�H���g�ł́A_matWorldRotMv = ��]�ϊ��s�� �~ ���s�ړ��ϊ��s��
    //                _matWorld      = �X�P�[���ϊ��s�� �~ _matWorldRotMv �ƂȂ�悤�ɂ��Ă���B
    //�܂� _matWorld = �g��k������]�����s�ړ�
    //_matWorldRotMv �� addSubGroupAsFk() ���s���Ɏg�p����邽�߂ɍ쐬���Ă���B
    //�]���� addSubGroupAsFk() ���g�p���Ȃ��Ȃ�΁AprocessSettlementBehavior() ���I�[�o�[���C�h���A
    //�ϊ��s��쐬�������ƒP�������邱�ƂŁA�����œK�����\�B

    if (_pActor_Base) {
        //��΍��W�ɕϊ�

        D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Base->_matWorldRotMv)); //����
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_Base->_matWorldRotMv)); //����
        changeGeoFinal();
        //���[���h�ϊ��s�񂩂��s�ړ������o���ŏI�I�ȍ��W�Ƃ���

        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;

        _X = DX_C(_fX);
        _Y = DX_C(_fY);
        _Z = DX_C(_fZ);

        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _RZ, _RY);

        //TODO:��΍��W�n��_RX, _RY, _RZ �ɕϊ��͕ۗ�
        //     ���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���߂���@�͈ȉ��̒ʂ�A
        //     �t���[�����[�N�ł� _RX, _RY, _RZ �͂ǂ��ł��悭�ϊ��s�񂪂���Ηǂ��B
        //     ���������Čv�Z���X�L�b�v�ł���B
        //     UTIL::convVectorToRzRy() �̌v�Z���ׂ������ł��Ȃ��ƍl�������߁A�����Ōv�Z���Ȃ��B
        //     �v�Z�ŋ��߂��Ȃ�Έȉ��̕��@�ōs����
        //
        //��������
        //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
        //�匳�̕����x�N�g����(Xorg_,Yorg_,Zorg_)�A
        //���[���h�ϊ��s��̉�]�����̐ρi_matWorldRotMv)�̐����� mat_xx�A
        //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
        //
        //                      | mat_11 mat_12 mat_13 |
        //| Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
        //                      | mat_31 mat_32 mat_33 |
        //�ƂȂ�B
        //
        //vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
        //vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
        //vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
        //
        //���Ă����ŁA�匳���O���̒P�ʕ����x�N�g��(1,0,0)�̏ꍇ�͂ǂ��Ȃ邩�H���l�����
        //
        //vX = Xorg_*mat_11
        //vY = Xorg_*mat_12
        //vZ = Xorg_*mat_13
        //
        //�ƂȂ�B�{�A�v���ł́A���f���͑S��(1,0,0)��O���Ƃ��Ă��邽��
        //�ŏI�I�ȕ����x�N�g���́iXorg_*mat_11, Xorg_*mat_12, Xorg_*mat_13) �ƂȂ�B
        //���̕����x�N�g���� _RZ _RY �\������Ηǂ��B
        //�v�Z���₷���悤��Xorg_��1�ƒu����
        //
        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _RZ, _RY);
        //�ƂȂ�
    }

    //������X�V
    GgafDxCamera* pCam = P_CAM;
    _dest_from_vppln_top    = pCam->_plnTop.a*_fX +
                              pCam->_plnTop.b*_fY +
                              pCam->_plnTop.c*_fZ +
                              pCam->_plnTop.d;

    _dest_from_vppln_bottom = pCam->_plnBottom.a*_fX +
                              pCam->_plnBottom.b*_fY +
                              pCam->_plnBottom.c*_fZ +
                              pCam->_plnBottom.d;

    _dest_from_vppln_left   = pCam->_plnLeft.a*_fX +
                              pCam->_plnLeft.b*_fY +
                              pCam->_plnLeft.c*_fZ +
                              pCam->_plnLeft.d;

    _dest_from_vppln_right  = pCam->_plnRight.a*_fX +
                              pCam->_plnRight.b*_fY +
                              pCam->_plnRight.c*_fZ +
                              pCam->_plnRight.d;

    _dest_from_vppln_front  = pCam->_plnFront.a*_fX +
                              pCam->_plnFront.b*_fY +
                              pCam->_plnFront.c*_fZ +
                              pCam->_plnFront.d;

    _dest_from_vppln_back   = pCam->_plnBack.a*_fX +
                              pCam->_plnBack.b*_fY +
                              pCam->_plnBack.c*_fZ +
                              pCam->_plnBack.d;
    _offscreen_kind = -1;

    //�W���ؓo�^
    if (_pChecker) {
        if (_can_hit_flg) {
            if (_can_hit_out_of_view == false && isOutOfView()) {
                //����O�����蔻�薳���̏ꍇ�͓o�^���Ȃ�
            } else  {
                _pChecker->updateHitArea();
            }
        }
    }
}


GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(actorkind prm_kind,
                                                     GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_X_init_local,
                                                     coord prm_Y_init_local,
                                                     coord prm_Z_init_local,
                                                     coord prm_RX_init_local,
                                                     coord prm_RY_init_local,
                                                     coord prm_RZ_init_local) {
#ifdef MY_DEBUG
    if (_pFunc_calcRotMvWorldMatrix) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxGeometricActor::addSubGroupAsFk() : "<<
                                   "this=("<<this<<")["<<getName()<<"] �́A_pFunc_calcRotMvWorldMatrix �� nullptr�ׁ̈AFK�x�[�X�ƂȂ鎑�i������܂���");
    }
#endif
    GgafGroupHead* pGroupHead = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_Base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_X = prm_X_init_local;
    prm_pGeoActor->_Y = prm_Y_init_local;
    prm_pGeoActor->_Z = prm_Z_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_X]  = prm_RX_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Y]  = prm_RY_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Z]  = prm_RZ_init_local;
    prm_pGeoActor->_pKurokoA->_angRzMv = prm_RZ_init_local;
    prm_pGeoActor->_pKurokoA->_angRyMv = prm_RY_init_local;
    prm_pGeoActor->_RX = prm_RX_init_local;
    prm_pGeoActor->_RY = prm_RY_init_local;
    prm_pGeoActor->_RZ = prm_RZ_init_local;
    prm_pGeoActor->changeGeoFinal();
    return pGroupHead;
}

GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_X_init_local,
                                                     coord prm_Y_init_local,
                                                     coord prm_Z_init_local,
                                                     coord prm_RX_init_local,
                                                     coord prm_RY_init_local,
                                                     coord prm_RZ_init_local) {
    return addSubGroupAsFk(prm_pGeoActor->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND),
                           prm_pGeoActor,
                           prm_X_init_local,
                           prm_Y_init_local,
                           prm_Z_init_local,
                           prm_RX_init_local,
                           prm_RY_init_local,
                           prm_RZ_init_local);
}

bool GgafDxGeometricActor::processHitChkLogic(GgafActor* prm_pOtherActor) {
    if (_can_hit_flg && prm_pOtherActor->_can_hit_flg) {
        //&& prm_pOtherActor->instanceOf(Obj_GgafDxGeometricActor)) { �����蔻�肪����̂�GgafDxGeometricActor�ȏ�Ɣ��f
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg �̃`�F�b�N�͂W���ؓo�^�O�ɂ��`�F�b�N���Ă邪
        //�����ł�������x�`�F�b�N����ق������ǂ��B
        //�Ȃ��Ȃ�΁A���ʂȃq�b�g�`�F�b�N���s��Ȃ����߁AonHit(GgafActor*) �������� setHitAble(false) ���s���A
        //�Q�d�q�b�g�`�F�b�N�h�~���s���Ă��邩������Ȃ�����B
        if (_pChecker) {
            return _pChecker->isHit(((GgafDxGeometricActor*)prm_pOtherActor)->_pChecker);
        }
    }
    return false;
}

int GgafDxGeometricActor::isOutOfView() {
    //_TRACE_("name="<<getName()<<" _bounding_sphere_radius="<<_bounding_sphere_radius);
    if (_offscreen_kind == -1) {
        dxcoord bound = _bounding_sphere_radius * _rate_of_bounding_sphere_radius*2;//�|����2�͋��E����傫�����āA��ʋ��E�̃`���c�L��}����
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_front < bound) {
                            if (_dest_from_vppln_back < bound) {
                                //Viewport�͈͓�
                                _offscreen_kind = 0;
                            } else {
                                //�����ʂ�艜�Ŕ͈͊O
                                _offscreen_kind = 6;
                            }
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreen_kind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreen_kind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreen_kind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreen_kind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}

bool GgafDxGeometricActor::isOutOfUniverse() {
    if (GgafDxUniverse::_X_gone_left < _X) {
        if (_X < GgafDxUniverse::_X_gone_right) {
            if (GgafDxUniverse::_Y_gone_bottom < _Y) {
                if (_Y < GgafDxUniverse::_Y_gone_top) {
                    if (GgafDxUniverse::_Z_gone_near < _Z) {
                        if (_Z < GgafDxUniverse::_Z_gone_far) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GgafDxGeometricActor::defineRotMvWorldMatrix(void (*prm_pFunc)(GgafDxGeometricActor*, D3DXMATRIX&)) {
    _pFunc_calcRotMvWorldMatrix = prm_pFunc;
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
}

void GgafDxGeometricActor::positionAs(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
    _Z = prm_pGeoElem->_Z;
}

void GgafDxGeometricActor::rotateAs(GgafDxGeometricActor* prm_pActor) {
    _RX = prm_pActor->_RX;
    _RY = prm_pActor->_RY;
    _RZ = prm_pActor->_RZ;
}
void GgafDxGeometricActor::rotateAs(GgafDxGeoElem* prm_pGeoElem) {
    _RX = prm_pGeoElem->_RX;
    _RY = prm_pGeoElem->_RY;
    _RZ = prm_pGeoElem->_RZ;
}

void GgafDxGeometricActor::scaleAs(GgafDxGeometricActor* prm_pActor) {
    _SX = prm_pActor->_SX;
    _SY = prm_pActor->_SY;
    _SZ = prm_pActor->_SZ;
}

void GgafDxGeometricActor::onEnd() {
    GgafDxBaseActor::onEnd();
    _pFormation = nullptr;
}

GgafDxGeometricActor::~GgafDxGeometricActor() {
    delete _pKurokoA;
    delete _pKurokoB;
    delete _pSeTx;
}

void GgafDxGeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t�b");
            if (pActor_tmp->getNext()) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��nullptr���Ă܂�");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_("\t\t\t\t\t\t\t\t����");
                break;
            }
        }
    }
}

void GgafDxGeometricActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump(prm_parent + "�b");
            if (pActor_tmp->getNext()) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��nullptr���Ă܂�");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_(prm_parent+"����");
                break;
            }
        }
    }
}

