#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram() : GgafDx9SplineProgram() {

    _paSPDistaceTo = NULL;
    _paSPNeedFrameTo = NULL;
    _is_executing = false;
    _option = 0;

    _X_relative = 0;
    _Y_relative = 0;
    _Z_relative = 0;
    _SPNextChangeFrame = 0;
    _SPPointIndex = 0;
    _angRotMove = ANGLE360;
}

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram(double prm_paaCriteriaPoints[][3],
                                                               int prm_point_num,
                                                               double prm_accuracy,
                                                               velo prm_veloMove,
                                                               angvelo prm_angRotMove )

                                        : GgafDx9SplineProgram(prm_paaCriteriaPoints,
                                                               prm_point_num,
                                                               prm_accuracy)      {


    //�e�_�̎��_�́A�����ƕK�v�ȃt���[������\�ߑS�����߂Ă���

    // prm_paaCriteriaPoints[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // prm_point_num = 3          //��_�̐�
    // prm_accuracy = 0.25(=1/4)  //�⊮�_���x
    // prm_veloMove = 5000        //���x
    // �̏ꍇ�A���}�̂悤�ɂȂ�܂��B
    //
    // X:��_
    // o:��_�Ԃ̕⊮�_�i�X�v���C���Ȑ��ʉߓ_�j
    // X--o: �ړ��\��̍��W��
    // _paSPDistaceTo[] : ���̕⊮�_�܂ł̋���
    // _paSPNeedFrameTo[] : ���̕⊮�_���B�ɕK�v�ȃt���[����
    //
    // sp._rnum �͍��v�̓_�̐���Ԃ��B���������� sp._rnum = 9 �ɂȂ�B
    // prm_accuracy ���Y��ȕ����ɂȂ�Ȃ��ꍇ�A��_��ɕ⊮�_���J�邩�Ƃ��A�S�R�킩��Ȃ��̂ŁAsp._rnum��K���g�p����
    // ���}���Y��ɏd�Ȃ����ꍇ�̐}�ł���B
    //
    //                           ��������  prm_veloMove = 5000��
    //      �����F_paSPDistaceTo[1]          _paSPDistaceTo[5]           _paSPDistaceTo[8]
    //
    //      ���ԁF_paSPNeedFrameTo[1]        _paSPNeedFrameTo[5]         _paSPNeedFrameTo[8]
    //           = _paSPDistaceTo[1]/5000   = _paSPDistaceTo[5]/5000     = _paSPDistaceTo[8]/5000  Frame �K�v
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
    //                                 ������ prm_veloMove �ňړ�
    //

    _angRotMove = prm_angRotMove;
    _veloMove = prm_veloMove;
    _paSPDistaceTo = NEW int[_sp->_rnum];
    _paSPNeedFrameTo = NEW DWORD[_sp->_rnum];

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
        _paSPDistaceTo[t] = GgafDx9Util::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //���� paDistaceTo[t] ���A���x prm_veloMove �ňړ�����̂ɕK�v�ȃt���[���������߂�B
        //���ԁ�����������
        _paSPNeedFrameTo[t] = (DWORD)(1.0*_paSPDistaceTo[t] / prm_veloMove);

    }

}

void GgafDx9FixedVelocitySplineProgram::begin(GgafDx9GeometricActor* prm_pActor, int prm_option) {

    if (_sp != NULL) {
        _is_executing = true;
        _option = prm_option;
        _pActor_executing = prm_pActor;
        _SPframe = 0;
        _SPNextChangeFrame = 0;
        _SPPointIndex = 0;
        if (_option == 1) {
            _X_relative = _sp->_X_compute[0] - _pActor_executing->_X ;
            _Y_relative = _sp->_Y_compute[0] - _pActor_executing->_Y;
            _Z_relative = _sp->_Z_compute[0] - _pActor_executing->_Z;
        }


    }
}




void GgafDx9FixedVelocitySplineProgram::behave() {

    if (_is_executing) {
        //�ς���
        if (_SPframe == _SPNextChangeFrame) {
            GgafDx9GeometryMover* _pActorMover = _pActor_executing->_pMover;
            if (_option == 1) {
                //���΍��W�^�[�Q�b�g
                _pActorMover->setSuspendTargetRzRyMoveAngle(_sp->_X_compute[_SPPointIndex] - _X_relative,
                                                            _sp->_Y_compute[_SPPointIndex] - _Y_relative,
                                                            _sp->_Z_compute[_SPPointIndex] - _Z_relative);
            } else {
                //��΍��W�^�[�Q�b�g
                _pActorMover->setSuspendTargetRzRyMoveAngle(_sp->_X_compute[_SPPointIndex],
                                                            _sp->_Y_compute[_SPPointIndex],
                                                            _sp->_Z_compute[_SPPointIndex]);
            }
            if (_pActorMover->getDifferenceFromRzMoveAngleTo(_pActorMover->_angTargetRzMove, TURN_CLOSE_TO) > 0) {
                _pActorMover->setRzMoveAngleVelocity(_angRotMove);
            } else {
                _pActorMover->setRzMoveAngleVelocity(-_angRotMove);
            }
            if (_pActorMover->getDifferenceFromRyMoveAngleTo(_pActorMover->_angTargetRyMove, TURN_CLOSE_TO) > 0) {
                _pActorMover->setRyMoveAngleVelocity(_angRotMove);
            } else {
                _pActorMover->setRyMoveAngleVelocity(-_angRotMove);
            }


            if (_SPPointIndex == 0) {
                //�n�_�֍s���I
                _paSPDistaceTo[0] = GgafDx9Util::getDistance(
                                        (double)_pActor_executing->_X,
                                        (double)_pActor_executing->_Y,
                                        (double)_pActor_executing->_Z,
                                        _sp->_X_compute[0],
                                        _sp->_Y_compute[0],
                                        _sp->_Z_compute[0]
                                     );
                //�n�_�܂łɕK�v�ȃt���[�����擾
                _paSPNeedFrameTo[0] =  (DWORD)(1.0*_paSPDistaceTo[0] / _veloMove);
                _pActorMover->setMoveVelocity(_veloMove);
            }

            //���̕⊮�_�܂łɕK�v�ȃt���[�������X�V
            _SPNextChangeFrame += _paSPNeedFrameTo[_SPPointIndex];
            _SPPointIndex++;
            if ( _SPPointIndex == _sp->_rnum) {
                //�I��
                _is_executing = false;
                return;
            }
        }
        _SPframe++;
    }

}
GgafDx9FixedVelocitySplineProgram::~GgafDx9FixedVelocitySplineProgram() {
    DELETEARR_POSSIBLE_NULL(_paSPDistaceTo);
    DELETEARR_POSSIBLE_NULL(_paSPNeedFrameTo);
}
