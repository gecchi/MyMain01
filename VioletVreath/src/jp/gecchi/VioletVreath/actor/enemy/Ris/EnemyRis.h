#ifndef ENEMYRIS_H_
#define ENEMYRIS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機リス .
 * フローラを弾として出す。
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyRis : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

//    /** フォーメーション(非フォーメーション時はnullptr) */
//    GgafLib::TreeFormation* pFormation_;
    /** 移動スプラインプログラム */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** 弾ストック */
    GgafCore::ActorDepository* pDepo_shot_;
    /** 弾発射効果エフェクト */
    GgafCore::ActorDepository* pDepo_effect_;

public:
    /** 行動パターン番号 */
    int iMovePatternNo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyRis(const char* prm_name);

    void onCreateModel() override;

    /**
     * リスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * リスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * リスの振る舞い .
     */
    void processBehavior() override;

    /**
     * リスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    void onInactive() override;


    virtual void config(
            GgafDx::VehicleLeader* prm_pVehicleLeader,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            ) {
        pVehicleLeader_ = prm_pVehicleLeader;
        pDepo_shot_ = prm_pDepo_shot;
        pDepo_effect_ = prm_pDepo_shotEffect;
    }

    virtual ~EnemyRis();
};

}
#endif /*ENEMYRIS_H_*/

