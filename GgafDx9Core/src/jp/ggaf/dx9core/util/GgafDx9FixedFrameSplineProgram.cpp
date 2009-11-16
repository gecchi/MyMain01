#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9FixedFrameSplineProgram::GgafDx9FixedFrameSplineProgram() : GgafDx9SplineProgram() {

    _SPframe_segment = 0;
    _paDistace_to = NULL;
    _paSPMoveVelocityTo = NULL;
    _is_executing = false;
    _option = 0;

    _X_relative = 0;
    _Y_relative = 0;
    _Z_relative = 0;

    _angFaceMove = ANGLE360;
}

GgafDx9FixedFrameSplineProgram::GgafDx9FixedFrameSplineProgram(double prm_paaCriteriaPoints[][3],
                                                               int prm_point_num,
                                                               double prm_accuracy,
                                                               DWORD prm_spent_frame,
                                                               angvelo prm_angFaceMove )

                                        : GgafDx9SplineProgram(prm_paaCriteriaPoints,
                                                               prm_point_num,
                                                               prm_accuracy)      {
    _spent_frame = prm_spent_frame;
    _angFaceMove = prm_angFaceMove;
    init();
}

GgafDx9FixedFrameSplineProgram::GgafDx9FixedFrameSplineProgram(GgafDx9Spline3D* prm_sp,
                                                               DWORD prm_spent_frame,
                                                               angvelo prm_angFaceMove) : GgafDx9SplineProgram(prm_sp) {
    _spent_frame = prm_spent_frame;
    _angFaceMove = prm_angFaceMove;
    init();
}


void GgafDx9FixedFrameSplineProgram::init() {
    //�e�_�̎��_�́A�����Ƒ��x��\�ߑS�����߂Ă���

    // prm_paaCriteriaPoints[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // prm_point_num = 3          //��_�̐�
    // prm_accuracy = 0.25(=1/4)  //�⊮�_���x
    // prm_spent_frame = 120      //��₷�t���[��
    // �̏ꍇ�A���}�̂悤�ɂȂ�܂��B
    //
    // X:��_
    // o:��_�Ԃ̕⊮�_�i�X�v���C���Ȑ��ʉߓ_�j
    // X--o: �ړ��\��̍��W��
    // _paDistace_to[] : ���̕⊮�_�܂ł̋���
    // paSPMoveVelocityTo[] : ���̕⊮�_���B�ɕK�v�ȑ��x
    //
    // sp._rnum �͍��v�̓_�̐���Ԃ��B���������� sp._rnum = 9 �ɂȂ�B
    // prm_accuracy ���Y��ȕ����ɂȂ�Ȃ��ꍇ�A��_��ɕ⊮�_���J�邩�Ƃ��A�S�R�킩��Ȃ��̂ŁAsp._rnum��K���g�p����
    // ���}���Y��ɏd�Ȃ����ꍇ�̐}�ł���B
    //
    //      v = paSPMoveVelocityTo[1]                              v = paSPMoveVelocityTo[8]
    //               paSPDistaceTo[1]     paSPDistaceTo[5]          paSPDistaceTo[8]
    //                    ||                     ||                         ||
    //                   <-->                 <------>                    <----->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    // (prm_paaCriteriaPoints[0][0],   (prm_paaCriteriaPoints[1][0],    (prm_paaCriteriaPoints[2][0],
    //  prm_paaCriteriaPoints[0][1],    prm_paaCriteriaPoints[1][1],     prm_paaCriteriaPoints[2][1],
    //  prm_paaCriteriaPoints[0][2])    prm_paaCriteriaPoints[1][2])     prm_paaCriteriaPoints[2][2])
    //   = (1000,2000,3000)             = (2000,1000,0)                    = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                                 120Frame��₵�Ĉړ�(=prm_spent_frame)
    //                  <-->
    //                  frm_segment = �P��Ԃ� 120/8 Frame = prm_spent_frame / (sp._rnum-1);

    //�P��Ԃ̎g�p�\�t���[��
    _SPframe_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_SPframe_segment < 1) {
        _SPframe_segment = 1;
    }
    _paDistace_to = NEW int[_sp->_rnum];
    _paSPMoveVelocityTo = NEW velo[_sp->_rnum];
    int x_from, y_from, z_from;
    int x_to, y_to, z_to;

    x_to = _sp->_X_compute[0];
    y_to = _sp->_Y_compute[0];
    z_to = _sp->_Z_compute[0];
    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t];
        y_to = _sp->_Y_compute[t];
        z_to = _sp->_Z_compute[t];
        _paDistace_to[t] = GgafDx9Util::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //���� paDistaceTo[t] ���A����frm_segment �ňړ����邽�߂ɕK�v�ȑ��x�����߂�B
        //����������������
        _paSPMoveVelocityTo[t] = (velo)(_paDistace_to[t] / _SPframe_segment);


    }
