#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeometricActor::GgafDxGeometricActor(const char* prm_name,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) : GgafDxBaseActor(prm_name, prm_pStat),
    _pKuroko(new GgafDxKuroko(this)),
    _pSeTx(new GgafDxSeTransmitterForActor(this)),
    _is_2D(false),
    _offscreen_kind(-1),
    _x(0), _y(0), _z(0),
    _rx(0), _ry(0), _rz(0),
    _sx(R_SC(1.0)), _sy(R_SC(1.0)), _sz(R_SC(1.0)),
    _pChecker(prm_pChecker),
    _rate_of_bounding_sphere_radius(1.0f),
    _fX(C_DX(_x)), _fY(C_DX(_y)), _fZ(C_DX(_z)),
    _dest_from_vppln_top(0.0f),
    _dest_from_vppln_bottom(0.0f),
    _dest_from_vppln_left(0.0f),
    _dest_from_vppln_right(0.0f),
    _dest_from_vppln_front(0.0f),
    _dest_from_vppln_back(0.0f),
    _pFunc_calc_rot_mv_world_matrix(nullptr),
    _matWorld(),
    _matWorldRotMv(),
    _matInvWorldRotMv(),
    _was_calculated_matInvWorldRotMv(false),
    _pActor_base(nullptr),
    _x_local(_x), _y_local(_y), _z_local(_z),
    _rx_local(_rx), _ry_local(_ry), _rz_local(_rz),
    _x_final(_x), _y_final(_y), _z_final(_z),
    _rx_final(_rx), _ry_final(_ry), _rz_final(_rz),
    _is_local(false)
{
    _obj_class |= Obj_GgafDxGeometricActor;
    _class_name = "GgafDxGeometricActor";
    _pFormation = nullptr;
}

