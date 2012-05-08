#include "stdafx.h"
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

    _veloMvUnit = LEN_UNIT; //���x1000�Ƃ����ꍇ�́A�e��Ԃ̃t���[���������߂�
    _paDistace_to = NEW coord[_sp->_rnum];
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

    _veloMvUnit = LEN_UNIT; //���x1000�Ƃ����ꍇ�́A�e��Ԃ̃t���[���������߂�
    _paDistace_to = NEW coord[_sp->_rnum];
    _paFrame_need_at = NEW float[_sp->_rnum];
}

void FixedVelocitySplineManufacture::calculate() {
    //���̂Q�̃e�[�u�����Čv�Z���X�V���܂��B
    // _paDistace_to[] : ���݂̕⊮�_����A���̕⊮�_�܂ł̋���
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
    // _paDistace_to[] : ���݂̕⊮�_����A���̕⊮�_�܂ł̋���
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
    //              _paDistace_to[1]      _paDistace_to[5]         _paDistace_to[8]
    //                    ||                     ||                         ||
    //                   <--->                <------->                  <------->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    //            (����_[0][0],           (����_[1][0],                   (����_[2][0],
    //             ����_[0][1],            ����_[1][1],                    ����_[2][1],
    //             ����_[0][2])            ����_[1][2])                    ����_[2][2])
    //              = (1000,2000,3000)    = (2000,1000,0)                   = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                         ������ veloMoveUnit �̑��x�ňړ��Ƃ����ꍇ���v�Z
    //

    coord x_from, y_from, z_from;
    coord x_to, y_to, z_to;

    x_to = _sp->_X_compute[0]*_rate_X;
    y_to = _sp->_Y_compute[0]*_rate_Y;
    z_to = _sp->_Z_compute[0]*_rate_Z;

    _paFrame_need_at[0] = 0;

    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t]*_rate_X;
        y_to = _sp->_Y_compute[t]*_rate_Y;
        z_to = _sp->_Z_compute[t]*_rate_Z;
        _paDistace_to[t] = GgafDxUtil::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //���� paDistaceTo[t] ���A���x _veloMvUnit(=1000) �ňړ�����̂ɕK�v�ȃt���[���������߂�B
        //���ԁ�����������
        _paFrame_need_at[t] = _paFrame_need_at[t-1] + (float)(1.0*_paDistace_to[t] / _veloMvUnit);
    }
}

SplineSequence* FixedVelocitySplineManufacture::createSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) {
    return NEW FixedVelocitySplineSequence(this, prm_pKurokoA);
}

FixedVelocitySplineManufacture::~FixedVelocitySplineManufacture() {
    DELETEARR_POSSIBLE_NULL(_paDistace_to);
    DELETEARR_POSSIBLE_NULL(_paFrame_need_at);
}
