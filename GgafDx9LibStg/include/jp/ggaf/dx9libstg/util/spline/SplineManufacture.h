#ifndef SPLINEMANUFACTURE_H_
#define SPLINEMANUFACTURE_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �⊮�_�Ɉړ����邽�߁A���x���r���ƃJ�N�J�N�ł��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::GgafObject {
private:
    SplineSourceConnection* _pSplineSourceConnection;
    SplineSource* _pSplineSource;
public:

    /** �X�v���C���Ȑ��̕⊮�_�����A�ێ�����N���X */
    Spline3D* _sp;
//    /** [r]�P��Ԃ̎g�p�\�t���[�� */
//    frame _SPframe_segment;

//    /** begin()����̌o�߃t���[���� */
//    frame _SPframe;
//    /** ���݃v���O�������s���ł��邩�ǂ��� */
//    bool _is_executing;
//    /** ���W�𑀍삷��ΏۂƂȂ�A�N�^�[ */
//    GgafDx9Core::GgafDx9GeometricActor* _pActor_target;
    /** �R���X�g���N�^������Spline3D�𐶐������ꍇtrue/�R���X�g���N�^������Spline3D���n���ꂽ�ꍇ�Afalse */
    bool _is_create_sp;
//    /** [r]�n�_X���W */
//    coord _X_begin;
//    /** [r]�n�_Y���W */
//    coord _Y_begin;
//    /** [r]�n�_Z���W */
//    coord _Z_begin;
    float _rate_X;
    float _rate_Y;
    float _rate_Z;

//    /**
//     * �R���X�g���N�^ .
//     * Spline3D�I�u�W�F�N�g�̎Q�Ƃ��ォ��ݒ肵�ĉ������B�isetSpline() ���\�b�h�Łj
//     * @param prm_pActor_target �Ώۂ̃A�N�^�[
//     */
//    SplineManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target);
//
//
//    /**
//     * �R���X�g���N�^ .
//     * �������������Spline3D�𐶐����X�v���C���Ȑ��⊮�_���v�Z���܂��B
//     * Spline3D�I�u�W�F�N�g�̉���������ōs���܂��B
//     * @param prm_pActor_target �Ώۂ̃A�N�^�[
//     * @param prm_paaCriteriaPoint ��_�z��
//     * @param prm_point_num  ��_�z��̗v�f��
//     * @param prm_accuracy  1��_�̐��x�i�r�� 1.0 �` 0.0 �ׂ���)�A
//     *                      ��_�Ɗ�_�̊Ԃ�1�Ƃ����ꍇ�́A�⊮�_�̓����i�ׂ₩���j���w��B
//     *                      1�̏ꍇ��_���玟��_�܂ŉ��������i�����j�B
//     *                      0.5 �Ƃ���Ɗ�_���玟��_�܂łɕ⊮�_��1����B
//     *                      0.1 �Ƃ���Ɗ�_�Ɗ�_�̊Ԃɕ⊮�_��9�B
//     */
//    SplineManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target,
//                         double prm_paaCriteriaPoint[][3],
//                         int prm_point_num,
//                         double prm_accuracy);
    /**
     * �R���X�g���N�^ .
     * �����̐����ς�Spline3D�I�u�W�F�N�g�𗘗p���܂��BSpline3D�̉���́A�Ăяo�����ōs���Ă��������B
     * ��������̃I�u�W�F�N�g�ɓ���������������ꍇ�́A������̃R���X�g���N�^�Ő������ׂ��ł��B
     * @param prm_pActor_target �Ώۂ̃A�N�^�[
     * @param prm_sp �X�v���C���Ȑ��̕⊮�_�����A�ێ��N���X�̃C���X�^���X
     */
//    SplineManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pActor,
//                      Spline3D* prm_sp,
//                      frame prm_spent_frame,
//                      ang_velo prm_ang_veloRzRyMv);
//    SplineManufacture();
    SplineManufacture(char* prm_idstr, const char* prm_sourceid);


    /**
     * �e�⊮�_��ǂݍ��ݎ��AX�������AY�������AZ���������ꂼ��Ɋ������悶�A�␳���܂� .
     * �f�t�H���g�� adjustAxisRate(1.0, 1.0, 1.0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * �����ŁAadjustCoodOffset() ������� �{���\�b�h�� adjustAxisRate() ���l������܂��B<BR>
     * �������̔{���␳ �� ���s�ړ��␳ �̏��Ԃł��B<BR>
     * @param prm_rate_X X�������␳����
     * @param prm_rate_Y Y�������␳����
     * @param prm_rate_Z Z�������␳����
     */
    virtual void adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z);


//    /**
//     * �ΏۃA�N�^�[(_pActor_target)�̍��W���A�X�v���C���̈�ԍŏ��̊�_���W�Őݒ肷�� .
//     * begin(0) �̏ꍇ�A�܂�u��΍��W�ړ��X�v���C���v�̏ꍇ�A�L���Ȑݒ�ƂȂ肤��ł��傤�B<BR>
//     * �u��΍��W�ړ��X�v���C���v���܂�Ӗ�������܂���B<BR>
//     */
//    void setAbsoluteBeginCoordinate();

    /**
     * �ォ��X�v���C���I�u�W�F�N�g��ݒ�B
     * @param prm_sp
     */
    virtual void setSpline(Spline3D* prm_sp);

//    /**
//     * �X�v���C���Ȑ��̕⊮�_���ړ�����v���O���������s�J�n
//     * @param prm_option �I�v�V���� ���ɈӖ������B���ʎ����g���p
//     */
//    virtual void begin(int prm_option = 0);
//
//    /**
//     * �ړ����s���\�b�h .
//     * �ړ����s�����߂ɁA���t���[�����̃��\�b�h���Ăяo���K�v������܂��B
//     */
//    virtual void behave();
//
//    /**
//     * �X�v���C���ړ��v���O�������s����
//     * @return true:���s�� / false:���s���I�����Ă���
//     */
//    bool isExecuting() {
//        return _is_executing;
//    }
    virtual void calculate() = 0;
    virtual SplineProgram* createSplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor) = 0;


    virtual ~SplineManufacture();
};

}
#endif /*SPLINEMANUFACTURE_H_*/
