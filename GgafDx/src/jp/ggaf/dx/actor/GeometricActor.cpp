#include "jp/ggaf/dx/actor/GeometricActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/NaviVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

GeometricActor::GeometricActor(const char* prm_name) : GgafCore::MainActor(prm_name),
_pLocusVehicle(nullptr),
_pCoordVehicle(nullptr),
_pNaviVehicle(nullptr),
_pScaler(nullptr),
_pSeTransmitter(nullptr),
_pVehicleLeader(nullptr),
_is_fix_2D(false),
_offscreen_kind(-1),
_x(0), _y(0), _z(0),
_rx(0), _ry(0), _rz(0),
_sx(R_SC(1.0)), _sy(R_SC(1.0)), _sz(R_SC(1.0)),
//_pSubChecker(nullptr),
_rate_of_bounding_sphere_radius(1.0f),
_fX(C_DX(_x)), _fY(C_DX(_y)), _fZ(C_DX(_z)),
_dest_from_vppln_top(0.0f),
_dest_from_vppln_bottom(0.0f),
_dest_from_vppln_left(0.0f),
_dest_from_vppln_right(0.0f),
_dest_from_vppln_infront(0.0f),
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
    _obj_class |= Obj_GgafDx_GeometricActor;
    _class_name = "GeometricActor";
    _pFormation = nullptr;
}
CollisionChecker* GeometricActor::createChecker() {
    return NEW CollisionChecker(this);
}
LocusVehicle* GeometricActor::getLocusVehicle() {
    return _pLocusVehicle ? _pLocusVehicle : _pLocusVehicle = NEW LocusVehicle(this);
}

CoordVehicle* GeometricActor::getCoordVehicle() {
    return _pCoordVehicle ? _pCoordVehicle : _pCoordVehicle = NEW CoordVehicle(this);
}

NaviVehicle* GeometricActor::getNaviVehicle() {
    return _pNaviVehicle ? _pNaviVehicle : _pNaviVehicle = NEW NaviVehicle(this);
}

VehicleLeader* GeometricActor::createCurveVehicleLeader(CurveManufacture* prm_pCurveManufacture) {
    VehicleLeader* pVehicleLeader = nullptr;
    CurveManufacture::MoveDriver move_driver = prm_pCurveManufacture->_move_driver;
    if (move_driver == CurveManufacture::MoveDriver::CoordVehicle) {
        pVehicleLeader = prm_pCurveManufacture->createCoordVehicleLeader(getCoordVehicle());
    } else if (move_driver == CurveManufacture::MoveDriver::LocusVehicle) {
        pVehicleLeader = prm_pCurveManufacture->createLocusVehicleLeader(getLocusVehicle());
    } else {
        throwCriticalException("createCurveVehicleLeader() : CurveManufacture::MoveDrive ���ݒ肳��Ă��܂���B"<<
                "ldr_file="<<prm_pCurveManufacture->_ldr_file<<" move_driver="<<move_driver<<" this="<<NODE_INFO<<"");
    }
    return pVehicleLeader;
}


SeTransmitterForActor* GeometricActor::getSeXmtr() {
    return _pSeTransmitter ? _pSeTransmitter : _pSeTransmitter = NEW SeTransmitterForActor(this);
}

Scaler* GeometricActor::getScaler() {
    return _pScaler ? _pScaler : _pScaler = NEW Scaler(this);
}

