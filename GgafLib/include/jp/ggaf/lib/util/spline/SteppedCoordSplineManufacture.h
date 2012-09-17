#ifndef STEPPEDCOORDSPLINEMANUFACTURE_H_
#define STEPPEDCOORDSPLINEMANUFACTURE_H_
namespace GgafLib {

/**
 * �����ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineManufacture : public SplineManufacture {

public:
    /** [r]���݂̕⊮�_(��_���܂�)����A���̕⊮�_(or��_)�܂ł̋����̃e�[�u�� */
    coord* _paDistace_to;
    /** [r]�n�_����n�Ԗڂ̕⊮�_(��_���܂�)���B�ɕK�v�ȃt���[�����̃e�[�u�� */
    float* _paFrame_need_at;
    /** [r]����x */
//    velo _veloMvUnit;
    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
//    angvelo _angveloRzRyMv;
        /** [rw]������@ */
    int _turn_way;
    /** [rw]����œK���L�� */
    bool _turn_optimize;
    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;

    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��
     * @param prm_angveloRzRyMv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g true)
     */
    SteppedCoordSplineManufacture(const char* prm_source_file,
//                                   angvelo prm_angveloRzRyMv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    /**
     *
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     * @param prm_angveloRzRyMv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g true)
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSplSrc,
//                                   angvelo prm_angveloRzRyMv = (D90ANG/9),
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
     * �C���X�^���X�� SteppedCoordSplineSequence �ł��B
     * @param prm_pKurokoA �X�v���C���ړ�������ΏۃA�N�^�[
     * @return SplineSequence�I�u�W�F�N�g
     */
    SplineSequence* createSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) override;

    virtual ~SteppedCoordSplineManufacture();
};

}
#endif /*FIXEDVELOCITYSPLINEMANUFACTURE_H_*/