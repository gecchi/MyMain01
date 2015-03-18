#ifndef ENEMYRATISLAVIAEYE_H_
#define ENEMYRATISLAVIAEYE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �g�[���X�̖ڋ� .
 * @version 1.00
 * @since 2012/10/16
 * @author Masatoshi Tsuge
 */
class EnemyRatislaviaEye : public GgafLib::DefaultMorphMeshActor {
    /** �e���ˑO���ߌ��ʃG�t�F�N�g */
    EffectRatislaviaEye001* pEffect_;

public:
    enum {
        PROG_MOVE ,
        PROG_OPEN ,
        PROG_TURN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_FIRE_END  ,
        PROG_CLOSE     ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };
    bool is_wake_;
    EnemyRatislavia* pRatislavia_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia);

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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void wake();

    virtual ~EnemyRatislaviaEye();
};

}
#endif /*ENEMYRATISLAVIAEYE_H_*/

