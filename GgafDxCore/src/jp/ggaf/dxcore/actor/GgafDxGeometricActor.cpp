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
    _x = _y = _z = 0;
    _rx = _ry = _rz = 0;
    _sx = _sy = _sz = R_SC(1.0);
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
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
    _x_local  = _x;
    _y_local  = _y;
    _z_local  = _z;
    _rx_local = _rx;
    _ry_local = _ry;
    _rz_local = _rz;
    _x_final  = _x;
    _y_final  = _y;
    _z_final  = _z;
    _rx_final = _rx;
    _ry_final = _ry;
    _rz_final = _rz;
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
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    //World�ϊ��s��i_matWorld�j���X�V
    if (_pFunc_calcRotMvWorldMatrix) {
        //��]�~�ړ��̂݌v�Z�� _matWorldRotMv �ɕێ�
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
        //��]�~�ړ� �̑O�� �X�P�[�����l�����āA
        //�ŏI�I�� _matWorld  �s��(�g��~��]�~�ړ�)��ێ�
        if (_sx != LEN_UNIT) {
            float sx = SC_R(_sx);
            _matWorld._11 = sx * _matWorldRotMv._11;
            _matWorld._12 = sx * _matWorldRotMv._12;
            _matWorld._13 = sx * _matWorldRotMv._13;
        } else {
            _matWorld._11 = _matWorldRotMv._11;
            _matWorld._12 = _matWorldRotMv._12;
            _matWorld._13 = _matWorldRotMv._13;
        }
        _matWorld._14 = _matWorldRotMv._14;

        if (_sy != LEN_UNIT) {
            float sy = SC_R(_sy);
            _matWorld._21 = sy * _matWorldRotMv._21;
            _matWorld._22 = sy * _matWorldRotMv._22;
            _matWorld._23 = sy * _matWorldRotMv._23;
        } else {
            _matWorld._21 = _matWorldRotMv._21;
            _matWorld._22 = _matWorldRotMv._22;
            _matWorld._23 = _matWorldRotMv._23;
        }
        _matWorld._24 = _matWorldRotMv._24;

        if (_sz != LEN_UNIT) {
            float sz = SC_R(_sz);
            _matWorld._31 = sz * _matWorldRotMv._31;
            _matWorld._32 = sz * _matWorldRotMv._32;
            _matWorld._33 = sz * _matWorldRotMv._33;
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
        _x = DX_C(_fX);
        _y = DX_C(_fY);
        _z = DX_C(_fZ);

        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);

        //TODO:��΍��W�n��_rx, _ry, _rz �ɕϊ��͕ۗ�
        //     ���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���߂���@�͈ȉ��̒ʂ�A
        //     �t���[�����[�N�ł� _rx, _ry, _rz �͂ǂ��ł��悭�ϊ��s�񂪂���Ηǂ��B
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
        //���̕����x�N�g���� _rz _ry �\������Ηǂ��B
        //�v�Z���₷���悤��Xorg_��1�ƒu����
        //
        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);
        //�ƂȂ�
    }

    //������X�V
    GgafDxCamera* pCam = P_CAM;
    _dest_from_vppln_top    = pCam->_plnTop.a * _fX +
                              pCam->_plnTop.b * _fY +
                              pCam->_plnTop.c * _fZ +
                              pCam->_plnTop.d;

    _dest_from_vppln_bottom = pCam->_plnBottom.a * _fX +
                              pCam->_plnBottom.b * _fY +
                              pCam->_plnBottom.c * _fZ +
                              pCam->_plnBottom.d;

    _dest_from_vppln_left   = pCam->_plnLeft.a * _fX +
                              pCam->_plnLeft.b * _fY +
                              pCam->_plnLeft.c * _fZ +
                              pCam->_plnLeft.d;

    _dest_from_vppln_right  = pCam->_plnRight.a * _fX +
                              pCam->_plnRight.b * _fY +
                              pCam->_plnRight.c * _fZ +
                              pCam->_plnRight.d;

    _dest_from_vppln_front  = pCam->_plnFront.a * _fX +
                              pCam->_plnFront.b * _fY +
                              pCam->_plnFront.c * _fZ +
                              pCam->_plnFront.d;

    _dest_from_vppln_back   = pCam->_plnBack.a * _fX +
                              pCam->_plnBack.b * _fY +
                              pCam->_plnBack.c * _fZ +
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
                                                     coord prm_x_init_local,
                                                     coord prm_y_init_local,
                                                     coord prm_z_init_local,
                                                     coord prm_rx_init_local,
                                                     coord prm_ry_init_local,
                                                     coord prm_rz_init_local) {
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
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_X]  = prm_rx_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Y]  = prm_ry_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Z]  = prm_rz_init_local;
    prm_pGeoActor->_pKurokoA->_angRzMv = prm_rz_init_local;
    prm_pGeoActor->_pKurokoA->_angRyMv = prm_ry_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
    prm_pGeoActor->changeGeoFinal();
    return pGroupHead;
}

GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_x_init_local,
                                                     coord prm_y_init_local,
                                                     coord prm_z_init_local,
                                                     coord prm_rx_init_local,
                                                     coord prm_ry_init_local,
                                                     coord prm_rz_init_local) {
    return addSubGroupAsFk(prm_pGeoActor->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND),
                           prm_pGeoActor,
                           prm_x_init_local,
                           prm_y_init_local,
                           prm_z_init_local,
                           prm_rx_init_local,
                           prm_ry_init_local,
                           prm_rz_init_local);
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
    if (GgafDxUniverse::_x_gone_left < _x) {
        if (_x < GgafDxUniverse::_x_gone_right) {
            if (GgafDxUniverse::_y_gone_bottom < _y) {
                if (_y < GgafDxUniverse::_y_gone_top) {
                    if (GgafDxUniverse::_z_gone_near < _z) {
                        if (_z < GgafDxUniverse::_z_gone_far) {
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
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
    _z = prm_pGeoElem->z;
}

void GgafDxGeometricActor::rotateAs(GgafDxGeometricActor* prm_pActor) {
    _rx = prm_pActor->_rx;
    _ry = prm_pActor->_ry;
    _rz = prm_pActor->_rz;
}
void GgafDxGeometricActor::rotateAs(GgafDxGeoElem* prm_pGeoElem) {
    _rx = prm_pGeoElem->rx;
    _ry = prm_pGeoElem->ry;
    _rz = prm_pGeoElem->rz;
}

void GgafDxGeometricActor::scaleAs(GgafDxGeometricActor* prm_pActor) {
    _sx = prm_pActor->_sx;
    _sy = prm_pActor->_sy;
    _sz = prm_pActor->_sz;
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
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
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
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
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

