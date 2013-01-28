#ifndef FIXEDVELOCITYSPLINESEQUENCE_H_
#define FIXEDVELOCITYSPLINESEQUENCE_H_
namespace GgafLib {

/**
 * �����ړ��X�v���C���Ȑ��ړ��B .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineSequence : public SplineSequence {

public:
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;

    /** [r]����x�ňړ������ꍇ�̃X�v���C���ړ����̌o�߃t���[���� */
    float _exec_fFrames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_exec_fFrames */
    float _fFrame_of_next;
    //�v�Z�p
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKurokoA �Ώۂ̃A�N�^�[�̍��qA
     */
    FixedVelocitySplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pKurokoA �Ώۂ̃A�N�^�[�̍��qA
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @param prm_angveloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    FixedVelocitySplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                               SplineLine* prm_sp,
                               angvelo prm_angveloRzRyMv);


    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void exec(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * exec() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * exec() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    void behave() override;


    virtual ~FixedVelocitySplineSequence();
};

}
#endif /*FIXEDVELOCITYSPLINESEQUENCE_H_*/