void GgafDxGeometricActor::processSettlementBehavior() {
    if (_is_2D) {
        return;
    }

    _was_calculated_matInvWorldRotMv = false; //�t�s�񖢌v�Z�Ƀ��Z�b�g

    if (_pActor_base) {
        //�y�䂠�莞���[�J�����W�Ɉ�U�߂�
        changeGeoLocal();
    }

    //DirectX�̒P�ʂɍ��W��ϊ����Ă����iWorld�ϊ��s��쐬���ɂ��g�p����܂��j
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    //World�ϊ��s��i_matWorld�j���X�V
    if (_pFunc_calc_rot_mv_world_matrix) {
        //��]�~�ړ��̂݌v�Z�� _matWorldRotMv �ɕێ�
        (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
        const D3DXMATRIX& matWorldRotMv = _matWorldRotMv;
        //��]�~�ړ� �̑O�� �X�P�[�����l�����āA
        //�ŏI�I�� _matWorld  �s��(�g��~��]�~�ړ�)��ێ�
        if (_sx != LEN_UNIT) {
            const float sx = SC_R(_sx);
            _matWorld._11 = sx * matWorldRotMv._11;
            _matWorld._12 = sx * matWorldRotMv._12;
            _matWorld._13 = sx * matWorldRotMv._13;
        } else {
            _matWorld._11 = matWorldRotMv._11;
            _matWorld._12 = matWorldRotMv._12;
            _matWorld._13 = matWorldRotMv._13;
        }
        _matWorld._14 = matWorldRotMv._14;

        if (_sy != LEN_UNIT) {
            const float sy = SC_R(_sy);
            _matWorld._21 = sy * matWorldRotMv._21;
            _matWorld._22 = sy * matWorldRotMv._22;
            _matWorld._23 = sy * matWorldRotMv._23;
        } else {
            _matWorld._21 = matWorldRotMv._21;
            _matWorld._22 = matWorldRotMv._22;
            _matWorld._23 = matWorldRotMv._23;
        }
        _matWorld._24 = matWorldRotMv._24;

        if (_sz != LEN_UNIT) {
            const float sz = SC_R(_sz);
            _matWorld._31 = sz * matWorldRotMv._31;
            _matWorld._32 = sz * matWorldRotMv._32;
            _matWorld._33 = sz * matWorldRotMv._33;
        } else {
            _matWorld._31 = matWorldRotMv._31;
            _matWorld._32 = matWorldRotMv._32;
            _matWorld._33 = matWorldRotMv._33;
        }
        _matWorld._34 = matWorldRotMv._34;

        _matWorld._41 = matWorldRotMv._41;
        _matWorld._42 = matWorldRotMv._42;
        _matWorld._43 = matWorldRotMv._43;
        _matWorld._44 = matWorldRotMv._44;
    }

    //�f�t�H���g�ł́A_matWorldRotMv = ��]�ϊ��s�� �~ ���s�ړ��ϊ��s��
    //                _matWorld      = �g��k���ϊ��s�� �~ _matWorldRotMv �ƂȂ�悤�ɂ��Ă���B
    //�܂� _matWorld = �g��k������]�����s�ړ�
    //_matWorldRotMv �� addSubGroupAsFk() ���s���Ɏg�p����邽�߂ɍ쐬���Ă���B
    //�]���� addSubGroupAsFk() ���Ύg�p���Ȃ��Ȃ�΁A_matWorldRotMv�̌v�Z�͕s�v�B
    //processSettlementBehavior() ���I�[�o�[���C�h���A
    //�ϊ��s��쐬�������ƒP�������邱�ƂŁA�����œK�����\�B

    if (_pActor_base) {
        //��΍��W�ɕϊ�
        D3DXMatrixMultiply(&_matWorld     , &_matWorld     , &(_pActor_base->_matWorldRotMv)); //����
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_base->_matWorldRotMv)); //����
        changeGeoFinal();
        //���[���h�ϊ��s��~�y�䃏�[���h�ϊ��s��́u��]�~�ړ��v�݂̂̐ρj���畽�s�ړ����������o���ŏI�I�ȍ��W�Ƃ���
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;
        _x = DX_C(_fX);
        _y = DX_C(_fY);
        _z = DX_C(_fZ);

        //���[�J���ł�face�����������ς݂̃��[���h�ϊ��s��́u��]�~�ړ��v�݂̂̐�(_matWorldRotMv)������̂ŁA
        //�x�N�g��(1,0,0)�ɍ����ςݕϊ��s����|����΍ŏI�I��face�����𓾂��
        UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);
        _rx = _rx_local; //���̂܂�

        //TODO:��΍��W�n��_rx, _ry, _rz �ɕϊ��͕ۗ�
        //     ���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���߂���@�͈ȉ��̒ʂ�A
        //     �t���[�����[�N�ł� _rx, _ry, _rz �͂ǂ��ł��悭�ϊ��s�񂪂���Ηǂ��B
        //     ���������Čv�Z���X�L�b�v�ł���ꍇ������B
        //     UTIL::convVectorToRzRy() �̌v�Z���ׂƑ��k�B
        //
        //��������
        //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
        //�匳�̕����x�N�g����(x_org_,y_org_,z_org_)�A
        //���[���h�ϊ��s��̉�]�����̐ρi_matWorldRotMv)�̐����� mat_xx�A
        //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
        //
        //                         | mat_11 mat_12 mat_13 |
        //| x_org_ y_org_ z_org_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
        //                         | mat_31 mat_32 mat_33 |
        //�ƂȂ�B
        //
        //vX = x_org_*mat_11 + y_org_*mat_21 + z_org_*mat_31
        //vY = x_org_*mat_12 + y_org_*mat_22 + z_org_*mat_32
        //vZ = x_org_*mat_13 + y_org_*mat_23 + z_org_*mat_33
        //
        //���Ă����ŁA�匳���O���̒P�ʕ����x�N�g��(1,0,0)�̏ꍇ�͂ǂ��Ȃ邩�H���l�����
        //
        //vX = x_org_*mat_11
        //vY = x_org_*mat_12
        //vZ = x_org_*mat_13
        //
        //�ƂȂ�B�{�A�v���ł́A���f���͑S��(1,0,0)��O���Ƃ��Ă��邽��
        //�ŏI�I�ȕ����x�N�g���́ix_org_*mat_11, x_org_*mat_12, x_org_*mat_13) �ƂȂ�B
        //���̕����x�N�g���� _rz _ry �\������Ηǂ��B
        //�v�Z���₷���悤��x_org_��1�ƒu����
        //
        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);
        //�ƂȂ�
        processChangeGeoFinal();
    }

    //������ʂ���̋������X�V
    const dxcoord fX = _fX;
    const dxcoord fY = _fY;
    const dxcoord fZ = _fZ;
    const GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    const D3DXPLANE& plnTop = pCam->_plnTop;
    _dest_from_vppln_top    = plnTop.a * fX +
                              plnTop.b * fY +
                              plnTop.c * fZ +
                              plnTop.d;
    const D3DXPLANE& plnBottom = pCam->_plnBottom;
    _dest_from_vppln_bottom = plnBottom.a * fX +
                              plnBottom.b * fY +
                              plnBottom.c * fZ +
                              plnBottom.d;
    const D3DXPLANE& plnLeft = pCam->_plnLeft;
    _dest_from_vppln_left   = plnLeft.a * fX +
                              plnLeft.b * fY +
                              plnLeft.c * fZ +
                              plnLeft.d;
    const D3DXPLANE& plnRight = pCam->_plnRight;
    _dest_from_vppln_right  = plnRight.a * fX +
                              plnRight.b * fY +
                              plnRight.c * fZ +
                              plnRight.d;
    const D3DXPLANE& plnFront = pCam->_plnFront;
    _dest_from_vppln_front  = plnFront.a * fX +
                              plnFront.b * fY +
                              plnFront.c * fZ +
                              plnFront.d;
   const D3DXPLANE& plnBack = pCam->_plnBack;
    _dest_from_vppln_back   = plnBack.a * fX +
                              plnBack.b * fY +
                              plnBack.c * fZ +
                              plnBack.d;
    _offscreen_kind = -1;

    //�����ؓo�^
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

