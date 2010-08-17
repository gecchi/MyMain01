#ifndef GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
#define GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��B .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedFrameSplineProgram : public GgafDx9SplineProgram {

public:
    /** [r]�P��Ԃ̎g�p�\�t���[�� */
    frame _SPframe_segment;
    /** [r]���̕⊮�_�܂ł̋����̃e�[�u�� */
    int* _paDistace_to;
    /** [r]���̕⊮�_���B�ɕK�v�Ȉړ����x�̃e�[�u�� */
    velo* _paSPMvVeloTo;
    /** [rw]�����]���ɋ������RzRy�̎��]���x */
    angvelo _angveloRzRyMv;
    /** [r]�ڕW�n�_�ɓ����܂łɐݒ肳�ꂽ�t���[���� */
    frame _spent_frame;
    /**
     * [r]�I�v�V����
     * 0:��΍��W�ړ��B
     * 1:�n�_�������W�Ƃ��A�X�v���C�����W�Q�͑��Έړ��Ōv�Z�B
     * 2:�n�_�������W�Ƃ��A����Ɍ��݂̌����i_pMover �� _angRzMv, _angRyMv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     */
    int _option;

    //�v�Z�p�萔
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     * �R���X�g���N�^
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9GeometricActor* prm_pActor);


    /**
     * �R���X�g���N�^.
     * �Œ莞�Ԉړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * �������������GgafDx9Spline3D�𐶐����X�v���C���Ȑ��⊮�_���v�Z���܂��B
     * GgafDx9Spline3D�I�u�W�F�N�g�̉���������ōs���܂��B
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1.0���w�肵���ꍇ�A��_���玟��_�܂ŉ��������i�����Ō��ԃC���[�W�j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9����i�Ȃ߂炩�ȃJ�[�u�ɂȂ�j�B
     * @param prm_spent_frame �n�_�`�I�_�ֈړ�����̂ɔ�₷�t���[����
     * @param prm_angveloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9GeometricActor* prm_pActor,
                                   double prm_paaCriteriaPoint[][3],
                                   int prm_point_num,
                                   double prm_accuracy,
                                   frame prm_spent_frame,
                                   angvelo prm_angveloRzRyMv);
    /**
     * �R���X�g���N�^.
     * �Œ莞�Ԉړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * ������GgafDx9Spline3D�𗘗p���܂��BGgafDx9Spline3D�̉���́A�Ăяo�����ōs���Ă��������B
     * ��������̃I�u�W�F�N�g�ɓ���GgafDx9Spline3D�̓�����������ꍇ�́A
     * ������̃R���X�g���N�^�Ő������ׂ��ł��B
     * @param prm_pActor �Ώۂ̃A�N�^�[
     * @param prm_sp �X�v���C���Ȑ��̕⊮�_�����A�ێ��N���X�̃C���X�^���X
     * @param prm_spent_frame �n�_�`�I�_�ֈړ�����̂ɋ������t���[����
     * @param prm_angveloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9GeometricActor* prm_pActor,
                                   GgafDx9Spline3D* prm_sp,
                                   frame prm_spent_frame,
                                   angvelo prm_angveloRzRyMv);

    /**
     * �������֐� .
     * �R���X�g���N�^�����p�B
     */
    void init();

    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void begin(int prm_option = 0) override;

    /**
     * �ړ����s���\�b�h .
     * �ړ��̂��߂ɖ��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave() override;

    virtual ~GgafDx9FixedFrameSplineProgram();
};

}
#endif /*GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_*/
