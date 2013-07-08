#ifndef ENEMYALLAS_H_
#define ENEMYALLAS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�A���X .
 * �H�̑����t�@��
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyAllas : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAllas(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A���X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoLeader
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        pKurokoLeader_ = prm_pKurokoLeader;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }


    virtual ~EnemyAllas();
};

}
#endif /*ENEMYALLAS_H_*/

