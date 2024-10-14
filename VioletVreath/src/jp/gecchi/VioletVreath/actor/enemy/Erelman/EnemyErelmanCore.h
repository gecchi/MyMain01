#ifndef ENEMYERELMANCORE_H_
#define ENEMYERELMANCORE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * エレルマンのコア .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanCore : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    EnemyErelmanController* pController_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErelmanCore(const char* prm_name, EnemyErelmanController* prm_pController);

    void onCreateModel() override;

    /**
     * エレルマンの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エレルマンがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エレルマンの振る舞い .
     */
    void processBehavior() override;

    /**
     * エレルマンの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エレルマンの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyErelmanCore();
};

}
#endif /*ENEMYERELMANCORE_H_*/

