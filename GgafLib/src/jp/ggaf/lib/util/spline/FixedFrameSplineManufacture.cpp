#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineAxesMoverLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineManufacture::FixedFrameSplineManufacture(const char* prm_source_file,
                                                         frame prm_spent_frames,
                                                         angvelo prm_angvelo_rzry_mv,
                                                         int prm_turn_way,
                                                         bool prm_turn_optimaize) : SplineManufacture(prm_source_file) {
    _spent_frames = prm_spent_frames;
    _angvelo_rzry_mv = prm_angvelo_rzry_mv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;

    //�P��Ԃ̎g�p�\�t���[��
    _frame_of_segment = 1.0*_spent_frames / (_sp->_rnum-1);
    if (_frame_of_segment < 1.0) {
        _TRACE_("���x����FixedFrameSplineManufacture ["<<prm_source_file<<"] _frame_of_segment="<<_frame_of_segment<<" < 1.0f �ł��B"
                "�⊮�_��("<<(_sp->_rnum)<<")�����A�n�_�`�I���_�t���[����("<<_spent_frames<<")���������̂ŁA�⊮�_�̔�т��Ȃ������߁A�����I��_frame_of_segment��1.0�ɏ㏑���B"
                "�]���Ĉړ��ɂ�"<<(_sp->_rnum)<<"�t���[��������܂��B�������������B");
        _frame_of_segment = 1.0;
    }
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
}

FixedFrameSplineManufacture::FixedFrameSplineManufacture(SplineSource* prm_pSplSrc,
                                                         frame prm_spent_frames,
                                                         angvelo prm_angvelo_rzry_mv,
                                                         int prm_turn_way,
                                                         bool prm_turn_optimaize) : SplineManufacture(prm_pSplSrc) {
    _spent_frames = prm_spent_frames;
    _angvelo_rzry_mv = prm_angvelo_rzry_mv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;

    //�P��Ԃ̎g�p�\�t���[��
    _frame_of_segment = 1.0*_spent_frames / (_sp->_rnum-1);
    if (_frame_of_segment < 1.0) {
        _TRACE_("���x����FixedFrameSplineManufacture  _frame_of_segment="<<_frame_of_segment<<" < 1.0f �ł��B"
                "�⊮�_��("<<(_sp->_rnum)<<")�����A�n�_�`�I���_�t���[����("<<_spent_frames<<")���������̂ŁA�⊮�_�̔�т��Ȃ������߁A�����I��_frame_of_segment��1.0�ɏ㏑���B"
                "�]���Ĉړ��ɂ�"<<(_sp->_rnum)<<"�t���[��������܂��B�������������B");
        _frame_of_segment = 1.0;
    }
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
}


void FixedFrameSplineManufacture::calculate() {
    //���̂Q�̃e�[�u�����Čv�Z���X�V���܂��B
    // _paDistance_to[] : ���̕⊮�_�܂ł̋���
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
    // _paDistance_to[] : ���̕⊮�_�܂ł̋���
    // _paSPMvVeloTo[] : ���̕⊮�_���B�ɕK�v�ȑ��x
    //
    // sp._rnum �͍��v�̓_�̐���Ԃ��B���������� sp._rnum = 9 �ɂȂ�B
    // accuracy ���Y��ȕ����ɂȂ�Ȃ��ꍇ�A����_��ɕ⊮�_���J�邩�Ƃ��A�ʓ|�Ȃ̂ŁAsp._rnum��K���g�p����
    // ���}���Y��ɏd�Ȃ����ꍇ�̐}�ł���B
    //
    //           v = _paSPMvVeloTo[1]                           v = _paSPMvVeloTo[8]
    //               _paDistance_to[1]     _paDistance_to[5]          _paDistance_to[8]
    //                    ||                     ||                         ||
    //                   <-->                 <------>                    <----->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._x_compute[0],         | (sp._x_compute[5],        sp._x_compute[8]
    //             sp._y_compute[0],         |  sp._y_compute[5],        sp._y_compute[8]
    //             sp._z_compute[0])         |  sp._z_compute[5])        sp._z_compute[8]
    //                  |                    |                                   |
    //              (����_[0][0],       (����_[1][0],                       (����_[2][0],
    //               ����_[0][1],        ����_[1][1],                        ����_[2][1],
    //               ����_[0][2])        ����_[1][2])                        ����_[2][2])
    //            = (1000,2000,3000)    = (2000,1000,0)                      = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                                 120Frame��₵�Ĉړ�(=_spent_frames)
    //                  <-->
    //                  _spent_frames = �P��Ԃ� 120/8 Frame = _spent_frames / (sp._rnum-1);
    SplineManufacture::calculate();
    int rnum = _sp->_rnum;
    //_TRACE_("rnum="<<rnum);
    for (int t = 1; t < rnum; t++) {
        //���� paDistanceTo[t] ���A����frm_segment �ňړ����邽�߂ɕK�v�ȑ��x�����߂�B
        //����������������
        _paSPMvVeloTo[t] = ((velo)(_paDistance_to[t] / _frame_of_segment));
        if (_paSPMvVeloTo[t] == 0) {
            _paSPMvVeloTo[t] = 1;
        }
        //_TRACE_("_paDistance_to["<<t<<"]="<<_paDistance_to[t]<<" _frame_of_segment="<<_frame_of_segment<<" _paSPMvVeloTo["<<t<<"]="<<_paDistance_to[t]<<"");
    }
    _paSPMvVeloTo[0] = 0; //�n�_�܂ł̑��x�ȂǕ�����Ȃ��B
    _paDistance_to[0] = 0;   //�n�_�܂ł̋����ȂǕ�����Ȃ��B
}

void FixedFrameSplineManufacture::recalculateBySpentFrame(frame prm_spent_frames) {
    _spent_frames = prm_spent_frames;
    _frame_of_segment = 1.0*_spent_frames / (_sp->_rnum-1);
    if (_frame_of_segment < 1.0) {
        _TRACE_("���x����FixedFrameSplineManufacture::setSpentFrames()  _frame_of_segment="<<_frame_of_segment<<" < 1.0f �ł��B"
                "�⊮�_��("<<(_sp->_rnum)<<")�����A�n�_�`�I���_�t���[����("<<_spent_frames<<")���������̂ŁA�⊮�_�̔�т��Ȃ������߁A�����I��_frame_of_segment��1.0�ɏ㏑���B"
                "�]���Ĉړ��ɂ�"<<(_sp->_rnum)<<"�t���[��������܂��B�������������B");
        _frame_of_segment = 1.0;
    }
    int rnum = _sp->_rnum;
    for (int t = 1; t < rnum; t++) {
        _paSPMvVeloTo[t] = ((velo)(_paDistance_to[t] / _frame_of_segment));
        if (_paSPMvVeloTo[t] == 0) {
            _paSPMvVeloTo[t] = 1;
        }
    }
    _paSPMvVeloTo[0] = 0; //�n�_�܂ł̑��x�ȂǕ�����Ȃ��B
}

SplineLeader* FixedFrameSplineManufacture::createKurokoLeader(GgafDxCore::GgafDxKuroko* prm_pKuroko) {
    return NEW FixedFrameSplineKurokoLeader(this, prm_pKuroko);
}
SplineLeader* FixedFrameSplineManufacture::createAxesMoverLeader(GgafDxCore::GgafDxAxesMover* prm_pAxesMover) {
    return NEW FixedFrameSplineAxesMoverLeader(this, prm_pAxesMover);
}
FixedFrameSplineManufacture::~FixedFrameSplineManufacture() {
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paSPMvVeloTo);
}
