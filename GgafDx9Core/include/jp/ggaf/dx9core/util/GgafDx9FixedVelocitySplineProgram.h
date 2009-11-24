#ifndef GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
#define GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �X�v���C���Ȑ��A�Ȃ߂炩�ȓ����ړ��̂��߂̏��Z�b�g
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedVelocitySplineProgram : public GgafDx9SplineProgram {

public:

    int* _paDistace_to;
    float* _paFrame_need_at;
    velo _veloMoveUnit; //�P�ʑ��x
    angvelo _angFaceMove;
    float _fFrame_executing;
    float _fFrame_next_point;
    //float _fSPPointFrame;
    int _point_index;

    /** �I�v�V���� 0:��΍��W�ړ��A1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ� */
    int _option;

    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    GgafDx9FixedVelocitySplineProgram();


    /**
     * �R���X�g���N�^
     * �ړ��̂��߂̕K�v�ȏ����v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
     * @param prm_veloMove �ړ����x
     * @param prm_angFaceMove ����\��1�t���[��������̉�]�p (1000 �� 1�x)
     */
    GgafDx9FixedVelocitySplineProgram(double prm_paaCriteriaPoint[][3],
                                      int prm_point_num,
                                      double prm_accuracy,
                                      angvelo prm_angFaceMove);

    GgafDx9FixedVelocitySplineProgram(GgafDx9Spline3D* prm_sp,
                                      angvelo prm_angFaceMove);


    void init();

    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void begin(GgafDx9GeometricActor* prm_pActor, int prm_option = 0);

    /**
     * ���t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave();


    virtual ~GgafDx9FixedVelocitySplineProgram();
};

}
#endif /*GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_*/
