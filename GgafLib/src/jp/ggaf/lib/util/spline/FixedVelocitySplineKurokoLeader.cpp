#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* const prm_pKuroko_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKuroko_target) {
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
    _ang_rz_mv_begin = prm_pKuroko_target->_ang_rz_mv;
    _ang_ry_mv_begin = prm_pKuroko_target->_ang_ry_mv;
}

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(GgafDxKuroko* const prm_pKuroko_target,
                                                                 SplineLine* prm_pSpl,
                                                                 angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKuroko_target) { //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�
    _pFixedVeloSplManuf = NEW FixedVelocitySplineManufacture(NEW SplineSource(prm_pSpl), prm_angveloRzRyMv);
    _pFixedVeloSplManuf->calculate(); //�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pFixedVeloSplManuf; //��ꃁ���o�[�Z�b�g�B�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���

    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
    _ang_rz_mv_begin = prm_pKuroko_target->_ang_rz_mv;
    _ang_ry_mv_begin = prm_pKuroko_target->_ang_ry_mv;
}
void FixedVelocitySplineKurokoLeader::getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedVeloSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedVelocitySplineKurokoLeader::getPointCoord �|�C���g�̃C���f�b�N�X�I�[�o�[�B"<<
                                   "�⊮�_��="<<(_pFixedVeloSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
    double dx = _flip_x*pSpl->_x_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_x + _offset_x;
    double dy = _flip_y*pSpl->_y_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_y + _offset_y;
    double dz = _flip_z*pSpl->_z_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_z + _offset_z;
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
            _sinRzMv_begin = ANG_SIN(pKuroko_target->_ang_rz_mv);
            _cosRzMv_begin = ANG_COS(pKuroko_target->_ang_rz_mv);
            _sinRyMv_begin = ANG_SIN(pKuroko_target->_ang_ry_mv);
            _cosRyMv_begin = ANG_COS(pKuroko_target->_ang_ry_mv);
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        //    ���s�ړ� �� Z����] �� Y����] �� ���s�ړ����� tx,ty,tz
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_x = ((dx * _cosRzMv_begin + dy * -_sinRzMv_begin) *  _cosRyMv_begin + dz * _sinRyMv_begin) + _x_start;
        out_y =  (dx * _sinRzMv_begin + dy *  _cosRzMv_begin)                                          + _y_start;
        out_z = ((dx * _cosRzMv_begin + dy * -_sinRzMv_begin) * -_sinRyMv_begin + dz * _cosRyMv_begin) + _z_start;

    } else if (_option == RELATIVE_COORD) {
        //���΍��W�^�[�Q�b�g
        if (_is_leading == false) {
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        out_x = dx + _x_start;
        out_y = dy + _y_start;
        out_z = dz + _z_start;
    } else { //ABSOLUTE_COORD
        //��΍��W�^�[�Q�b�g
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void FixedVelocitySplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pFixedVeloSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        _ang_rz_mv_begin = _pActor_target->getKuroko()->_ang_rz_mv;
        _ang_ry_mv_begin = _pActor_target->getKuroko()->_ang_ry_mv;
        restart();
    } else {
        throwGgafCriticalException("FixedVelocitySplineKurokoLeader::start Manufacture������܂���B_pActor_target="<<_pActor_target->getName());
    }
}
void FixedVelocitySplineKurokoLeader::restart() {
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B

    SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
    double p0x = _flip_x * pSpl->_x_compute[0] * _pFixedVeloSplManuf->_rate_x + _offset_x;
    double p0y = _flip_y * pSpl->_y_compute[0] * _pFixedVeloSplManuf->_rate_y + _offset_y;
    double p0z = _flip_z * pSpl->_z_compute[0] * _pFixedVeloSplManuf->_rate_z + _offset_z;
    if (!_is_fix_start_pos) {
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
    if (_option == RELATIVE_DIRECTION) {
        _sinRzMv_begin = ANG_SIN(_ang_rz_mv_begin);
        _cosRzMv_begin = ANG_COS(_ang_rz_mv_begin);
        _sinRyMv_begin = ANG_SIN(_ang_ry_mv_begin);
        _cosRyMv_begin = ANG_COS(_ang_ry_mv_begin);
        _distance_to_begin = UTIL::getDistance(
                                       0.0, 0.0, 0.0,
                                       p0x, p0y, p0z
                                  );
    } else if (_option == RELATIVE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                       0.0, 0.0, 0.0,
                                       p0x, p0y, p0z
                                  );
    } else { //ABSOLUTE_COORD
        _distance_to_begin = UTIL::getDistance(
                                (double)(_pActor_target->_x),
                                (double)(_pActor_target->_y),
                                (double)(_pActor_target->_z),
                                p0x, p0y, p0z
                             );
   }
}
void FixedVelocitySplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        //�ς���
        if (_leadning_fFrames >= _fFrame_of_next) {
            _point_index++;
            if ( _point_index == _pFixedVeloSplManuf->_sp->_rnum) {
                if (_cnt_loop == _max_loop) {
                    //�I��
                    _is_leading = false;
                    return;
                } else {
                    //���[�v
                    _cnt_loop++;
                    restart();
                    _point_index++;
                }
            }
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            pKuroko_target->turnMvAngTwd(x, y, z,
                                         _pFixedVeloSplManuf->_angveloRzRyMv, 0,
                                         _pFixedVeloSplManuf->_turn_way,
                                         _pFixedVeloSplManuf->_turn_optimize);
            if (_point_index == 0) {
                //�ŏ��̕K�R�u���C�N�A�n�_�֍s��
                //�n�_�܂łɕK�v�ȃt���[�����擾
                _fFrame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit);
            } else {
                //�n�_�ȊO�̏ꍇ���̕⊮�_�܂łɕK�v�ȃt���[�������X�V
                _fFrame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
             }
        }
        //�L�����̑��x��1000�Ȃ�΁A_leadning_fFrames ++;
        //�L�����̑��x��2000�Ȃ��  _leadning_fFrames += 2.0;
        //�L�����̑��x��500�Ȃ�΁A _leadning_fFrames += 0.5
//        _leadning_fFrames += (1.0*pKuroko_target->_velo_mv / LEN_UNIT);
        _leadning_fFrames += (pKuroko_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocitySplineKurokoLeader::~FixedVelocitySplineKurokoLeader() {
}
