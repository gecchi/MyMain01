#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"

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
    _fFrame_of_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_fFrame_of_segment < 1.0f) {
        _TRACE_("���x����FixedFrameSplineManufacture ["<<prm_source_file<<"] _fFrame_of_segment="<<_fFrame_of_segment<<" < 1.0f �ł��B"<<
                "�⊮�_��("<<(_sp->_rnum)<<")�����A�n�_�`�I���_�t���[����("<<_spent_frame<<")���������̂ŁA�⊮�_�̔�т��Ȃ������߁A�����I��_fFrame_of_segment��1.0�ɏ㏑���B"<<
                "�]���Ĉړ��ɂ�"<<(_sp->_rnum)<<"�t���[��������܂��B�������������B");
        _fFrame_of_segment = 1.0f;
    }
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
    _fFrame_of_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_fFrame_of_segment < 1.0f) {
        _TRACE_("���x����FixedFrameSplineManufacture  _fFrame_of_segment="<<_fFrame_of_segment<<" < 1.0f �ł��B"<<
                "�⊮�_��("<<(_sp->_rnum)<<")�����A�n�_�`�I���_�t���[����("<<_spent_frame<<")���������̂ŁA�⊮�_�̔�т��Ȃ������߁A�����I��_fFrame_of_segment��1.0�ɏ㏑���B"<<
                "�]���Ĉړ��ɂ�"<<(_sp->_rnum)<<"�t���[��������܂��B�������������B");
        _fFrame_of_segment = 1.0f;
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
    SplineManufacture::calculate();
    for (int t = 1; t < _sp->_rnum; t ++) {
        //���� paDistanceTo[t] ���A����frm_segment �ňړ����邽�߂ɕK�v�ȑ��x�����߂�B
        //����������������
        _paSPMvVeloTo[t] = (velo)(_paDistance_to[t] / _fFrame_of_segment);
    }
    _paSPMvVeloTo[0] = 0; //�n�_�܂ł̑��x�ȂǕ�����Ȃ��B
    _paDistance_to[0] = 0;   //�n�_�܂ł̋����ȂǕ�����Ȃ��B
}

SplineKurokoLeader* FixedFrameSplineManufacture::createKurokoLeader(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) {
    return NEW FixedFrameSplineKurokoLeader(this, prm_pKurokoA);
}

FixedFrameSplineManufacture::~FixedFrameSplineManufacture() {
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paSPMvVeloTo);
}
