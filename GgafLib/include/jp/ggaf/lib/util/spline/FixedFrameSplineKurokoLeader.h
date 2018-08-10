#ifndef GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�A����(GgafDxCore::GgafDxKuroko)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineKurokoLeader : public SplineLeader {

public:
    GgafDxCore::GgafDxKuroko* _pKuroko_target;
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
     * @param prm_pKuroko
     */
    FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture,
                                 GgafDxCore::GgafDxKuroko* prm_pKuroko_target);

    virtual void restart() override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;


    virtual ~FixedFrameSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_*/