void GeometricActor::processSettlementBehavior() {
    if (_is_fix_2D) {
        // ������
    } else {
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
            //��]�~�ړ��̂݌v�Z�� _matWorldRotMv ��
            (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
            _matWorld = _matWorldRotMv; //�R�s�[���ĕێ�
            //��]�~�ړ� �̑O�� �X�P�[�����l�����āA
            //�ŏI�I�� _matWorld  �s��(�g��~��]�~�ړ�)��ێ�
            if (_sx != LEN_UNIT) {
                const float sx = SC_R(_sx);
                _matWorld._11 *= sx;
                _matWorld._12 *= sx;
                _matWorld._13 *= sx;
            }
            if (_sy != LEN_UNIT) {
                const float sy = SC_R(_sy);
                _matWorld._21 *= sy;
                _matWorld._22 *= sy;
                _matWorld._23 *= sy;
            }
            if (_sz != LEN_UNIT) {
                const float sz = SC_R(_sz);
                _matWorld._31 *= sz;
                _matWorld._32 *= sz;
                _matWorld._33 *= sz;
            }
        }

        //�f�t�H���g�ł́A_matWorldRotMv = ��]�ϊ��s�� �~ ���s�ړ��ϊ��s��
        //                _matWorld      = �g��k���ϊ��s�� �~ _matWorldRotMv �ƂȂ�悤�ɂ��Ă���B
        //�܂� _matWorld = �g��k������]�����s�ړ�
        //_matWorldRotMv �� appendChildAsFk() ���s���Ɏg�p����邽�߂ɍ쐬���Ă���B
        //�]���� appendChildAsFk() ���Ύg�p���Ȃ��Ȃ�΁A_matWorldRotMv�̌v�Z�͕s�v�B
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
            //��������Ă���̂������B
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
            processChangeGeoFinal(); //��΍��W�v�Z��̏����p�R�[���o�b�N
        }

        // ������̖ʂ���̋���
        //-------------------------------------------------
        //  ���ʕ������Fax+by+cz+d
        //  ���ʂ̖@���x�N�g���Fn = (a, b, c)
        //  ���ʏ��1�_���Ap = (x0, y0, z0) �Ƃ���ƁA
        //  ���ʂ̖@���x�N�g���ƕ��ʏ��1�_�̓��ρFd = n*p
        //
        //  �\�����������Ƃ��́A�_ p = (x0, y0, z0)���A
        //  p = (x0, y0, z0, 1) �Ƃ݂Ȃ��A
        //  ���ʂƂ̓��ρFa*x0 + b*y0 + c*z0 + d*1 = ans
        //  ans > 0 �Ȃ�\�Aans < 0 �Ȃ痠�Aans == 0 �Ȃ�ʏ�A�ƂȂ�B
        //  DXPlaneDotCoord() �́A���̏������s���Ă���
        //
        //  �܂��Ap = (x0, y0, z0, 0) �Ƃ݂Ȃ��ē��ς̌v�Z���s���ƁA
        //  �p�x�̊֌W�𒲂ׂ邱�Ƃ��ł���B
        //  �� D3DXPlaneDotNormal()
        //-------------------------------------------------
        //�ʁFa x + b y + c z + d = 0
        //�_�F(x0, y0, z0)
        //�ɂ����āA�ʂƓ_�̋�����        _______________
        //D = (a x0 + b y0 + cz0 + d) / ��a^2 +b^2 + c^2
        //�ł��邪
        //�ʕ������̖@�����K���ς݂Ȃ̂ŁA���ꁁ1 �ƂȂ�

        //������ʂ���̋������X�V
        const dxcoord fX = _fX;
        const dxcoord fY = _fY;
        const dxcoord fZ = _fZ;
        Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
        const D3DXPLANE* pPlnTop = &(pCam->_plnTop);
        _dest_from_vppln_top     = pPlnTop->a * fX +
                                   pPlnTop->b * fY +
                                   pPlnTop->c * fZ +
                                   pPlnTop->d;
        const D3DXPLANE* pPlnBottom = &(pCam->_plnBottom);
        _dest_from_vppln_bottom  = pPlnBottom->a * fX +
                                   pPlnBottom->b * fY +
                                   pPlnBottom->c * fZ +
                                   pPlnBottom->d;
        const D3DXPLANE* pPlnLeft = &(pCam->_plnLeft);
        _dest_from_vppln_left    = pPlnLeft->a * fX +
                                   pPlnLeft->b * fY +
                                   pPlnLeft->c * fZ +
                                   pPlnLeft->d;

        const D3DXPLANE* pPlnRight = &(pCam->_plnRight);
        _dest_from_vppln_right   = pPlnRight->a * fX +
                                   pPlnRight->b * fY +
                                   pPlnRight->c * fZ +
                                   pPlnRight->d;

        const D3DXPLANE* pPlnInfront = &(pCam->_plnInfront);
        _dest_from_vppln_infront = pPlnInfront->a * fX +
                                   pPlnInfront->b * fY +
                                   pPlnInfront->c * fZ +
                                   pPlnInfront->d;
        const D3DXPLANE* pPlnBack = &(pCam->_plnBack);
        _dest_from_vppln_back    = pPlnBack->a * fX +
                                   pPlnBack->b * fY +
                                   pPlnBack->c * fZ +
                                   pPlnBack->d;
        _offscreen_kind = -1;
    }
}

