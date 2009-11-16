#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �⊮�_�Ɉړ����邽�߁A���x���r���ƃJ�N�J�N�ł��B
 */
class GgafDx9SplineProgram : public GgafCore::GgafObject {

public:

    GgafDx9Spline3D* _sp;
    DWORD _SPframe;
    boolean _is_executing;
    GgafDx9GeometricActor* _pActor_target;
    bool _is_create_sp;

    GgafDx9SplineProgram();


    /**
     *
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
     *
     * @param prm_sp
     * @return
     */
    GgafDx9SplineProgram(GgafDx9Spline3D* prm_sp);

    /**
     * �X�v���C���Ȑ����p�ړ��v���O�����J�n
     * @param prm_pActor_target �Ώۂ̃A�N�^�[
     * @param prm_option �I�v�V���� ���ɈӖ������B���ʎ����p
     */
    virtual void begin(GgafDx9GeometricActor* prm_pActor_target, int prm_option = 0);

    /**
     * ���t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave();

    virtual ~GgafDx9SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
