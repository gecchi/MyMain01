#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9Core {

class GgafDx9SplineProgram : public GgafCore::GgafObject {

public:

    GgafDx9Spline3D* _sp;
    DWORD _SPframe_segment;
    DWORD _SPframe;
    int* _paSPDistaceTo;
    velo* _paSPMoveVelocityTo;
    boolean _is_executing;
    GgafDx9GeometricActor* _pActor_executing;
    angvelo _angRotMove;

    /** ���Έړ��t���O */
    boolean _is_relative;
    int _X_relative;
    int _Y_relative;
    int _Z_relative;

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
     * @param prm_paaCriteriaPoint �n�_����I�_�ֈړ�����̂ɔ�₷�t���[����
     * @param prm_angRotMove �⊮�_�ւ̕����x�N�g���Ƀ^�[�Q���e�B���O����ۂ́A����\��1�t���[��������̉�]�ړ��p
     */
    GgafDx9SplineProgram(double prm_paaCriteriaPoint[][3],
                         int prm_point_num,
                         double prm_accuracy,
                         DWORD prm_spent_frame,
                         angvelo prm_angRotMove);


    void beginSplineCurveAbsolute(GgafDx9GeometricActor* _pActor);
    void beginSplineCurveRelative(GgafDx9GeometricActor* _pActor);
    void behave();


    /**
     *
     * @param prm_paaCriteriaPoint ��_�z��
     * @param prm_point_num  ��_�z��̗v�f��
     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
     * @param prm_paaCriteriaPoint ��_�����_�ֈړ�����̂ɔ�₷�t���[����
     */

    virtual ~GgafDx9SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
