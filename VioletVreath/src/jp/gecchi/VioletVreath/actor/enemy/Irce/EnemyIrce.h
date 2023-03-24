#ifndef ENEMYIRCE_H_
#define ENEMYIRCE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機イルケ .
 * 最初に作った敵
 * @version 1.00
 * @since 2010/03/25
 * @author Masatoshi Tsuge
 */
class EnemyIrce : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** 行動パターン番号 */
    int iMovePatternNo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIrce(const char* prm_name);

    /**
     * イルケモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * イルケの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * イルケがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * イルケの振る舞い .
     */
    void processBehavior() override;


    /**
     * イルケの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * イルケの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyIrce();
};

}
#endif /*ENEMYIRCE_H_*/

