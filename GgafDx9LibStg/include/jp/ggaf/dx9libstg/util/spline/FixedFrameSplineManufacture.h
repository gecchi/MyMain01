#ifndef FIXEDFRAMESPLINEMANUFACTURE_H_
#define FIXEDFRAMESPLINEMANUFACTURE_H_
namespace GgafDx9LibStg {

/**
 * ��ԌŒ莞�ԁi�t���[���j�ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineManufacture : public SplineManufacture {

public:
    /** [r]�P��Ԃ̎g�p�\�t���[�� */
    frame _SPframe_segment;
    /** [r]���̕⊮�_�܂ł̋����̃e�[�u�� */
    coord* _paDistace_to;
    /** [r]���̕⊮�_���B�ɕK�v�Ȉړ����x�̃e�[�u�� */
    velo* _paSPMvVeloTo;
    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
    ang_velo _ang_veloRzRyMv;
    /** [r]�ŏI�n�_�����܂ł̃t���[���� */
    frame _spent_frame;
    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��
     * @param prm_spent_frame �ŏI�n�_�����܂ł̃t���[����
     * @param prm_ang_veloRzRyMv �A�N�^�[�̐���p�x
     */
    FixedFrameSplineManufacture(const char* prm_source_file, frame prm_spent_frame, ang_velo prm_ang_veloRzRyMv);
    FixedFrameSplineManufacture(SplineSource* prm_pSplineSource, frame prm_spent_frame, ang_velo prm_ang_veloRzRyMv);

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * SplineSequence�I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� FixedFrameSplineManufacture �ł��B
     * @param prm_pForWhichActor �X�v���C���ړ�������ΏۃA�N�^�[
     * @return SplineSequence�I�u�W�F�N�g
     */
    SplineSequence* createSplineSequence(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor) override;

    virtual ~FixedFrameSplineManufacture();
};

}
#endif /*FIXEDFRAMESPLINEMANUFACTURE_H_*/
