#ifndef ENEMYEBE_H_
#define ENEMYEBE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エーベ .
 * フェルマー螺旋。
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class EnemyEbe : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** 移動スプラインのシークエンスプログラム */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** 弾ストック */
    GgafCore::ActorDepository* pDepo_shot_;
    /** 弾発射効果エフェクト */
    GgafCore::ActorDepository* pDepo_effect_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyEbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * エーベの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エーベがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エーベの振る舞い .
     */
    void processBehavior() override;

    /**
     * エーベの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エーベの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pVehicleLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafDx::CurveManufacture*  prm_pCurveManufacture,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyEbe();
};

}
#endif /*ENEMYEBE_H_*/

