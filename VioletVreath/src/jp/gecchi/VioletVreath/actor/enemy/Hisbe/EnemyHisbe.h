#ifndef ENEMYHISBE_H_
#define ENEMYHISBE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {


/**
 * 敵機ヒズビー .
 * ヒルベルトレーザーを撃ちます。
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyHisbe :  public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {
//class EnemyHisbe : public VvEnemyActor<GgafLib::CubeMapMorphMeshActor> {

    /** 移動スプラインプログラム */
    GgafLib::SplineLeader* pRikishaLeader_;
    /** 弾ストック */
    GgafCore::ActorDepository* pDepo_shot_;
    /** 弾発射効果エフェクト */
    GgafCore::ActorDepository* pDepo_effect_;


    DepositoryConnection* pConn_pDepoStore_laser_set;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHisbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * ヒズビーの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ヒズビーがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ヒズビーの振る舞い .
     */
    void processBehavior() override;

    /**
     * ヒズビーの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ヒズビーの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 発射弾Depository設定 .
     * initialize() までに設定して下さい。
     * @param prm_pDepo
     */
    void setDepository_Shot(GgafCore::ActorDepository* prm_pDepo) {
        pDepo_shot_ = prm_pDepo;
    }

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pRikishaLeader
     */
    void setSplineRikishaLeader(GgafLib::SplineLeader* prm_pRikishaLeader) {
        pRikishaLeader_ = prm_pRikishaLeader;
    }

    /**
     * ショット発射効果エフェクト設定 .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::ActorDepository* prm_pDepo) {
        pDepo_effect_ = prm_pDepo;
    }

    virtual ~EnemyHisbe();
};

}
#endif /*ENEMYHISBE_H_*/

