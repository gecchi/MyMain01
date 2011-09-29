#ifndef FIXEDFRAMESPLINESEQUENCE_H_
#define FIXEDFRAMESPLINESEQUENCE_H_
namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��B .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineSequence : public SplineSequence {

public:

    FixedFrameSplineManufacture* _pFixedFrameSplManuf;

    //�v�Z�p�萔
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     *
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKurokoA
     */
    FixedFrameSplineSequence(SplineManufacture* prm_pManufacture,
                             GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    FixedFrameSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                             SplineLine* prmpSpl,
                             frame prm_spent_frame,
                             ang_velo prm_ang_veloRzRyMv);
    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void exec(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * �ړ����s���\�b�h .
     * �ړ��̂��߂ɖ��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave() override;

    virtual ~FixedFrameSplineSequence();
};

}
#endif /*FIXEDFRAMESPLINESEQUENCE_H_*/
