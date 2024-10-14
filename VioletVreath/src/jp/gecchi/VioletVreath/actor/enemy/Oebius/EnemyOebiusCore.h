#ifndef ENEMYOEBIUSCORE_H_
#define ENEMYOEBIUSCORE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * エビウスのコア .
 * @version 1.00
 * @since 2014/11/11
 * @author Masatoshi Tsuge
 */
class EnemyOebiusCore : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    EnemyOebiusController* pController_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOebiusCore(const char* prm_name, EnemyOebiusController* prm_pController);

    void onCreateModel() override;

    /**
     * エビウスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エビウスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エビウスの振る舞い .
     */
    void processBehavior() override;

    /**
     * エビウスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エビウスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOebiusCore();
};

}
#endif /*ENEMYOEBIUSCORE_H_*/

