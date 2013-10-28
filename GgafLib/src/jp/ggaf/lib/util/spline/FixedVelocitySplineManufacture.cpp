#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedVelocitySplineManufacture::FixedVelocitySplineManufacture(const char* prm_source_file,
                                                               angvelo prm_angveloRzRyMv,
                                                               int prm_turn_way,
                                                               bool prm_turn_optimaize) :
        SplineManufacture(prm_source_file) {
    _angveloRzRyMv = prm_angveloRzRyMv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _point_index = 0;
    _veloMvUnit = PX_C(1); //���x PX_C(1) �Ƃ����ꍇ�̊e��Ԃ̃t���[��������{�Ƃ���
    _paFrame_need_at = NEW float[_sp->_rnum];
}

FixedVelocitySplineManufacture::FixedVelocitySplineManufacture(SplineSource* prm_pSplSrc,
                                                               angvelo prm_angveloRzRyMv,
                                                               int prm_turn_way,
                                                               bool prm_turn_optimaize) :
        SplineManufacture(prm_pSplSrc) {
    _angveloRzRyMv = prm_angveloRzRyMv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _point_index = 0;
    _veloMvUnit = PX_C(1); //���x PX_C(1) �Ƃ����ꍇ�̊e��Ԃ̃t���[��������{�Ƃ���
    _paFrame_need_at = NEW float[_sp->_rnum];
}

void FixedVelocitySplineManufacture::calculate() {
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
    //                           ��������  _veloMvUnit = 1000��
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
    SplineManufacture::calculate();
    _paFrame_need_at[0] = 0; //�n�_�ɍs���܂łɕK�v�ȃt���[�����͕s��
    for (int t = 1; t < _sp->_rnum; t ++) {
        //���� paDistanceTo[t] ���A���x _veloMvUnit(=1000) �ňړ�����̂ɕK�v�ȃt���[���������߂�B
        //���ԁ�����������
        _paFrame_need_at[t] = _paFrame_need_at[t-1] + (float)(1.0*_paDistance_to[t] / _veloMvUnit);
    }
}

SplineKurokoLeader* FixedVelocitySplineManufacture::createKurokoLeader(GgafDxCore::GgafDxKurokoA* const prm_pKurokoA) {
    return NEW FixedVelocitySplineKurokoLeader(this, prm_pKurokoA);
}

FixedVelocitySplineManufacture::~FixedVelocitySplineManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    GGAF_DELETEARR_NULLABLE(_paFrame_need_at);
}
