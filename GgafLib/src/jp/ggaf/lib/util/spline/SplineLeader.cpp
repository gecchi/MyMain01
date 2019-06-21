#include "jp/ggaf/lib/util/spline/SplineLeader.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"



using namespace GgafLib;

SplineLeader::SplineLeader(SplineManufacture* prm_pManufacture, GgafDx::GeometricActor* prm_pActor_target) :
        GgafCore::Object() {
    _pManufacture = prm_pManufacture;
    if (!_pManufacture->_is_calculated) {
        _pManufacture->calculate();
    }
    _pActor_target = prm_pActor_target;
    _option = ABSOLUTE_COORD;
    _x_start_in_loop = 0;
    _y_start_in_loop = 0;
    _z_start_in_loop = 0;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
    _sinRx_begin = 0.0f;
    _cosRx_begin = 0.0f;
    _sinRz_begin = 0.0f;
    _cosRz_begin = 0.0f;
    _sinRy_begin = 0.0f;
    _cosRy_begin = 0.0f;

    _was_started = false;
    _is_leading = false;
    _distance_to_begin = 0;
    _cnt_loop = 0;
    _max_loop = 1;
    _is_force_start_pos = false;
    _is_fix_pos = false;
    _is_force_start_ang = false;
//    _is_loop_ang_by_face = true;
    _turn_smooth = false;
}

