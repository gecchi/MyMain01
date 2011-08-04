#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �⊮�_�Ɉړ����邽�߁A���x���r���ƃJ�N�J�N�ł��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineProgram : public GgafCore::GgafObject {

public:
    /** �X�v���C���Ȑ��̕⊮�_�����A�ێ�����N���X */
    Spline3D* _sp;
    /** begin()����̌o�߃t���[���� */
    frame _SPframe;
    /** ���݃v���O�������s���ł��邩�ǂ��� */
    bool _is_executing;
    /** ���W�𑀍삷��ΏۂƂȂ�A�N�^�[ */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_target;
    /** �R���X�g���N�^������Spline3D�𐶐������ꍇtrue/�R���X�g���N�^������Spline3D���n���ꂽ�ꍇ�Afalse */
    bool _is_create_sp;
    /** [r]�n�_X���W */
    coord _X_begin;
    /** [r]�n�_Y���W */
    coord _Y_begin;
    /** [r]�n�_Z���W */
    coord _Z_begin;
    float _rate_X;
    float _rate_Y;
    float _rate_Z;
    coord _offset_X;
    coord _offset_Y;
    coord _offset_Z;
    /**
     * �R���X�g���N�^ .
     * Spline3D�I�u�W�F�N�g�̎Q�Ƃ��ォ��ݒ肵�ĉ������B�isetSpline() ���\�b�h�Łj
     * @param prm_pActor_target �Ώۂ̃A�N�^�[
     */
    SplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target);


    /**
     * �R���X�g���N�^ .
     * �������������Spline3D�𐶐����X�v���C���Ȑ��⊮�_���v�Z���܂��B
     * Spline3D�I�u�W�F�N�g�̉���������ōs���܂��B
     * @param prm_pActor_target �Ώۂ̃A�N�^�[
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
     */
    SplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target,
                         double prm_paaCriteriaPoint[][3],
                         int prm_point_num,
                         double prm_accuracy);
    /**
     * �R���X�g���N�^ .
     * �����̐����ς�Spline3D�I�u�W�F�N�g�𗘗p���܂��BSpline3D�̉���́A�Ăяo�����ōs���Ă��������B
     * ��������̃I�u�W�F�N�g�ɓ���������������ꍇ�́A������̃R���X�g���N�^�Ő������ׂ��ł��B
     * @param prm_pActor_target �Ώۂ̃A�N�^�[
     * @param prm_sp �X�v���C���Ȑ��̕⊮�_�����A�ێ��N���X�̃C���X�^���X
     */
    SplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target,
                         Spline3D* prm_sp);


    /**
     * �X�v���C���Ȑ��S�̂��AX�������AY�������AZ���������ꂼ��ɉ��Z���A�␳���邱�Ƃ��o���܂��B
     * �f�t�H���g�� adjustAxisOffset(0, 0, 0) �ƂȂ�܂��B
     * �����v�Z�ł́A�{���\�b�h��adjustAxisOffset() ������� adjustAxisRate() ���s���A
     * �Ō�ɖ{���\�b�h�w��̃I�t�Z�b�g�������W���������܂��B
     * @param prm_offset_X X�������␳������
     * @param prm_offset_Y Y�������␳������
     * @param prm_offset_Z Z�������␳������
     */
    virtual void adjustAxisOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z);

    /**
     * �X�v���C���Ȑ��S�̂��AX�������AY�������AZ���������ꂼ��ɁA�������悶�␳���邱�Ƃ��o���܂��B
     * �f�t�H���g�� adjustAxisRate(1.0, 1.0, 1.0) �ƂȂ�܂��B
     * �����v�Z�ł́AadjustAxisOffset() ������� �{���\�b�h�� adjustAxisRate() ���s���܂��B
     * @param prm_rate_X X�������␳����
     * @param prm_rate_Y Y�������␳����
     * @param prm_rate_Z Z�������␳����
     */
    virtual void adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z);


    /**
     * �ΏۃA�N�^�[(_pActor_target)�̍��W���A�X�v���C���̈�ԍŏ��̊�_���W�Őݒ肷�� .
     * begin(0) �̏ꍇ�A�܂�u��΍��W�ړ��X�v���C���v�̏ꍇ�A�L���Ȑݒ�ƂȂ肤��ł��傤�B<BR>
     * �u��΍��W�ړ��X�v���C���v���܂�Ӗ�������܂���B<BR>
     */
    void setAbsoluteBeginCoordinate();

    /**
     * �ォ��X�v���C���I�u�W�F�N�g��ݒ�B
     * @param prm_sp
     */
    virtual void setSpline(Spline3D* prm_sp);

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����v���O���������s�J�n
     * @param prm_option �I�v�V���� ���ɈӖ������B���ʎ����g���p
     */
    virtual void begin(int prm_option = 0);

    /**
     * �ړ����s���\�b�h .
     * �ړ����s�����߂ɁA���t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave();

    /**
     * �X�v���C���ړ��v���O�������s����
     * @return true:���s�� / false:���s���I�����Ă���
     */
    bool isExecuting() {
        return _is_executing;
    }

    virtual ~SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
