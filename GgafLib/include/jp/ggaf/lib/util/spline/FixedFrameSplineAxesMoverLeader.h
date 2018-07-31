#ifndef GGAFLIB_FIXEDFRAMESPLINEAXESMOVERLEADER_H_
#define GGAFLIB_FIXEDFRAMESPLINEAXESMOVERLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�AGgafDxCore::GgafDxAxesMover �Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2018/07/25
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineAxesMoverLeader : public SplineLeader {

public:
    GgafDxCore::GgafDxAxesMover* _pAxesMover_target;
    /** [r]�X�v���C�����Z�b�g(spl�t�@�C���̏��ɑ���) */
    FixedFrameSplineManufacture* _pFixedFrameSplManuf;
    /** _leading_frames�ɉ��Z�����␳�t���[�� */
    frame _hosei_frames;
    /** [r]���݌������Ă���Œ��̕⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** �O���_point_index */
    int _prev_point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;
public:
    /**
     *
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pAxesMover
     */
    FixedFrameSplineAxesMoverLeader(SplineManufacture* prm_pManufacture,
                                 GgafDxCore::GgafDxAxesMover* prm_pAxesMover_target);

    FixedFrameSplineAxesMoverLeader(GgafDxCore::GgafDxAxesMover* prm_pAxesMover_target,
                                 SplineLine* prm_pSpl,
                                 frame prm_spent_frames,
                                 angvelo prm_angvelo_rzry_mv);

    virtual void restart() override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;


    virtual ~FixedFrameSplineAxesMoverLeader();
};

}
#endif /*GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_*/