void SplineLeader::getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pManufacture->_pSpl->_rnum) {
        throwCriticalException("�|�C���g�̃C���f�b�N�X�I�[�o�[�B"
                                   "�⊮�_��="<<(_pManufacture->_pSpl->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    const SplineSource* const pSpl = _pManufacture->_pSpl;
    const double dx = _flip_x*pSpl->_x_compute[prm_point_index]*_pManufacture->_rate_x + _offset_x;
    const double dy = _flip_y*pSpl->_y_compute[prm_point_index]*_pManufacture->_rate_y + _offset_y;
    const double dz = _flip_z*pSpl->_z_compute[prm_point_index]*_pManufacture->_rate_z + _offset_z;
    //���̕�ԓ_�ior����_)�Ɉړ����p��������
    if (_option == RELATIVE_COORD_DIRECTION) {
        if (_is_leading) {
            //�͎Ԃ��񂪐擱��(leading��)
            //start����Ă���̂ŁA�����̕�ԓ_���W���m�肵�Ă���
            //    ���s�ړ� �� X����] �� Z����] �� Y����]
            // | cosRz*cosRy                                                                       sinRz                                       cosRz*-sinRy                                                                        0 |
            // | cosRx*-sinRz*cosRy + sinRx*sinRy                                                  cosRx*cosRz                                 cosRx*-sinRz*-sinRy + sinRx*cosRy                                                   0 |
            // | -sinRx*-sinRz*cosRy + cosRx*sinRy                                                 -sinRx*cosRz                                -sinRx*-sinRz*-sinRy + cosRx*cosRy                                                  0 |
            // | (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*cosRy + ((dy*sinRx + dz*cosRx))*sinRy  (dx*sinRz + (dy*cosRx + dz*-sinRx)*cosRz)   (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*-sinRy + ((dy*sinRx + dz*cosRx))*cosRy   1 |
            const double dx_cosRz_begin = dx*_cosRz_begin;
            const double dy_cosRx_begin = dy*_cosRx_begin;
            const double dz_sinRx_begin = dz*_sinRx_begin;
            const double dy_sinRx_begin = dy*_sinRx_begin;
            const double dz_cosRx_begin = dz*_cosRx_begin;
            out_x = ((dx_cosRz_begin  + (dy_cosRx_begin + -dz_sinRx_begin)*-_sinRz_begin)* _cosRy_begin + ((dy_sinRx_begin + dz_cosRx_begin))*_sinRy_begin ) + _x_start_in_loop;
            out_y = ((dx*_sinRz_begin + (dy_cosRx_begin + -dz_sinRx_begin)* _cosRz_begin)                                                                  ) + _y_start_in_loop;
            out_z = ((dx_cosRz_begin  + (dy_cosRx_begin + -dz_sinRx_begin)*-_sinRz_begin)*-_sinRy_begin + ((dy_sinRx_begin + dz_cosRx_begin))*_cosRy_begin ) + _z_start_in_loop;
        } else {
            //�͎Ԃ��񂪐擱���Ă��Ȃ�(not leading ��)
            //�܂� start ����Ă��Ȃ��̂ŁA�����̕�ԓ_���W�����m��
            //���̏ꍇ�A���ɍ��R�R�� start ���ꂽ�ꍇ�̍��W���v�Z���ĕԂ�
            const float sinRx_now = ANG_SIN(_pActor_target->_rx);
            const float cosRx_now = ANG_COS(_pActor_target->_rx);
            const float sinRz_now = ANG_SIN(_pActor_target->_rz);
            const float cosRz_now = ANG_COS(_pActor_target->_rz);
            const float sinRy_now = ANG_SIN(_pActor_target->_ry);
            const float cosRy_now = ANG_COS(_pActor_target->_ry);
            const double dx_cosRz_now = dx*cosRz_now;
            const double dy_cosRx_now = dy*cosRx_now;
            const double dz_sinRx_now = dz*sinRx_now;
            const double dy_sinRx_now = dy*sinRx_now;
            const double dz_cosRx_now = dz*cosRx_now;
            //    ���s�ړ� �� X����] �� Z����] �� Y����]
            if (_is_force_start_pos) {
                out_x = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)* cosRy_now + ((dy_sinRx_now + dz_cosRx_now))*sinRy_now ) + 0;
                out_y = ((dx*sinRz_now + (dy_cosRx_now + -dz_sinRx_now)* cosRz_now)                                                        ) + 0;
                out_z = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)*-sinRy_now + ((dy_sinRx_now + dz_cosRx_now))*cosRy_now ) + 0;
            } else {
                out_x = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)* cosRy_now + ((dy_sinRx_now + dz_cosRx_now))*sinRy_now ) + _pActor_target->_x;
                out_y = ((dx*sinRz_now + (dy_cosRx_now + -dz_sinRx_now)* cosRz_now)                                                        ) + _pActor_target->_y;
                out_z = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)*-sinRy_now + ((dy_sinRx_now + dz_cosRx_now))*cosRy_now ) + _pActor_target->_z;
            }


        }
    } else if (_option == RELATIVE_COORD) {
        //���΍��W�^�[�Q�b�g
        if (_is_leading) {
            //�͎Ԃ��񂪐擱��(leading��)
            out_x = dx + _x_start_in_loop;
            out_y = dy + _y_start_in_loop;
            out_z = dz + _z_start_in_loop;
        } else {
            //�͎Ԃ��񂪐擱���Ă��Ȃ�(not leading ��)
            if (_is_force_start_pos) {
                out_x = dx + 0;
                out_y = dy + 0;
                out_z = dz + 0;
            } else {
                out_x = dx + _pActor_target->_x;
                out_y = dy + _pActor_target->_y;
                out_z = dz + _pActor_target->_z;
            }
        }
    } else { //RELATIVE_COORD_DIRECTION
        //��΍��W�^�[�Q�b�g
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void SplineLeader::restart() {
    const SplineSource* const pSpl = _pManufacture->_pSpl;
    const double p0x = _flip_x * pSpl->_x_compute[0] * _pManufacture->_rate_x + _offset_x;
    const double p0y = _flip_y * pSpl->_y_compute[0] * _pManufacture->_rate_y + _offset_y;
    const double p0z = _flip_z * pSpl->_z_compute[0] * _pManufacture->_rate_z + _offset_z;
//    if (_cnt_loop >= 2) {
//        //�Q���ڈȍ~�� setStartPosition() ���ݒ肳��Ă��Ă��A���͂͂Ȃ��Ȃ�B
//        _is_force_start_pos = false;
//        _is_force_start_ang = false;
//    }
    if (_is_fix_pos) {
        //�J�n���W�͉����[�v���Ă��Œ�B
    } else {
        if (_is_force_start_pos) {
            //�J�n���W(_x_start_in_loop, _y_start_in_loop, _z_start_in_loop)�́A
            //�ʓr setStartPosition() �ɂ��ݒ�ς�
            _is_force_start_pos = false;
        } else {
            if (_cnt_loop == 1) {
                //�P�T�ڂ͐��ɍ��̍��W���J�n���W
                _x_start_in_loop = _pActor_target->_x;
                _y_start_in_loop = _pActor_target->_y;
                _z_start_in_loop = _pActor_target->_z;
            } else {
                //�Q�T�ڈȍ~�́A�J�n���W�́A�O��̘_���ŏI���W���A�J�n���W
                coord end_x, end_y, end_z;
                getPointCoord(getPointNum()-1, end_x, end_y, end_z);
                _x_start_in_loop = end_x;
                _y_start_in_loop = end_y;
                _z_start_in_loop = end_z;
            }
        }
    }

    if (_is_force_start_ang) {
        //_rz_mv_start, _ry_mv_start�A��
        //�ʓr setStartAngle() �ɂ��ݒ�ς݂̏ꍇ�́A
        //�A�N�^�[�̍��̌����Ɋ֌W�Ȃ��A�ݒ�ς݂̌����ƂȂ�
        _is_force_start_ang = false;
    } else {
        if (_cnt_loop == 1) {
//            if (_is_loop_ang_by_face) {
//                //setLoopAngleByFaceAng() �ݒ�ς݂̏ꍇ�i�f�t�H���g)
                //�P�T�ڂ̓A�N�^�[�����ɍ������Ă���������J�n�ړ�����
                angle rx_mv_start = _pActor_target->_rx;
                angle rz_mv_start = _pActor_target->_rz;
                angle ry_mv_start = _pActor_target->_ry;
                _sinRx_begin = ANG_SIN(rx_mv_start);
                _cosRx_begin = ANG_COS(rx_mv_start);
                _sinRz_begin = ANG_SIN(rz_mv_start);
                _cosRz_begin = ANG_COS(rz_mv_start);
                _sinRy_begin = ANG_SIN(ry_mv_start);
                _cosRy_begin = ANG_COS(ry_mv_start);
//            } else {
//                //setLoopAngleByMvAng() �ݒ�ς݂̏ꍇ
//                //�P�T�ڂ̓A�N�^�[�̈ړ��������J�n�ړ�����
//                GgafDx::Rikisha* pActorRikisha = _pActor_target->callRikisha();
//                angle rx_mv_start = D0ANG;
//                angle rz_mv_start = pActorRikisha->_rz_mv;
//                angle ry_mv_start = pActorRikisha->_ry_mv;
//                _sinRx_begin = ANG_SIN(rx_mv_start);
//                _cosRx_begin = ANG_COS(rx_mv_start);
//                _sinRz_begin = ANG_SIN(rz_mv_start);
//                _cosRz_begin = ANG_COS(rz_mv_start);
//                _sinRy_begin = ANG_SIN(ry_mv_start);
//                _cosRy_begin = ANG_COS(ry_mv_start);
//            }
        } else {
            //�Q�T�ڈȍ~�́A���̂܂�;
        }
    }

//    if (_option == RELATIVE_COORD_DIRECTION) {
//        _distance_to_begin = UTIL::getDistance(0.0, 0.0, 0.0,
//                                               p0x, p0y, p0z );
//    } else if (_option == RELATIVE_COORD) {
//        _distance_to_begin = UTIL::getDistance(0.0, 0.0, 0.0,
//                                               p0x, p0y, p0z );
//    } else { //ABSOLUTE_COORD
//        _distance_to_begin = UTIL::getDistance(
//                                (double)(_pActor_target->_x),
//                                (double)(_pActor_target->_y),
//                                (double)(_pActor_target->_z),
//                                p0x, p0y, p0z
//                             );
//   }
    if (_option == ABSOLUTE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                (double)(_pActor_target->_x),
                                (double)(_pActor_target->_y),
                                (double)(_pActor_target->_z),
                                p0x, p0y, p0z
                             );
    } else {
        _distance_to_begin = 0;
    }
}

