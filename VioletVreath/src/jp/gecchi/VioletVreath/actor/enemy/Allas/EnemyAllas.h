#ifndef ENEMYALLAS_H_
#define ENEMYALLAS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
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
    GgafDx::VehicleLeader* pVehicleLeader_;
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
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pVehicleLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafDx::CurveManufacture* prm_pCurveManufacture,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyAllas();
};

}
#endif /*ENEMYALLAS_H_*/

