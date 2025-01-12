#ifndef ENEMYASSALIABASE_H_
#define ENEMYASSALIABASE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * エミリア .
 * 隕石群の隕石
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaBase : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

protected:
    virtual void processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) = 0;
public:
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo R_mv_velo_;
    EnemyEmiliaBase* pOrg_;
    FormationEmilia* pFormationEmilia_;
public:
    EnemyEmiliaBase(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    /**
     * エミリアがでポジトリから取得された際に呼び出されるコールバック .
     * @param prm_pFormationEmilia でポジトリから取得を行ったフォーメーション（グループ）への参照
     * @param prm_pOrg 分裂元になったエミリア(nullptr:大元)
     */
    virtual void onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia);


    void updateRankParameter();

    virtual void onCreateModel() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    virtual void onInactive() override;

    virtual ~EnemyEmiliaBase();
};

}
#endif /*ENEMYASSALIABASE_H_*/

