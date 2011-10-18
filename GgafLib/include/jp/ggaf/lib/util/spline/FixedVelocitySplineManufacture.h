#ifndef FIXEDVELOCITYSPLINEMANUFACTURE_H_
#define FIXEDVELOCITYSPLINEMANUFACTURE_H_
namespace GgafLib {

/**
 * �����ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineManufacture : public SplineManufacture {

public:
    /** [r]���݂̕⊮�_(��_���܂�)����A���̕⊮�_(or��_)�܂ł̋����̃e�[�u�� */
    coord* _paDistace_to;
    /** [r]�n�_����n�Ԗڂ̕⊮�_(��_���܂�)���B�ɕK�v�ȃt���[�����̃e�[�u�� */
    float* _paFrame_need_at;
    /** [r]����x */
    velo _veloMvUnit;
    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
    ang_velo _ang_veloRzRyMv;
        /** [rw]������@ */
    int _turn_way;
    /** [rw]����œK���L�� */
    bool _turn_optimize;
    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;

    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��
     * @param prm_ang_veloRzRyMv �A�N�^�[�̐���p�x
     */
    FixedVelocitySplineManufacture(const char* prm_source_file,
                                   ang_velo prm_ang_veloRzRyMv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    FixedVelocitySplineManufacture(SplineSource* prm_pSplSrc,
                                   ang_velo prm_ang_veloRzRyMv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * SplineSequence�I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� FixedVelocitySplineSequence �ł��B
     * @param prm_pKurokoA �X�v���C���ړ�������ΏۃA�N�^�[
     * @return SplineSequence�I�u�W�F�N�g
     */
    SplineSequence* createSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) override;

    virtual ~FixedVelocitySplineManufacture();
};

}
#endif /*FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
