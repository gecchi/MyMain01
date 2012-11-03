#ifndef ENEMYSYLVIAEYE_H_
#define ENEMYSYLVIAEYE_H_
namespace VioletVreath {


/**
 * �g�[���X�̖ڋ� .
 * @version 1.00
 * @since 2012/10/16
 * @author Masatoshi Tsuge
 */
class EnemySylviaEye :
  public GgafLib::DefaultMorphMeshActor {
    /** �e���ˑO���ߌ��ʃG�t�F�N�g */
    EffectSylviaEye001* pEffect_;

public:
    enum {
        PROG_MOVE = 1  ,
        PROG_OPEN ,
        PROG_TURN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_FIRE_END,
        PROG_CLOSE     ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
        SE_FIRE,
    };
    bool is_wake_;
    EnemySylvia* pSylvia_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemySylviaEye(const char* prm_name, EnemySylvia* prm_pSylvia);

    void onCreateModel() override;

    /**
     * �g�[���X�A�C�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �g�[���X�A�C���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �g�[���X�A�C�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �g�[���X�A�C�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �g�[���X�A�C�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void wake();

    virtual ~EnemySylviaEye();
};

}
#endif /*ENEMYSYLVIAEYE_H_*/
