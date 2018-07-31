#ifndef ENEMYUNOMIA_H_
#define ENEMYUNOMIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア .
 * n * m の編隊。
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyUnomia : public GgafLib::DefaultMassMeshActor {

public:
    /** 移動スプラインのシークエンスプログラム */
    GgafLib::SplineLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_effect_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyUnomia(const char* prm_name);

    void onCreateModel() override;

    /**
     * ウーノミアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ウーノミアの状態リセット処理 .
     */
    void onReset() override;

    /**
     * ウーノミアがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ウーノミアの振る舞い .
     */
    void processBehavior() override;

    /**
     * ウーノミアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ウーノミアの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafLib::SplineLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_shot,
            GgafCore::GgafActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyUnomia();
};

}
#endif /*ENEMYUNOMIA_H_*/

