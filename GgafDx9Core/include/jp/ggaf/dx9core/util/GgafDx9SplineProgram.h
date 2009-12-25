#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �⊮�_�Ɉړ����邽�߁A���x���r���ƃJ�N�J�N�ł��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class GgafDx9SplineProgram : public GgafCore::GgafObject {

public:
    /** �X�v���C���Ȑ��̕⊮�_�����A�ێ�����N���X */
    GgafDx9Spline3D* _sp;
    /** begin()����̌o�߃t���[���� */
    DWORD _SPframe;
    /** ���݃v���O�������s���ł��邩�ǂ��� */
    boolean _is_executing;
    /** ���W�𑀍삷��ΏۂƂȂ�A�N�^�[ */
    GgafDx9GeometricActor* _pActor_target;
    /** �R���X�g���N�^������GgafDx9Spline3D�𐶐������ꍇtrue/�R���X�g���N�^������GgafDx9Spline3D���n���ꂽ�ꍇ�Afalse */
    bool _is_create_sp;

    /**
     * �R���X�g���N�^ .
     * GgafDx9Spline3D�I�u�W�F�N�g�̎Q�Ƃ��ォ��ݒ肵�ĉ������B
     */
    GgafDx9SplineProgram();


    /**
     * �R���X�g���N�^ .
     * �������������GgafDx9Spline3D�𐶐����X�v���C���Ȑ��⊮�_���v�Z���܂��B
     * GgafDx9Spline3D�I�u�W�F�N�g�̉���������ōs���܂��B
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
     */
    GgafDx9SplineProgram(double prm_paaCriteriaPoint[][3],
                            int prm_point_num,
                            double prm_accuracy);
    /**
     * �R���X�g���N�^ .
     * ������GgafDx9Spline3D�𗘗p���܂��BGgafDx9Spline3D�̉���́A�Ăяo�����ōs���Ă��������B
     * ��������̃I�u�W�F�N�g�ɓ���������������ꍇ�́A������̃R���X�g���N�^�Ő������ׂ��ł��B
     * @param prm_sp �X�v���C���Ȑ��̕⊮�_�����A�ێ��N���X�̃C���X�^���X
     */
    GgafDx9SplineProgram(GgafDx9Spline3D* prm_sp);


    virtual void setSpline(GgafDx9Spline3D* prm_sp);
    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����v���O���������s�J�n
     * @param prm_pActor_target �Ώۂ̃A�N�^�[
     * @param prm_option �I�v�V���� ���ɈӖ������B���ʎ����g���p
     */
    virtual void begin(GgafDx9GeometricActor* prm_pActor_target, int prm_option = 0);

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

    virtual ~GgafDx9SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
