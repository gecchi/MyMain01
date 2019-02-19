#ifndef ENEMYASSALIABASE_H_
#define ENEMYASSALIABASE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �G�~���A .
 * 覐ΌQ��覐�
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaBase : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

protected:
    virtual void processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) = 0;
public:
    /** �ґ������o�[�̏����ړ����x(RANK�ϓ�) */
    velo R_mv_velo_;
    EnemyEmiliaBase* pOrg_;
    FormationEmilia* pFormationEmilia_;
public:
    EnemyEmiliaBase(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    /**
     * �G�~���A���Ń|�W�g������擾���ꂽ�ۂɌĂяo�����R�[���o�b�N .
     * @param prm_pFormationEmilia �Ń|�W�g������擾���s�����t�H�[���[�V�����i�O���[�v�j�ւ̎Q��
     * @param prm_pOrg ���􌳂ɂȂ����G�~���A(nullptr:�匳)
     */
    virtual void onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia);


    void updateRankParameter();

    virtual void onCreateModel() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual void onInactive() override;

    virtual ~EnemyEmiliaBase();
};

}
#endif /*ENEMYASSALIABASE_H_*/

