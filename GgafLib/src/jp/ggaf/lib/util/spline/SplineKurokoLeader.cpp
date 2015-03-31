#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineKurokoLeader::SplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* prm_pKuroko) :
        GgafObject() {
    _pManufacture = prm_pManufacture;
    _pActor_target = prm_pKuroko->_pActor;
    _option = ABSOLUTE_COORD;
    _x_start = 0;
    _y_start = 0;
    _z_start = 0;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;

    _was_started = false;
    _is_leading = false;
    if (prm_pManufacture) {
        _is_created_pManufacture = false;
    } else {
        _is_created_pManufacture = true;
    }
    _distance_to_begin = 0;
    _cnt_loop = 0;
    _max_loop = 1;
    _is_fix_start_pos = false;

    _is_fix_start_mv_ang = false;
    _ang_rz_mv_start = prm_pKuroko->_ang_rz_mv;
    _ang_ry_mv_start = prm_pKuroko->_ang_ry_mv;
}

void SplineKurokoLeader::getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pManufacture->_sp->_rnum) {
        throwGgafCriticalException("SplineKurokoLeader::getPointCoord �|�C���g�̃C���f�b�N�X�I�[�o�[�B"<<
                                   "�⊮�_��="<<(_pManufacture->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    const SplineLine* const pSpl = _pManufacture->_sp;
    const double dx = _flip_x*pSpl->_x_compute[prm_point_index]*_pManufacture->_rate_x + _offset_x;
    const double dy = _flip_y*pSpl->_y_compute[prm_point_index]*_pManufacture->_rate_y + _offset_y;
    const double dz = _flip_z*pSpl->_z_compute[prm_point_index]*_pManufacture->_rate_z + _offset_z;
    //���̕�ԓ_�ior����_)�Ɉړ����p��������
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading) {
            //���߂��񂪐擱��(leading��)
            //start����Ă���̂ŁA�����̕�ԓ_���W���m�肵�Ă���
            //    ���s�ړ� �� Z����] �� Y����]
            //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
            //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
            //    | sinRy                                  , 0                    , cosRy                                   , 0 |
            //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
            out_x = ((dx*_cosRzMv_begin + dy*-_sinRzMv_begin) *  _cosRyMv_begin + dz*_sinRyMv_begin) + _x_start;
            out_y =  (dx*_sinRzMv_begin + dy* _cosRzMv_begin)                                        + _y_start;
            out_z = ((dx*_cosRzMv_begin + dy*-_sinRzMv_begin) * -_sinRyMv_begin + dz*_cosRyMv_begin) + _z_start;
        } else {
            //���߂��񂪐擱���Ă��Ȃ�(not leading ��)
            //�܂� start ����Ă��Ȃ��̂ŁA�����̕�ԓ_���W�����m��
            //���̏ꍇ�A���ɍ��R�R�� start ���ꂽ�ꍇ�̍��W���v�Z���ĕԂ�
            const GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
            const float sinRzMv_now = ANG_SIN(pKuroko_target->_ang_rz_mv);
            const float cosRzMv_now = ANG_COS(pKuroko_target->_ang_rz_mv);
            const float sinRyMv_now = ANG_SIN(pKuroko_target->_ang_ry_mv);
            const float cosRyMv_now = ANG_COS(pKuroko_target->_ang_ry_mv);
            //    ���s�ړ� �� Z����] �� Y����]
            //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
            //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
            //    | sinRy                                  , 0                    , cosRy                                   , 0 |
            //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
            if (_is_fix_start_pos) {
                out_x = ((dx*cosRzMv_now + dy*-sinRzMv_now) *  cosRyMv_now + dz*sinRyMv_now) + 0;
                out_y =  (dx*sinRzMv_now + dy* cosRzMv_now)                                  + 0;
                out_z = ((dx*cosRzMv_now + dy*-sinRzMv_now) * -sinRyMv_now + dz*cosRyMv_now) + 0;
            } else {
                out_x = ((dx*cosRzMv_now + dy*-sinRzMv_now) *  cosRyMv_now + dz*sinRyMv_now) + _pActor_target->_x;
                out_y =  (dx*sinRzMv_now + dy* cosRzMv_now)                                  + _pActor_target->_y;
                out_z = ((dx*cosRzMv_now + dy*-sinRzMv_now) * -sinRyMv_now + dz*cosRyMv_now) + _pActor_target->_z;
            }


        }
    } else if (_option == RELATIVE_COORD) {
        //���΍��W�^�[�Q�b�g
        if (_is_leading) {
            //���߂��񂪐擱��(leading��)
            out_x = dx + _x_start;
            out_y = dy + _y_start;
            out_z = dz + _z_start;
        } else {
            //���߂��񂪐擱���Ă��Ȃ�(not leading ��)
            if (_is_fix_start_pos) {
                out_x = dx + 0;
                out_y = dy + 0;
                out_z = dz + 0;
            } else {
                out_x = dx + _pActor_target->_x;
                out_y = dy + _pActor_target->_y;
                out_z = dz + _pActor_target->_z;
            }
        }
    } else { //RELATIVE_DIRECTION
        //��΍��W�^�[�Q�b�g
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void SplineKurokoLeader::restart() {
    const SplineLine* const pSpl = _pManufacture->_sp;
    const double p0x = _flip_x * pSpl->_x_compute[0] * _pManufacture->_rate_x + _offset_x;
    const double p0y = _flip_y * pSpl->_y_compute[0] * _pManufacture->_rate_y + _offset_y;
    const double p0z = _flip_z * pSpl->_z_compute[0] * _pManufacture->_rate_z + _offset_z;
    if (_cnt_loop >= 2) {
        //�Q���ڈȍ~�� fixStartPosition() ���ݒ肳��Ă��Ă��A���͂͂Ȃ��Ȃ�B
        _is_fix_start_pos = false;
        _is_fix_start_mv_ang = false;
    }
    if (_is_fix_start_pos) {
        //�J�n���W(_x_start, _y_start, _z_start)�́A
        //�ʓr fixStartPosition() �ɂ��ݒ�ς�
    } else {
        if (_cnt_loop == 1) {
            //�P�T�ڂ͐��ɍ��̍��W���J�n���W
            _x_start = _pActor_target->_x;
            _y_start = _pActor_target->_y;
            _z_start = _pActor_target->_z;
        } else {
            //�Q�T�ڈȍ~�́A�J�n���W�́A�O��̘_���ŏI���W���A�J�n���W
            coord end_x, end_y, end_z;
            getPointCoord(getPointNum()-1, end_x, end_y, end_z);
            _x_start = end_x;
            _y_start = end_y;
            _z_start = end_z;
        }
    }

    if (_is_fix_start_mv_ang) {
        //_rz_mv_start, _ry_mv_start�A��
        //�ʓr fixStartMvAngle() �ɂ��ݒ�ς�
        _sinRzMv_begin = ANG_SIN(_ang_rz_mv_start);
        _cosRzMv_begin = ANG_COS(_ang_rz_mv_start);
        _sinRyMv_begin = ANG_SIN(_ang_ry_mv_start);
        _cosRyMv_begin = ANG_COS(_ang_ry_mv_start);
    } else {
        if (_cnt_loop == 1) {
            //�P�T�ڂ͐��ɍ��̈ړ��������J�n�ړ�����
            _ang_rz_mv_start = _pActor_target->getKuroko()->_ang_rz_mv;
            _ang_ry_mv_start = _pActor_target->getKuroko()->_ang_ry_mv;
            _sinRzMv_begin = ANG_SIN(_ang_rz_mv_start);
            _cosRzMv_begin = ANG_COS(_ang_rz_mv_start);
            _sinRyMv_begin = ANG_SIN(_ang_ry_mv_start);
            _cosRyMv_begin = ANG_COS(_ang_ry_mv_start);
        } else {
            //�Q�T�ڈȍ~�́A���̂܂�;
        }
    }

    if (_option == RELATIVE_DIRECTION) {
        _distance_to_begin = UTIL::getDistance(0.0, 0.0, 0.0,
                                               p0x, p0y, p0z );
    } else if (_option == RELATIVE_COORD) {
        _distance_to_begin = UTIL::getDistance(0.0, 0.0, 0.0,
                                               p0x, p0y, p0z );
    } else { //ABSOLUTE_COORD
        _distance_to_begin = UTIL::getDistance(
                                (double)(_pActor_target->_x),
                                (double)(_pActor_target->_y),
                                (double)(_pActor_target->_z),
                                p0x, p0y, p0z
                             );
   }
}
void SplineKurokoLeader::setManufacture(SplineManufacture* prm_pManufacture) {
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

void SplineKurokoLeader::adjustCoordOffset(coord prm_offset_x, coord prm_offset_y, coord prm_offset_z) {
    _offset_x = prm_offset_x;
    _offset_y = prm_offset_y;
    _offset_z = prm_offset_z;
}

void SplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pManufacture) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        restart();
    } else {
        throwGgafCriticalException("SplineKurokoLeader::start Manufacture������܂���B_pActor_target="<<_pActor_target->getName());
    }
}
void SplineKurokoLeader::stop() {
    _is_leading = false;
}


