#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
FixedVelocitySplineKurokoStepper::FixedVelocitySplineKurokoStepper(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prmpKurokoA_target) :
        SplineKurokoStepper(prm_pManufacture, prmpKurokoA_target) {
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _exec_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}

FixedVelocitySplineKurokoStepper::FixedVelocitySplineKurokoStepper(GgafDxKurokoA* prmpKurokoA_target,
                                                                   SplineLine* prmpSpl,
                                                                   angvelo prm_angveloRzRyMv):
        SplineKurokoStepper(nullptr, prmpKurokoA_target) { //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�
    _pFixedVeloSplManuf = NEW FixedVelocitySplineManufacture(NEW SplineSource(prmpSpl), prm_angveloRzRyMv);
    _pFixedVeloSplManuf->calculate(); //�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pFixedVeloSplManuf; //��ꃁ���o�[�Z�b�g�B�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���

    _exec_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}

void FixedVelocitySplineKurokoStepper::start(SplinTraceOption prm_option) {
    if (_pFixedVeloSplManuf) {
        _is_stepping = true;
        _option = prm_option;
        _exec_fFrames = 0.0f;
        _fFrame_of_next = -0.00001f;
        _point_index = 0;
        SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
        double P0X = _flip_X * pSpl->_X_compute[0] * _pFixedVeloSplManuf->_rate_X + _offset_X;
        double P0Y = _flip_Y * pSpl->_Y_compute[0] * _pFixedVeloSplManuf->_rate_Y + _offset_Y;
        double P0Z = _flip_Z * pSpl->_Z_compute[0] * _pFixedVeloSplManuf->_rate_Z + _offset_Z;
        _X_begin = _pActor_target->_X;
        _Y_begin = _pActor_target->_Y;
        _Z_begin = _pActor_target->_Z;
        if (_option == RELATIVE_DIRECTION) {
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
            _distance_to_begin = UTIL::getDistance(
                                           0.0, 0.0, 0.0,
                                           P0X, P0Y, P0Z
                                      );
        } else if (_option == RELATIVE_COORD) {
            _distance_to_begin = UTIL::getDistance(
                                           0.0, 0.0, 0.0,
                                           P0X, P0Y, P0Z
                                      );
        } else { //ABSOLUTE_COORD
            _distance_to_begin = UTIL::getDistance(
                                    _pActor_target->_X,
                                    _pActor_target->_Y,
                                    _pActor_target->_Z,
                                    _X_begin,
                                    _Y_begin,
                                    _Z_begin
                                 );
       }
    } else {
        throwGgafCriticalException("SplineKurokoStepper::exec Manufacture������܂���B_pActor_target="<<_pActor_target->getName());
    }
}

void FixedVelocitySplineKurokoStepper::behave() {
    if (_is_stepping) {
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
        //�ς���
        if (_exec_fFrames >= _fFrame_of_next) {
            SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
            //���̕�ԓ_�ior����_)�Ɉړ����p��������
            double dx = _flip_X*pSpl->_X_compute[_point_index]*_pFixedVeloSplManuf->_rate_X + _offset_X;
            double dy = _flip_Y*pSpl->_Y_compute[_point_index]*_pFixedVeloSplManuf->_rate_Y + _offset_Y;
            double dz = _flip_Z*pSpl->_Z_compute[_point_index]*_pFixedVeloSplManuf->_rate_Z + _offset_Z;
            if (_option == RELATIVE_DIRECTION) {
                //    ���s�ړ� �� Z����] �� Y����] �� ���s�ړ����� tx,ty,tz
                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                pKurokoA_target->turnMvAngTwd(
                                    ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) *  _COS_RyMv_begin + dz * _SIN_RyMv_begin) + _X_begin,
                                     (dx * _SIN_RzMv_begin + dy *  _COS_RzMv_begin)                                            + _Y_begin,
                                    ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz * _COS_RyMv_begin) + _Z_begin,
                                    _pFixedVeloSplManuf->_angveloRzRyMv, 0,
                                    _pFixedVeloSplManuf->_turn_way,
                                    _pFixedVeloSplManuf->_turn_optimize);

            } else if (_option == RELATIVE_COORD) {
                //���΍��W�^�[�Q�b�g
                pKurokoA_target->turnMvAngTwd(
                                    dx + _X_begin,
                                    dy + _Y_begin,
                                    dz + _Z_begin,
                                    _pFixedVeloSplManuf->_angveloRzRyMv, 0,
                                    _pFixedVeloSplManuf->_turn_way,
                                    _pFixedVeloSplManuf->_turn_optimize);

            } else { //ABSOLUTE_COORD
                //��΍��W�^�[�Q�b�g
                pKurokoA_target->turnMvAngTwd(
                                    dx, dy, dz,
                                    _pFixedVeloSplManuf->_angveloRzRyMv, 0,
                                    _pFixedVeloSplManuf->_turn_way,
                                    _pFixedVeloSplManuf->_turn_optimize);

            }
            if (_point_index == 0) {
                //�n�_�܂łɕK�v�ȃt���[�����擾
                _fFrame_of_next = (float)(1.0*_distance_to_begin / _pFixedVeloSplManuf->_veloMvUnit);
            } else {
                //�n�_�ȊO�̏ꍇ���̕⊮�_�܂łɕK�v�ȃt���[�������X�V
                _fFrame_of_next = _pFixedVeloSplManuf->_paFrame_need_at[0] +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
            }
            _point_index++;
            if ( _point_index == pSpl->_rnum) {
                //�I��
                _is_stepping = false;
                return;
            }
        } else {
        }

        //�L�����̑��x��1000�Ȃ�΁A_exec_fFrames ++;
        //�L�����̑��x��2000�Ȃ��  _exec_fFrames += 2.0;
        //�L�����̑��x��500�Ȃ�΁A _exec_fFrames += 0.5
        _exec_fFrames += (1.0*pKurokoA_target->_veloMv / LEN_UNIT);
    }

}
FixedVelocitySplineKurokoStepper::~FixedVelocitySplineKurokoStepper() {
}
