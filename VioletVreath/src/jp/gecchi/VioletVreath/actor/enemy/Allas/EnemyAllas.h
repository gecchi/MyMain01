#ifndef ENEMYALLAS_H_
#define ENEMYALLAS_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機アラス .
 * 羽の多いファン
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyAllas : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** 移動スプラインプログラム */
    GgafLib::SplineLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::ActorDepository* pDepo_shot_;
    /** 弾発射効果エフェクト */
    GgafCore::ActorDepository* pDepo_effect_;
    /** 行動パターン番号 */
    int iMovePatternNo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAllas(const char* prm_name);

    void onCreateModel() override;

    /**
     * アラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アラスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * アラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アラスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafLib::SplineLeader* prm_pKurokoLeader,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            ) {
        pKurokoLeader_ = prm_pKurokoLeader;
        pDepo_shot_ = prm_pDepo_shot;
        pDepo_effect_ = prm_pDepo_shotEffect;
    }


    virtual ~EnemyAllas();
};

}
#endif /*ENEMYALLAS_H_*/