void GeometricActor::judge() {
    if (_is_active_in_the_tree_flg) {
        processJudgement();    //���[�U�[�����p

        //�����蔻��ׂ̈ɔ����؁i�l���؁j�ɓo�^���� .
        if (_can_hit_flg) {
            if (_enable_out_of_view_hit_flg == false && isOutOfView()) {
                //����O�����蔻�薳���̏ꍇ�͓o�^���Ȃ�
            } else {
                //�ؓo�^
                CollisionChecker* pColliChecker = getChecker();
                do {
                    if (pColliChecker->_kind > 0) {
                        pColliChecker->updateHitArea();
                    }
                    pColliChecker = (CollisionChecker*)pColliChecker->_pNextChecker;
                } while (pColliChecker);
            }
        }
        //�ċA
        GgafCore::Element<GgafCore::Actor>* pElementTemp = _pChildFirst;
        while (pElementTemp) {
            pElementTemp->judge();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}
void GeometricActor::processAfterDraw() {
#ifdef MY_DEBUG
//    //�e�����V�[���̃��J�[�e����ݒ肷��B
//    getEffect()->setAlphaMaster(((Scene*)getPlatformScene())->_scene_alpha);
//    _TRACE_("this="<<getName()<<" PlathoneScene="<<((Scene*)getPlatformScene())->getName()<<" _scene_alpha="<<((Scene*)getPlatformScene())->_scene_alpha);
    //�����蔻��̈�\��
    int draw_hit_area_kind = pCARETAKER->_draw_hit_area_kind;
    if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME) {
        if (draw_hit_area_kind == 1) {
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            drawHitArea();
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
        } else if (draw_hit_area_kind == 2) {
            drawHitArea();
        }
    } else {
        //pCARETAKER->_d3dfillmode == D3DFILL_SOLID
        if (draw_hit_area_kind == 1) {
            drawHitArea();
        } else if (draw_hit_area_kind == 2) {
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
            drawHitArea();
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        }

    }
#endif
}

void GeometricActor::changeGeoLocal() {
#ifdef MY_DEBUG
        if (!_pActor_base) {
            throwCriticalException("changeGeoLocal() : �y��A�N�^�[������܂���B�m�F���ĉ������Bthis="<<NODE_INFO<<"");
        }
        if (_is_local) {
            throwCriticalException("changeGeoLocal() : ���Ƀ��[�J�����W�n�ł��B�Ή����m�F���ĉ������Bthis="<<NODE_INFO<<"");
        }
#endif
        _x_final  = _x;
        _y_final  = _y;
        _z_final  = _z;
        _rx_final = _rx;
        _ry_final = _ry;
        _rz_final = _rz;
        _x  = _x_local;
        _y  = _y_local;
        _z  = _z_local;
        _rx = _rx_local;
        _ry = _ry_local;
        _rz = _rz_local;
        _is_local = true;
    }

void GeometricActor::changeGeoFinal() {
#ifdef MY_DEBUG
    if (!_pActor_base) {
        throwCriticalException("changeGeoFinal() : �y��A�N�^�[������܂���B�m�F���ĉ������Bthis="<<NODE_INFO<<"");
    }
    if (!_is_local) {
        throwCriticalException("changeGeoFinal() : ���Ƀ��[�J�����W�n�ł��B�Ή����m�F���ĉ������Bthis="<<NODE_INFO<<"");
    }
#endif
    _x_local = _x;
    _y_local = _y;
    _z_local = _z;
    _rx_local = _rx;
    _ry_local = _ry;
    _rz_local = _rz;
    _x  = _x_final;
    _y  = _y_final;
    _z  = _z_final;
    _rx = _rx_final;
    _ry = _ry_final;
    _rz = _rz_final;
    _is_local = false;
}

//void GeometricActor::updateGeoFinalFromLocal() {
//
//}
void GeometricActor::appendChildAsFk( GeometricActor* prm_pGeoActor,
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
        throwCriticalException("GeometricActor::appendChildAsFk() : "<<
                "this="<<NODE_INFO<<" �́A_pFunc_calc_rot_mv_world_matrix �� nullptr�ׁ̈AFK�x�[�X�ƂȂ鎑�i������܂���");
    }
#endif
    appendChild( prm_pGeoActor);
    prm_pGeoActor->_pActor_base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
//    prm_pGeoActor->getLocusVehicle()->_rz_mv = prm_rz_init_local;
//    prm_pGeoActor->getLocusVehicle()->_ry_mv = prm_ry_init_local;

    prm_pGeoActor->changeGeoFinal();
}