void SplineKurokoLeader::setAbsoluteBeginCoord() {
    SplineKurokoLeader::getPointCoord(0, _pActor_target->_x, _pActor_target->_y, _pActor_target->_z);
}

coord SplineKurokoLeader::getSegmentDistance(int prm_index) {
#ifdef MY_DEBUG
    if (prm_index < 0 || prm_index > (_pManufacture->_sp->_rnum -1)) {
        throwGgafCriticalException("SplineKurokoLeader::getSegmentDistance("<<prm_index<<") �́A�͈͊O�ł�._pActor_target="<< _pActor_target <<"["<< _pActor_target->getName() <<"]");
    }
#endif
    if (prm_index == 0) {
        return _distance_to_begin;
    } else {
        return _pManufacture->_paDistance_to[prm_index];
    }
}

coord SplineKurokoLeader::getTotalDistance() {
    return _pManufacture->_total_distance + _distance_to_begin;
}

int SplineKurokoLeader::getPointNum() {
    return _pManufacture->_sp->_rnum;
}
SplineKurokoLeader::~SplineKurokoLeader() {
    if (_is_created_pManufacture) {
        SplineSource* pSplSrc = _pManufacture->_pSplSrc;
        GGAF_DELETE(pSplSrc);
        GGAF_DELETE(_pManufacture);
    }
}
