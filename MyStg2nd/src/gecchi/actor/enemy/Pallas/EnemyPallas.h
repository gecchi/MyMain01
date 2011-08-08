#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace MyStg2nd {

/**
 * �G�@�p���X .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyPallas : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx9LibStg::SplineProgram* _pSplProgram;
    /** �e�X�g�b�N */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorStore* _pStore_ShotEffect;

    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyPallas(const char* prm_name);

    void onCreateModel() override;

    /**
     * �p���X�̂����������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �p���X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �p���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �p���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �p���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pSplProgram
     * @param prm_pStore_Shot
     * @param prm_pStore_ShotEffect
     */
    virtual void config(
            GgafDx9LibStg::SplineProgram* prm_pSplProgram,
            GgafCore::GgafActorStore* prm_pStore_Shot,
            GgafCore::GgafActorStore* prm_pStore_ShotEffect
            ) {
        _pSplProgram = prm_pSplProgram;
        _pStore_Shot = prm_pStore_Shot;
        _pStore_ShotEffect = prm_pStore_ShotEffect;
    }


    virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