int GeometricActor::isOutOfView() {
    //TODO:�A�C�f�B�A
    //�O��� isOutOfView() �l���o���Ă���
    //���肷�鎋����̖ʂ̗D�揇�ʂ�ς���ƁA�͂₭�Ȃ�邩���B
    //�O�񎋐���O�̖ʂ́A�����������O�̖ʂł���m������������

    //���E���a�i���f�����̂������j�̂ŁAPX_DX(1) ����ʓ��ɂ��邩�ǂ����𔻒肷��B
    //���f������ʓ��ɂ��邩�ǂ�������́AFigureActor �ŃI�[�o�[���C�h����Ă����ōs���B
    if (_offscreen_kind == -1) {
        const dxcoord bound = PX_DX(1); //���E���a
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
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

bool GeometricActor::isOutOfSpacetime() const {
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
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

void GeometricActor::defineRotMvWorldMatrix(void (*prm_pFunc)(const GeometricActor*, D3DXMATRIX&)) {
    _pFunc_calc_rot_mv_world_matrix = prm_pFunc;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GeometricActor::defineRotMvWorldMatrix_Billboard() {
    defineRotMvWorldMatrix(Util::setWorldMatrix_RzBxyzMv);
}

void GeometricActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
    _z = prm_pGeoElem->z;
}

void GeometricActor::setPositionAround(coord x, coord y, coord z, coord r) {
    double out_x, out_y, out_z;
    UTIL::getRndSpherCoord(r, out_x, out_y, out_z);
    setPosition(x+out_x, y+out_y, z+out_z);
}

void GeometricActor::setPositionAround(coord x, coord y, coord r) {
    double out_x, out_y;
    UTIL::getRndCircleCoord(r, out_x, out_y);
    setPosition(x+out_x, y+out_y);
}

void GeometricActor::setPositionAroundAt(const GeometricActor* prm_pActor, coord r) {
    setPositionAround(prm_pActor->_x, prm_pActor->_y, prm_pActor->_z, r);
}
void GeometricActor::setPositionAroundAt(const GeoElem* prm_pGeoElem, coord r) {
    setPositionAround(prm_pGeoElem->x, prm_pGeoElem->y, prm_pGeoElem->z, r);
}

void GeometricActor::setPositionByViewCoord(coord prm_view_x, coord prm_view_y, coord prm_depth) {
#ifdef MY_DEBUG
    if (_is_fix_2D) {
        throwCriticalException("GeometricActor::setPositionByViewCoord() : "<<
                "this="<<NODE_INFO<<" �́AFIX2D�A�N�^�[�̂��߁A�{���\�b�h�̎g�p�͕ςł͂Ȃ��ł����H�iViewCoord�������Ă��܂��j");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvViewCoordToWorld(prm_view_x, prm_view_y, prm_depth,
                                _x, _y, _z);
}

void GeometricActor::getWorldPosition(coord prm_depth, coord& out_world_x, coord& out_world_y, coord& out_world_z) {
#ifdef MY_DEBUG
    if (!_is_fix_2D) {
        throwCriticalException("GeometricActor::getWorldPosition() : "<<
                "this="<<NODE_INFO<<" �́A3D�A�N�^�[�̂��߁A�{���\�b�h�̎g�p�͕ςł͂Ȃ��ł����H�iWorldCoord�������Ă��܂��j");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvViewCoordToWorld(_x, _y, prm_depth,
                    out_world_x, out_world_y, out_world_z);
}

void GeometricActor::setPositionByWorldCoord(coord prm_world_x, coord prm_world_y, coord prm_world_z) {
#ifdef MY_DEBUG
    if (!_is_fix_2D) {
        throwCriticalException("GeometricActor::setPositionByWorldCoord() : "<<
                "this="<<NODE_INFO<<" �́A3D�A�N�^�[�̂��߁A�{���\�b�h�̎g�p�͕ςł͂Ȃ��ł����H�iWorldCoord�������Ă��܂��j");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvWorldCoordToView(prm_world_x, prm_world_y, prm_world_z,
                                _x, _y);
}

void GeometricActor::getViewPosition(coord& out_view_x, coord& out_view_y) {
#ifdef MY_DEBUG
    if (_is_fix_2D) {
        throwCriticalException("GeometricActor::getViewPosition() : "<<
                "this="<<NODE_INFO<<" �́AFIX2D�A�N�^�[�̂��߁A�{���\�b�h�̎g�p�͕ςł͂Ȃ��ł����H�iViewCoord�������Ă��܂��j");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvWorldCoordToView(_x, _y, _z,
                                out_view_x, out_view_y);
}

void GeometricActor::setFaceAngAs(const GeometricActor* prm_pActor) {
    setRxFaceAng(prm_pActor->_rx);
    setRyFaceAng(prm_pActor->_ry);
    setRzFaceAng(prm_pActor->_rz);
}
void GeometricActor::setFaceAngAs(const GeoElem* prm_pGeoElem) {
    setRxFaceAng(prm_pGeoElem->rx);
    setRyFaceAng(prm_pGeoElem->ry);
    setRzFaceAng(prm_pGeoElem->rz);
}

//void GeometricActor::setFaceAng(axis prm_axis, angle prm_face) {
//    _face[prm_axis] = UTIL::simplifyAng(prm_face);
//}

void GeometricActor::setRzFaceAng(angle prm_face) {
    _rz = UTIL::simplifyAng(prm_face);
}
void GeometricActor::setRyFaceAng(angle prm_face) {
    _ry = UTIL::simplifyAng(prm_face);
}
void GeometricActor::setRxFaceAng(angle prm_face) {
    _rx = UTIL::simplifyAng(prm_face);
}

void GeometricActor::setRzRyFaceAng(angle prm_rz_face, angle prm_ry_face) {
    setRzFaceAng(prm_rz_face);
    setRyFaceAng(prm_ry_face);
}

void GeometricActor::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
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
void GeometricActor::setFaceAngTwd(const GeometricActor* prm_pActor) {
    setFaceAngTwd(prm_pActor->_x, prm_pActor->_y, prm_pActor->_z);
}

void GeometricActor::onEnd() {
    _pFormation = nullptr;
}

GeometricActor::~GeometricActor() {
    GGAF_DELETE_NULLABLE(_pLocusVehicle);
    GGAF_DELETE_NULLABLE(_pCoordVehicle);
    GGAF_DELETE_NULLABLE(_pNaviVehicle);
    GGAF_DELETE_NULLABLE(_pScaler);
    GGAF_DELETE_NULLABLE(_pSeTransmitter);
}

void GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<isOutOfView()<<"/"<<isOutOfSpacetime()<<""<<DUMP_FLGS);
    GgafCore::Actor* pActor_tmp = _pChildFirst;
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

void GeometricActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<isOutOfView()<<"/"<<isOutOfSpacetime()<<""<<DUMP_FLGS);
    GgafCore::Actor* pActor_tmp = _pChildFirst;
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

