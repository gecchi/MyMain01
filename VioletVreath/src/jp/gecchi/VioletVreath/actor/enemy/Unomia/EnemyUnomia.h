#ifndef ENEMYUNOMIA_H_
#define ENEMYUNOMIA_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A .
 * n * m �̕ґ��B
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyUnomia : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafDx::DriverLeader* pDriverLeader_;
    /** �e�X�g�b�N */
    GgafCore::ActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::ActorDepository* pDepo_effect_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyUnomia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �E�[�m�~�A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �E�[�m�~�A�̏�ԃ��Z�b�g���� .
     */
    void onReset() override;

    /**
     * �E�[�m�~�A���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �E�[�m�~�A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �E�[�m�~�A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �E�[�m�~�A�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pDriverLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafDx::DriverLeader* prm_pDriverLeader,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyUnomia();
};

}
#endif /*ENEMYUNOMIA_H_*/