void SplineLeader::setManufacture(SplineManufacture* prm_pManufacture) {
    _pManufacture = prm_pManufacture;
    _pActor_target = nullptr;
    _option = ABSOLUTE_COORD;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
    _was_started = false;
    _is_leading = false;
}

void SplineLeader::adjustCoordOffset(coord prm_offset_x, coord prm_offset_y, coord prm_offset_z) {
    _offset_x = prm_offset_x;
    _offset_y = prm_offset_y;
    _offset_z = prm_offset_z;
}

void SplineLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pManufacture) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        restart();
    } else {
        throwCriticalException("Manufacture������܂���B_pActor_target="<<_pActor_target->getName());
    }
}

void SplineLeader::stop() {
    _is_leading = false;
}

void SplineLeader::setAbsoluteBeginCoord() {
    SplineLeader::getPointCoord(0, _pActor_target->_x, _pActor_target->_y, _pActor_target->_z);
}

coord SplineLeader::getSegmentDistance(int prm_index) {
#ifdef MY_DEBUG
    if (prm_index < 0 || prm_index > (_pManufacture->_pSpl->_rnum -1)) {
        throwCriticalException("prm_index="<<prm_index<<" �́A�͈͊O�ł�._pActor_target="<< _pActor_target <<"["<< _pActor_target->getName() <<"]");
    }
#endif
    if (prm_index == 0) {
        return _distance_to_begin;
    } else {
        return _pManufacture->_paDistance_to[prm_index];
    }
}

coord SplineLeader::getTotalDistance() {
    return _pManufacture->_total_distance + _distance_to_begin;
}

int SplineLeader::getPointNum() {
    return _pManufacture->_pSpl->_rnum;
}

void SplineLeader::setStartAngle(angle prm_rx, angle prm_ry, angle prm_rz) {
    _is_force_start_ang = true;
    angle rx_mv_start = UTIL::simplifyAng(prm_rx);
    angle rz_mv_start = UTIL::simplifyAng(prm_rz);
    angle ry_mv_start = UTIL::simplifyAng(prm_ry);
    _sinRx_begin = ANG_SIN(rx_mv_start);
    _cosRx_begin = ANG_COS(rx_mv_start);
    _sinRz_begin = ANG_SIN(rz_mv_start);
    _cosRz_begin = ANG_COS(rz_mv_start);
    _sinRy_begin = ANG_SIN(ry_mv_start);
    _cosRy_begin = ANG_COS(ry_mv_start);
}

SplineLeader::~SplineLeader() {
//    if (_is_created_pManufacture) {
//        SplineSource* pSplSrc = _pManufacture->_pSplSrc;
//        GGAF_DELETE(pSplSrc);
//        GGAF_DELETE(_pManufacture);
//    }
}
