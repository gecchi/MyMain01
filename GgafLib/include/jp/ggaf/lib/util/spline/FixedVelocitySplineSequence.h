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

//    /** [r]���݂̕⊮�_(��_���܂�)����A���̕⊮�_(or��_)�܂ł̋����̃e�[�u�� */
//    coord* _paDistace_to;
//    /** [r]�n�_����n�Ԗڂ̕⊮�_(��_���܂�)���B�ɕK�v�ȃt���[�����̃e�[�u�� */
//    float* _paFrame_need_at;
    /** [r]����x */
//    velo _veloMvUnit;
//    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
//    ang_velo _ang_veloRzRyMv;
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
     *
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKurokoA
     */
    FixedVelocitySplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);
//    /**
//     * �R���X�g���N�^ .
//     * �ォ��F�X�ݒ肷��ꍇ�̃R���X�g���N�^
//     * @param prm_pActor �Ώۂ̃A�N�^�[
//     */
//    FixedVelocitySplineSequence(GgafDxCore::GgafDxGeometricActor* prm_pActor);
//
//    /**
//     * �R���X�g���N�^ .
//     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
//     * @param prm_pActor �Ώۂ̃A�N�^�[
//     * @param prm_paaCriteriaPoint ����_�z��
//     * @param prm_point_num  ����_�z��̗v�f��
//     * @param prm_accuracy  1����_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
//     *                      ����_�Ɛ���_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
//     *                      1.0���w�肵���ꍇ�A����_���玟����_�܂ŉ��������i�����Ō��ԃC���[�W�j�B
//     *                      0.5 �Ƃ���Ɛ���_���玟����_�܂łɕ⊮�_��1����B
//     *                      0.1 �Ƃ���Ɛ���_�Ɛ���_�̊Ԃɕ⊮�_��9����i�Ȃ߂炩�ȃJ�[�u�ɂȂ�j�B
//     * @param prm_ang_veloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
//     */
//    FixedVelocitySplineSequence(GgafDxCore::GgafDxGeometricActor* prm_pActor,
//                               double prm_paaCriteriaPoint[][3],
//                               int prm_point_num,
//                               double prm_accuracy,
//                               ang_velo prm_ang_veloRzRyMv);
//
    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @param prm_ang_veloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    FixedVelocitySplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                               SplineLine* prm_sp,
                               ang_velo prm_ang_veloRzRyMv);


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


    virtual ~FixedVelocitySplineSequence();
};

}
#endif /*FIXEDVELOCITYSPLINESEQUENCE_H_*/