//void GgafDxGeometricActor::updateGeoFinalFromLocal() {
//
//}
GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(actorkind prm_kind,
                                                     GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_x_init_local,
                                                     coord prm_y_init_local,
                                                     coord prm_z_init_local,
                                                     coord prm_rx_init_local,
                                                     coord prm_ry_init_local,
                                                     coord prm_rz_init_local) {
#ifdef MY_DEBUG
    if (_pFunc_calc_rot_mv_world_matrix) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxGeometricActor::addSubGroupAsFk() : "<<
                                   "this="<<NODE_INFO<<" �́A_pFunc_calc_rot_mv_world_matrix �� nullptr�ׁ̈AFK�x�[�X�ƂȂ鎑�i������܂���");
    }
#endif
    GgafGroupHead* pGroupHead = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
//    prm_pGeoActor->getKuroko()->_ang_rz_mv = prm_rz_init_local;
//    prm_pGeoActor->getKuroko()->_ang_ry_mv = prm_ry_init_local;

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
    return addSubGroupAsFk(prm_pGeoActor->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND),
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
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg �̃`�F�b�N�͔����ؓo�^�O�ɂ��`�F�b�N���Ă邪
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
    //���E���a�i���f�����̂������j�̂ŁAPX_DX(1) ����ʓ��ɂ��邩�ǂ����𔻒肷��B
    //���f������ʓ��ɂ��邩�ǂ�������́AGgafDxFigureActor �ŃI�[�o�[���C�h����Ă����ōs���B
    if (_offscreen_kind == -1) {
        const dxcoord bound = PX_DX(1); //���E���a
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

bool GgafDxGeometricActor::isOutOfSpacetime() const {
    GgafDxSpacetime* pSpacetime =  P_GOD->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x) {
        if (_x <= pSpacetime->_x_bound_right) {
            if (pSpacetime->_y_bound_bottom <= _y) {
                if (_y <= pSpacetime->_y_bound_top) {
                    if (pSpacetime->_z_bound_near <= _z) {
                        if (_z <= pSpacetime->_z_bound_far) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GgafDxGeometricActor::defineRotMvWorldMatrix(void (*prm_pFunc)(const GgafDxGeometricActor*, D3DXMATRIX&)) {
    _pFunc_calc_rot_mv_world_matrix = prm_pFunc;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxGeometricActor::positionAs(const GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
    _z = prm_pGeoElem->z;
}
void GgafDxGeometricActor::positionAboutAs(const GgafDxGeoElem* prm_pGeoElem, coord margin) {
    _x = RND_ABOUT(prm_pGeoElem->x, margin);
    _y = RND_ABOUT(prm_pGeoElem->y, margin);
    _z = RND_ABOUT(prm_pGeoElem->z, margin);
}
void GgafDxGeometricActor::setFaceAngAs(const GgafDxGeometricActor* prm_pActor) {
    _rx = prm_pActor->_rx;
    _ry = prm_pActor->_ry;
    _rz = prm_pActor->_rz;
}
void GgafDxGeometricActor::setFaceAngAs(const GgafDxGeoElem* prm_pGeoElem) {
    _rx = prm_pGeoElem->rx;
    _ry = prm_pGeoElem->ry;
    _rz = prm_pGeoElem->rz;
}

//void GgafDxGeometricActor::setFaceAng(axis prm_axis, angle prm_angFace) {
//    _angFace[prm_axis] = UTIL::simplifyAng(prm_angFace);
//}

void GgafDxGeometricActor::setRzFaceAng(angle prm_angFace) {
    _rz = UTIL::simplifyAng(prm_angFace);
}
void GgafDxGeometricActor::setRyFaceAng(angle prm_angFace) {
    _ry = UTIL::simplifyAng(prm_angFace);
}
void GgafDxGeometricActor::setRxFaceAng(angle prm_angFace) {
    _rx = UTIL::simplifyAng(prm_angFace);
}

void GgafDxGeometricActor::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _x;
    coord vy = prm_ty - _y;
    coord vz = prm_tz - _z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //���g�̍��W�ɓ������̂ŁA�������Ȃ�
    } else {
        UTIL::convVectorToRzRy(vx, vy, vz,
                               _rz, _ry );
    }
}

void GgafDxGeometricActor::scaleAs(const GgafDxGeometricActor* prm_pActor) {
    _sx = prm_pActor->_sx;
    _sy = prm_pActor->_sy;
    _sz = prm_pActor->_sz;
}

void GgafDxGeometricActor::onEnd() {
    GgafDxBaseActor::onEnd();
    _pFormation = nullptr;
}

GgafDxGeometricActor::~GgafDxGeometricActor() {
    delete _pKuroko;
    delete _pSeTx;
}

void GgafDxGeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->dump("\t\t\t\t\t\t\t\t�b");
        if (pActor_tmp->getNext()) {
            pActor_tmp = pActor_tmp->getNext();
        } else {
            _TRACE_("�y�x���z"<<NODE_INFO<<" ��next��nullptr���Ă܂�");
            break;
        }
        if (pActor_tmp->isFirst()) {
            _TRACE_("\t\t\t\t\t\t\t\t����");
            break;
        }
    }
}

void GgafDxGeometricActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->dump(prm_parent + "�b");
        if (pActor_tmp->getNext()) {
            pActor_tmp = pActor_tmp->getNext();
        } else {
            _TRACE_("�y�x���z"<<NODE_INFO<<" ��next��nullptr���Ă܂�");
            break;
        }
        if (pActor_tmp->isFirst()) {
            _TRACE_(prm_parent+"����");
            break;
        }
    }
}

