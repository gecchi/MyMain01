#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;



FixedFrameSplineSequence::FixedFrameSplineSequence(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prmpKurokoA_target) :
        SplineSequence(prm_pManufacture, prmpKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}
FixedFrameSplineSequence::FixedFrameSplineSequence(GgafDxKurokoA* prmpKurokoA_target,
                                                 SplineLine* prmpSpl,
                                                 frame prm_spent_frame,
                                                 angvelo prm_angveloRzRyMv):
        SplineSequence(NULL, prmpKurokoA_target) {  //NULL�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//������Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pFixedFrameSplManuf;

    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}


void FixedFrameSplineSequence::exec(SplinTraceOption prm_option) {
    if (_pFixedFrameSplManuf) {

        _is_executing = true;
        _option = prm_option;
        _execute_frames = 0;
        SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
        if (_option == RELATIVE_DIRECTION) {
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X - _pActor_target->_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y - _pActor_target->_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z - _pActor_target->_Z;
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = GgafDxUtil::SIN[pKurokoA_target->_angRzMv/SANG_RATE];
            _COS_RzMv_begin = GgafDxUtil::COS[pKurokoA_target->_angRzMv/SANG_RATE];
            _SIN_RyMv_begin = GgafDxUtil::SIN[pKurokoA_target->_angRyMv/SANG_RATE];
            _COS_RyMv_begin = GgafDxUtil::COS[pKurokoA_target->_angRyMv/SANG_RATE];
        } else if (_option == RELATIVE_COORD) {
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X - _pActor_target->_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y - _pActor_target->_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z - _pActor_target->_Z;
        } else { //ABSOLUTE_COORD
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z;

        }
    }
}


void FixedFrameSplineSequence::behave() {
    if (_is_executing) {
        SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;

        //���݂̓_INDEX
        int point_index = _execute_frames/_pFixedFrameSplManuf->_frame_of_segment;
        if ( point_index == pSpl->_rnum) {
            //�I��
            _is_executing = false;
            return;
        }

        //�ς���
        if (_execute_frames % _pFixedFrameSplManuf->_frame_of_segment == 0) {
            double dx = _flip_X*pSpl->_X_compute[point_index]*_pFixedFrameSplManuf->_rate_X + _offset_X;
            double dy = _flip_Y*pSpl->_Y_compute[point_index]*_pFixedFrameSplManuf->_rate_Y + _offset_Y;
            double dz = _flip_Z*pSpl->_Z_compute[point_index]*_pFixedFrameSplManuf->_rate_Z + _offset_Z;

            //���̕�ԓ_�ior����_)�Ɉړ����p��������
            if (_option == RELATIVE_DIRECTION) {
                //    ���s�ړ� �� Z����] �� Y����]
                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                pKurokoA_target->execTurnMvAngSequence(
                                ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * _COS_RyMv_begin  + dz*_SIN_RyMv_begin) - _X_begin,
                                 (dx*_SIN_RzMv_begin + dy* _COS_RzMv_begin) - _Y_begin,
                                ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) - _Z_begin,
                                _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            } else if (_option == RELATIVE_COORD) {
                //���΍��W�^�[�Q�b�g
                pKurokoA_target->execTurnMvAngSequence(
                                dx - _X_begin, dy - _Y_begin, dz - _Z_begin,
                                _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            } else { //RELATIVE_DIRECTION
                //��΍��W�^�[�Q�b�g
                pKurokoA_target->execTurnMvAngSequence(
                                dx, dy, dz,
                                _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);
            }

            //�ړ����x�ݒ�
            if (point_index == 0) {
                //_paSPMvVeloTo[0] �͖���`�Ȃ̂ŁA���ʏ���
                if (pKurokoA_target->_veloMv <= 0) {
                    pKurokoA_target->setMvVelo(1000);
                } else {
                    //�Ȃɂ�����
                }
            } else {
                pKurokoA_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[point_index]);
            }
        }
        _execute_frames++;
    }

}
FixedFrameSplineSequence::~FixedFrameSplineSequence() {

}
