#ifndef GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
#define GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �X�v���C���Ȑ��A�Ȃ߂炩�ȃt���[���w��ړ��̂��߂̏��Z�b�g
 */
class GgafDx9FixedFrameSplineProgram : public GgafDx9SplineProgram {

public:

    DWORD _SPframe_segment;
    int* _paDistace_to;
    velo* _paSPMoveVelocityTo;
    angvelo _angRotMove;

    /** �I�v�V���� 0:��΍��W�ړ��A1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ� */
    int _option;
    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    GgafDx9FixedFrameSplineProgram();


    /**
     *
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
     * @param prm_paaCriteriaPoint �n�_�`�I�_�ֈړ�����̂ɋ������t���[����
     * @param prm_angRotMove ����\��1�t���[��������̉�]�p (1000 �� 1�x)
     */
    GgafDx9FixedFrameSplineProgram(double prm_paaCriteriaPoint[][3],
                                   int prm_point_num,
                                   double prm_accuracy,
                                   DWORD prm_spent_frame,
                                   angvelo prm_angRotMove);

    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void begin(GgafDx9GeometricActor* _pActor, int prm_option = 0);

    /**
     * ���t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave();




    virtual ~GgafDx9FixedFrameSplineProgram();
};

}
#endif /*GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_*/
