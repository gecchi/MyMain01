#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;



FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prmpKurokoA_target) :
        SplineKurokoLeader(prm_pManufacture, prmpKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}
FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(GgafDxKurokoA* prmpKurokoA_target,
                                                           SplineLine* prmpSpl,
                                                           frame prm_spent_frame,
                                                           angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prmpKurokoA_target) {  //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//������Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pFixedFrameSplManuf;

    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}

void FixedFrameSplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_X, coord& out_Y, coord& out_Z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedFrameSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::getPointCoord �|�C���g�̃C���f�b�N�X�I�[�o�[�B"<<
                                   "�⊮�_��="<<(_pFixedFrameSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double dx = _flip_X*pSpl->_X_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_X + _offset_X;
    double dy = _flip_Y*pSpl->_Y_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_Y + _offset_Y;
    double dz = _flip_Z*pSpl->_Z_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_Z + _offset_Z;
    //���̕�ԓ_�ior����_)�Ɉړ����p��������
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
            _X_begin = _pActor_target->_X;
            _Y_begin = _pActor_target->_Y;
            _Z_begin = _pActor_target->_Z;
        }
        //    ���s�ړ� �� Z����] �� Y����]
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_X = ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) *  _COS_RyMv_begin + dz*_SIN_RyMv_begin) + _X_begin;
        out_Y =  (dx*_SIN_RzMv_begin + dy* _COS_RzMv_begin)                                          + _Y_begin;
        out_Z = ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) + _Z_begin;
    } else if (_option == RELATIVE_COORD) {
        //���΍��W�^�[�Q�b�g
        out_X = dx + _X_begin;
        out_Y = dy + _Y_begin;
        out_Z = dz + _Z_begin;
    } else { //RELATIVE_DIRECTION
        //��΍��W�^�[�Q�b�g
        out_X = dx;
        out_Y = dy;
        out_Z = dz;
    }
}

void FixedFrameSplineKurokoLeader::start(SplinTraceOption prm_option) {
    if (_pFixedFrameSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _execute_frames = 0;
        SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
        double P0X = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X;
        double P0Y = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y;
        double P0Z = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z;
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
                                           0.0  , 0.0  , 0.0  ,
                                           P0X, P0Y, P0Z
                                      );
        } else if (_option == RELATIVE_COORD) {
            _distance_to_begin = UTIL::getDistance(
                                           0.0  , 0.0  , 0.0  ,
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
    }
}


void FixedFrameSplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;

        //���݂̓_INDEX
        _point_index = _execute_frames/_pFixedFrameSplManuf->_frame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_sp->_rnum) {
            //�I��
            _is_leading = false;
            return;
        }

        //�ς���
        if (_execute_frames % _pFixedFrameSplManuf->_frame_of_segment == 0) {
            coord X, Y, Z;
            getPointCoord(_point_index, X, Y, Z);
            pKurokoA_target->turnMvAngTwd(X, Y, Z,
                                          _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                          _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            //�ړ����x�ݒ�
            if (_point_index == 0) {
                //_paSPMvVeloTo[0] �͖���`�Ȃ̂ŁA���ʏ���
                if (pKurokoA_target->_veloMv <= 0) {
                    //�����A���ݑ��x��0�̏ꍇ�A�n�_�ɓ��B���邽�߂ɖ�����葬�x�� 1000 �ɂ���B
                    _TRACE_("[�x��]  FixedFrameSplineKurokoLeader::behave() "<<pKurokoA_target->_pActor->getName()<<" �̑��x�𖳗���葬�x�� 1000 �ɂ��܂����B�Ӑ}���Ă܂����H");
                    pKurokoA_target->setMvVelo(1000);
                } else {
                    //�Ȃɂ�����
                }
            } else {
                pKurokoA_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
            }
        }
        _execute_frames++;
    }

}
FixedFrameSplineKurokoLeader::~FixedFrameSplineKurokoLeader() {

}
