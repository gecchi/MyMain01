#ifndef GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
#define GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �X�v���C���Ȑ��A�Ȃ߂炩�ȃt���[���w��ړ��̂��߂̏��Z�b�g
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedFrameSplineProgram : public GgafDx9SplineProgram {

public:
    /** �P��Ԃ̎g�p�\�t���[�� */
    DWORD _SPframe_segment;
    /** ���̕⊮�_�܂ł̋����̃e�[�u�� */
    int* _paDistace_to;
    /** ���̕⊮�_���B�ɕK�v�Ȉړ����x�̃e�[�u�� */
    velo* _paSPMoveVelocityTo;
    /** �����]���ɋ������RzRy�̎��]���x */
    angvelo _angFaceMove;
    /** �ڕW�n�_�ɓ����܂łɐݒ肳�ꂽ�t���[���� */
    DWORD _spent_frame;

    /** �I�v�V���� 0:��΍��W�ړ��A1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ� */
    int _option;
    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    /**
     * �R���X�g���N�^
     */
    GgafDx9FixedFrameSplineProgram();


    /**
     * �R���X�g���N�^.
     * �������������GgafDx9Spline3D�𐶐����X�v���C���Ȑ��⊮�_���v�Z���܂��B
     * GgafDx9Spline3D�I�u�W�F�N�g�̉���������ōs���܂��B
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
     * @param prm_paaCriteriaPoint �n�_�`�I�_�ֈړ�����̂ɋ������t���[����
     * @param prm_angFaceMove ����\��1�t���[��������̉�]�p (1000 �� 1�x)
     */
    GgafDx9FixedFrameSplineProgram(double prm_paaCriteriaPoint[][3],
                                   int prm_point_num,
                                   double prm_accuracy,
                                   DWORD prm_spent_frame,
                                   angvelo prm_angFaceMove);
    /**
     * �R���X�g���N�^.
     * ������GgafDx9Spline3D�𗘗p���܂��BGgafDx9Spline3D�̉���́A�Ăяo�����ōs���Ă��������B
     * ��������̃I�u�W�F�N�g�ɓ���������������ꍇ�́A������̃R���X�g���N�^�Ő������ׂ��ł��B
     * @param prm_sp �X�v���C���Ȑ��̕⊮�_�����A�ێ��N���X�̃C���X�^���X
     * @param prm_spent_frame �n�_�`�I�_�ֈړ�����̂ɋ������t���[����
     * @param prm_angFaceMove ����\��1�t���[��������̉�]�p (1000 �� 1�x)
     * @return
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9Spline3D* prm_sp,
                                   DWORD prm_spent_frame,
                                   angvelo prm_angFaceMove);

    /**
     * �������֐� .
     * �R���X�g���N�^�����p�B
     */
    void init();

    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void begin(GgafDx9GeometricActor* _pActor, int prm_option = 0);

    /**
     * �ړ����s���\�b�h .
     * �ړ��̂��߂ɖ��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave();

    virtual ~GgafDx9FixedFrameSplineProgram();
};

}
#endif /*GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_*/
