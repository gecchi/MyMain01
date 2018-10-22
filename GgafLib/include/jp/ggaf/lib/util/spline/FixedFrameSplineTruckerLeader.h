#ifndef GGAFLIB_FIXEDFRAMESPLINETRUCKERLEADER_H_
#define GGAFLIB_FIXEDFRAMESPLINETRUCKERLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�AGgafDxCore::GgafDxTrucker �Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2018/07/25
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineTruckerLeader : public SplineLeader {

public:
    GgafDxCore::GgafDxTrucker* _pTrucker_target;
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
     * @param prm_pManufacture
     * @param prm_pTrucker
     */
    FixedFrameSplineTruckerLeader(SplineManufacture* prm_pManufacture,
                                    GgafDxCore::GgafDxTrucker* prm_pTrucker_target);

    virtual void restart() override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;

    virtual ~FixedFrameSplineTruckerLeader();
};

}
#endif /*GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_*/
