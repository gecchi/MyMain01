#ifndef ENEMYIDA_H_
#define ENEMYIDA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機イーダ .
 * スペハリのIDAみたいなんでいこうか。
 * 最初のFKフォーメション。
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIda : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIda(const char* prm_name);

    void onCreateModel() override;

    /**
     * イーダの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * イーダがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * イーダの振る舞い .
     */
    void processBehavior() override;

    /**
     * イーダの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * イーダの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyIda();
};

}
#endif /*ENEMYIDA_H_*/

