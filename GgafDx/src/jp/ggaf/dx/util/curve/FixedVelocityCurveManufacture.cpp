#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"

#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveVecDriverLeader.h"

using namespace GgafDx;

FixedVelocityCurveManufacture::FixedVelocityCurveManufacture(const char* prm_coord_data_file,
                                                               angvelo prm_angvelo_rzry_mv,
                                                               int prm_turn_way,
                                                               bool prm_turn_optimaize) :
        CurveManufacture(prm_coord_data_file) {
    _angvelo_rzry_mv = prm_angvelo_rzry_mv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _velo_mvUnit = PX_C(1); //���x PX_C(1) �Ƃ����ꍇ�̊e��Ԃ̃t���[��������{�Ƃ���
    _paFrame_need_at = NEW float[_pCurve->_rnum];
}

FixedVelocityCurveManufacture::FixedVelocityCurveManufacture(CurveSource* prm_pCurve,
                                                               angvelo prm_angvelo_rzry_mv,
                                                               int prm_turn_way,
                                                               bool prm_turn_optimaize) :
        CurveManufacture(prm_pCurve) {
    _angvelo_rzry_mv = prm_angvelo_rzry_mv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _velo_mvUnit = PX_C(1); //���x PX_C(1) �Ƃ����ꍇ�̊e��Ԃ̃t���[��������{�Ƃ���
    _paFrame_need_at = NEW float[_pCurve->_rnum];
}

void FixedVelocityCurveManufacture::calculate() {
    //���̂Q�̃e�[�u�����Čv�Z���X�V���܂��B
    // _paDistance_to[] : ���݂̕⊮�_����A���̕⊮�_�܂ł̋���
    // _paFrame_need_at[] : �n�_����⊮�_���B�ɕK�v�ȃt���[�����̔z��

    //�e�_�̎��_�́A�����ƕK�v�ȃt���[������\�ߑS�����߂Ă���
    // ����_[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // point_num = 3          //����_�̐�
    // accuracy = 0.25(=1/4)  //�⊮�_���x
    //
    // �̏ꍇ�A���}�̂悤�ɂȂ�܂��B
    //
    // X:����_
    // o:����_�Ԃ̕⊮�_�i�X�v���C���Ȑ��ʉߓ_�j
    // X--o: �ړ��\��̍��W��
    // _paDistance_to[] : ���݂̕⊮�_����A���̕⊮�_�܂ł̋���
    // _paFrame_need_at[] : �n�_����⊮�_���B�ɕK�v�ȃt���[�����̔z��
    //
    // sp._rnum �͍��v�̓_�̐���Ԃ��B���������� sp._rnum = 9 �ɂȂ�B
    // prm_accuracy ���Y��ȕ����ɂȂ�Ȃ��ꍇ�A����_��ɕ⊮�_���J�邩�Ƃ��A�S�R�킩��Ȃ��̂ŁAsp._rnum��K���g�p����
    // ���}���Y��ɏd�Ȃ����ꍇ�̐}�ł���B
    //
    //                           ��������  _velo_mvUnit = 1000��
    //
    //               _paFrame_need_at[1] �K�v�ȃt���[����
    //                     ||              _paFrame_need_at[5]
    //                   <--->                      ||                 _paFrame_need_at[8]
    //                   <----------------------------->                      ||
    //                   <------------------------------------------------------->
    //
    //              _paDistance_to[1]      _paDistance_to[5]         _paDistance_to[8]
    //                    ||                     ||                         ||
    //                   <--->                <------->                  <------->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._x_compute[0],         | (sp._x_compute[5],        sp._x_compute[8]
    //             sp._y_compute[0],         |  sp._y_compute[5],        sp._y_compute[8]
    //             sp._z_compute[0])         |  sp._z_compute[5])        sp._z_compute[8]
    //                  |                    |                                   |
    //            (����_[0][0],           (����_[1][0],                   (����_[2][0],
    //             ����_[0][1],            ����_[1][1],                    ����_[2][1],
    //             ����_[0][2])            ����_[1][2])                    ����_[2][2])
    //              = (1000,2000,3000)    = (2000,1000,0)                   = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                         ������ veloMoveUnit �̑��x�ňړ��Ƃ����ꍇ���v�Z
    //
    CurveManufacture::calculate();
    _paFrame_need_at[0] = 0; //�n�_�ɍs���܂łɕK�v�ȃt���[�����͕s��
    int rnum = _pCurve->_rnum;
    for (int t = 1; t < rnum; t ++) {
        //���� paDistanceTo[t] ���A���x _velo_mvUnit(=1000) �ňړ�����̂ɕK�v�ȃt���[���������߂�B
        //���ԁ�����������
        _paFrame_need_at[t] = _paFrame_need_at[t-1] + (float)(1.0*_paDistance_to[t] / _velo_mvUnit);
    }
}

DriverLeader* FixedVelocityCurveManufacture::createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) {
    return NEW FixedVelocityCurveVecDriverLeader(this, prm_pVecDriver);
}

FixedVelocityCurveManufacture::~FixedVelocityCurveManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    GGAF_DELETEARR_NULLABLE(_paFrame_need_at);
}
