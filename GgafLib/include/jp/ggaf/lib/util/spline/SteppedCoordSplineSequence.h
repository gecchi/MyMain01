#ifndef STEPPEDCOORDSPLINESEQUENCE_H_
#define STEPPEDCOORDSPLINESEQUENCE_H_
namespace GgafLib {

/**
 * �����ړ��X�v���C���Ȑ��ړ��B .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineSequence : public SplineSequence {

public:
    SteppedCoordSplineManufacture* _pFixedVeloSplManuf;

    /** [r]����x�ňړ������ꍇ�̃X�v���C���ړ����̌o�߃t���[���� */
    float _exec_fFrames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_exec_fFrames */
    float _fFrame_of_next;
    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;


    //�v�Z�p
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKurokoA �Ώۂ̃A�N�^�[�̍��qA
     */
    SteppedCoordSplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pKurokoA �Ώۂ̃A�N�^�[�̍��qA
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @param prm_angveloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    SteppedCoordSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                               SplineLine* prm_sp,
                               angvelo prm_angveloRzRyMv);


    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void exec(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave() override;


    virtual ~SteppedCoordSplineSequence();
};

}
#endif /*FIXEDVELOCITYSPLINESEQUENCE_H_*/
