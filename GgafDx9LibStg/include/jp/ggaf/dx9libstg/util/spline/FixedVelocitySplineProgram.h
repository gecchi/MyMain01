#ifndef GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
#define GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �����ړ��X�v���C���Ȑ��ړ��B .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedVelocitySplineProgram : public SplineProgram {

public:
    /** [r]���݂̕⊮�_(��_���܂�)����A���̕⊮�_(or��_)�܂ł̋����̃e�[�u�� */
    coord* _paDistace_to;
    /** [r]�n�_����n�Ԗڂ̕⊮�_(��_���܂�)���B�ɕK�v�ȃt���[�����̃e�[�u�� */
    float* _paFrame_need_at;
    /** [r]����x */
    velo _veloMvUnit;
    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
    ang_velo _ang_veloRzRyMv;
    /** [r]����x�ňړ������ꍇ�̃X�v���C���ړ����̌o�߃t���[���� */
    float _fFrame_executing;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_fFrame_executing */
    float _fFrame_next_point;
    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;
    /**
     * [r]�I�v�V����
     * 0:��΍��W�ړ��B
     * 1:�n�_�������W�Ƃ��A�X�v���C�����W�Q�͑��Έړ��Ōv�Z�B
     * 2:�n�_�������W�Ƃ��A����Ɍ��݂̌����i_pKurokoA �� _angRzMv, _angRyMv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     */
    int _option;


    //�v�Z�p�萔
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     * �R���X�g���N�^ .
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @return
     */
    GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1.0���w�肵���ꍇ�A��_���玟��_�܂ŉ��������i�����Ō��ԃC���[�W�j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9����i�Ȃ߂炩�ȃJ�[�u�ɂȂ�j�B
     * @param prm_ang_veloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     */
    GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor,
                                      double prm_paaCriteriaPoint[][3],
                                      int prm_point_num,
                                      double prm_accuracy,
                                      ang_velo prm_ang_veloRzRyMv);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @param prm_ang_veloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor,
                                      Spline3D* prm_sp,
                                      ang_velo prm_ang_veloRzRyMv);

    /**
     * �������i�v�Z�j����.
     * �R���X�g���N�^���Ăяo����܂��B
     */
    void init();

    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void begin(int prm_option = 0) override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave() override;


    virtual ~GgafDx9FixedVelocitySplineProgram();
};

}
#endif /*GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_*/