//
//    for (int t = 0; t < _sp->_rnum; t ++) {
//        _TRACE_((float)_sp->_X_compute[t]<<"  "<< (float)_sp->_Y_compute[t]<<"  "<< (float)_sp->_Z_compute[t]);
//    }

}

void GgafDx9FixedFrameSplineProgram::begin(GgafDx9GeometricActor* _pActor, int prm_option) {

    if (_sp != NULL) {
        _is_executing = true;
        _option = prm_option;
        _pActor_target = _pActor;
        _SPframe = 0;
        velo v = _pActor->_pMover->_veloMove;
        if (v == 0) {
            _paSPMoveVelocityTo[0] = 1000;
        } else {
            _paSPMoveVelocityTo[0] = v;
        }

        if (_option == 1) {
            _X_relative = _sp->_X_compute[0] - _pActor->_X ;
            _Y_relative = _sp->_Y_compute[0] - _pActor->_Y;
            _Z_relative = _sp->_Z_compute[0] - _pActor->_Z;
        }
    }
}




void GgafDx9FixedFrameSplineProgram::behave() {

    if (_is_executing) {
        //���݂̓_INDEX
        int SPPointIndex = _SPframe/_SPframe_segment;
        if ( SPPointIndex == _sp->_rnum) {
            //�I��
            _is_executing = false;
            return;
        }

        //�ς���
        if (_SPframe % _SPframe_segment == 0) {
            if (_option == 1) {
                //���΍��W�^�[�Q�b�g
                _pActor_target->_pMover->setStopTarget_RzRyMoveAngle(_sp->_X_compute[SPPointIndex] - _X_relative,
                                                                   _sp->_Y_compute[SPPointIndex] - _Y_relative,
                                                                   _sp->_Z_compute[SPPointIndex] - _Z_relative);
            } else {
                //��΍��W�^�[�Q�b�g
                _pActor_target->_pMover->setStopTarget_RzRyMoveAngle(_sp->_X_compute[SPPointIndex],
                                                                   _sp->_Y_compute[SPPointIndex],
                                                                   _sp->_Z_compute[SPPointIndex]);
            }

            if (_pActor_target->_pMover->getRzMoveAngleDistance(_pActor_target->_pMover->_angTargetRzMove, TURN_CLOSE_TO) > 0) {
                _pActor_target->_pMover->setRzMoveAngleVelocity(_angFaceMove);
            } else {
                _pActor_target->_pMover->setRzMoveAngleVelocity(-_angFaceMove);
            }

            if (_pActor_target->_pMover->getRyMoveAngleDistance(_pActor_target->_pMover->_angTargetRyMove, TURN_CLOSE_TO) > 0) {
                _pActor_target->_pMover->setRyMoveAngleVelocity(_angFaceMove);
            } else {
                _pActor_target->_pMover->setRyMoveAngleVelocity(-_angFaceMove);
            }


            _pActor_target->_pMover->setMoveVelocity(_paSPMoveVelocityTo[SPPointIndex]);
        }

        _SPframe++;

    }

}
GgafDx9FixedFrameSplineProgram::~GgafDx9FixedFrameSplineProgram() {
    DELETEARR_POSSIBLE_NULL(_paDistace_to);
    DELETEARR_POSSIBLE_NULL(_paSPMoveVelocityTo);
}
