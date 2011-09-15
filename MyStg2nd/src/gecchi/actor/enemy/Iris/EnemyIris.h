#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * �G�@�C���X .
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshSetActor {
    /** �t�H�[���[�V����(��t�H�[���[�V��������NULL) */
    GgafDx9LibStg::FormationActor* _pFormation;
    /** �ړ��X�v���C���v���O���� */
    GgafDx9LibStg::SplineSequence* _pSplSeq;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* _pDepo_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* _pDepo_ShotEffect;
public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    void onCreateModel() override;

    /**
     * �C���X�̂����������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �C���X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �C���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �C���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �C���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual void config(
            GgafDx9LibStg::FormationActor* prm_pFormation,
            GgafDx9LibStg::SplineSequence* prm_pSplSeq,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        _pFormation = prm_pFormation;
        _pSplSeq = prm_pSplSeq;
        _pDepo_Shot = prm_pDepo_Shot;
        _pDepo_ShotEffect = prm_pDepo_ShotEffect;
    }

//    /**
//     * ���˒eDepository�ݒ� .
//     * initialize() �܂łɐݒ肵�ĉ������B
//     * @param prm_pDepo
//     */
//    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
//        _pDepo_Shot = prm_pDepo;
//    }
//
//    /**
//     * �X�v���C���ړ��ݒ� .
//     * initialize() �܂łɐݒ肵�ĉ������B
//     * @param prm_pSplSeq
//     */
//    void setSplineSequence(GgafDx9LibStg::SplineSequence* prm_pSplSeq) {
//        _pSplSeq = prm_pSplSeq;
//    }
//
//    /**
//     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
//     * @param prm_pDepo
//     */
//    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
//        _pDepo_ShotEffect = prm_pDepo;
//    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

