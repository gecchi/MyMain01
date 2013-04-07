#ifndef FIXEDFRAMESPLINEKUROKOSTEPPER_H_
#define FIXEDFRAMESPLINEKUROKOSTEPPER_H_
namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��B .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�A����A(GgafDxCore::GgafDxKurokoA)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineKurokoStepper : public SplineKurokoStepper {

public:
    FixedFrameSplineManufacture* _pFixedFrameSplManuf;

    //�v�Z�p�萔
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

public:
    /**
     *
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKurokoA
     */
    FixedFrameSplineKurokoStepper(SplineManufacture* prm_pManufacture,
                                  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    FixedFrameSplineKurokoStepper(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                                  SplineLine* prmpSpl,
                                  frame prm_spent_frame,
                                  angvelo prm_angveloRzRyMv);
    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void start(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    void behave() override;

    virtual ~FixedFrameSplineKurokoStepper();
};

}
#endif /*FIXEDFRAMESPLINEKUROKOSTEPPER_H_*/
