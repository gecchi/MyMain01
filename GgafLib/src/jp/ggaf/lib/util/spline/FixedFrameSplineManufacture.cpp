#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineManufacture::FixedFrameSplineManufacture(const char* prm_source_file,
                                                         frame prm_spent_frame,
                                                         angvelo prm_angveloRzRyMv,
                                                         int prm_turn_way,
                                                         bool prm_turn_optimaize) :
        SplineManufacture(prm_source_file) {
    _spent_frame = prm_spent_frame;
    _angveloRzRyMv = prm_angveloRzRyMv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;

    //�P��Ԃ̎g�p�\�t���[��
    _frame_of_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_frame_of_segment < 1) {
        _frame_of_segment = 1;
    }
    _paDistace_to = NEW coord[_sp->_rnum];
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
}

FixedFrameSplineManufacture::FixedFrameSplineManufacture(SplineSource* prm_pSplSrc,
                                                         frame prm_spent_frame,
                                                         angvelo prm_angveloRzRyMv,
                                                         int prm_turn_way,
                                                         bool prm_turn_optimaize) :
      SplineManufacture(prm_pSplSrc) {
    _spent_frame = prm_spent_frame;
    _angveloRzRyMv = prm_angveloRzRyMv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;

    //�P��Ԃ̎g�p�\�t���[��
    _frame_of_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_frame_of_segment < 1) {
        _frame_of_segment = 1;
    }
    _paDistace_to = NEW coord[_sp->_rnum];
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
}


void FixedFrameSplineManufacture::calculate() {
    //���̂Q�̃e�[�u�����Čv�Z���X�V���܂��B
    // _paDistace_to[] : ���̕⊮�_�܂ł̋���
    // _paSPMvVeloTo[] : ���̕⊮�_���B�ɕK�v�ȑ��x

    //�e�_�̎��_�́A�����Ƒ��x��\�ߑS�����߂Ă���
    // ����_[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // point_num = 3          //����_�̐�
    // accuracy = 0.25(=1/4)  //�⊮�_���x
    // spent_frame = 120      //��₷�t���[��
    // �̏ꍇ�A���}�̂悤�ɂȂ�܂��B
    //
    // X:����_
    // o:����_�Ԃ̕⊮�_�i�X�v���C���Ȑ��ʉߓ_�j
    // X--o: �ړ��\��̍��W��
    // _paDistace_to[] : ���̕⊮�_�܂ł̋���
    // _paSPMvVeloTo[] : ���̕⊮�_���B�ɕK�v�ȑ��x
    //
    // sp._rnum �͍��v�̓_�̐���Ԃ��B���������� sp._rnum = 9 �ɂȂ�B
    // accuracy ���Y��ȕ����ɂȂ�Ȃ��ꍇ�A����_��ɕ⊮�_���J�邩�Ƃ��A�ʓ|�Ȃ̂ŁAsp._rnum��K���g�p����
    // ���}���Y��ɏd�Ȃ����ꍇ�̐}�ł���B
    //
    //           v = _paSPMvVeloTo[1]                           v = _paSPMvVeloTo[8]
    //               _paDistace_to[1]     _paDistace_to[5]          _paDistace_to[8]
    //                    ||                     ||                         ||
    //                   <-->                 <------>                    <----->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    //              (����_[0][0],       (����_[1][0],                       (����_[2][0],
    //               ����_[0][1],        ����_[1][1],                        ����_[2][1],
    //               ����_[0][2])        ����_[1][2])                        ����_[2][2])
    //            = (1000,2000,3000)    = (2000,1000,0)                      = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                                 120Frame��₵�Ĉړ�(=prm_spent_frame)
    //                  <-->
    //                  _spent_frame = �P��Ԃ� 120/8 Frame = prm_spent_frame / (sp._rnum-1);

    coord x_from, y_from, z_from;
    coord x_to, y_to, z_to;

    x_to = _sp->_X_compute[0]*_rate_X;
    y_to = _sp->_Y_compute[0]*_rate_Y;
    z_to = _sp->_Z_compute[0]*_rate_Z;
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

        //���� paDistaceTo[t] ���A����frm_segment �ňړ����邽�߂ɕK�v�ȑ��x�����߂�B
        //����������������
        _paSPMvVeloTo[t] = (velo)(_paDistace_to[t] / _frame_of_segment);
    }
    _paSPMvVeloTo[0] = 1000;
}

SplineSequence* FixedFrameSplineManufacture::createSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) {
    return NEW FixedFrameSplineSequence(this, prm_pKurokoA);
}

FixedFrameSplineManufacture::~FixedFrameSplineManufacture() {
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    DELETEARR_POSSIBLE_NULL(_paDistace_to);
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    DELETEARR_POSSIBLE_NULL(_paSPMvVeloTo);
}
