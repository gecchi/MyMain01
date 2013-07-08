#ifndef ENEMYHISBE_H_
#define ENEMYHISBE_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {


/**
 * 敵機ヒズビー .
 * ヒルベルトレーザーを撃ちます。
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyHisbe :  public GgafLib::DefaultMorphMeshActor {
//class EnemyHisbe : public GgafLib::CubeMapMorphMeshActor {

    /** 移動スプラインプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;


    DepositoryConnection* pConn_LaserChipDepoStore_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    enum {
        PROG_WAIT,
        PROG_OPEN,
        PROG_FIRE,
        PROG_CLOSE,
    };
    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };


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
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 発射弾Depository設定 .
     * initialize() までに設定して下さい。
     * @param prm_pDepo
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_Shot_ = prm_pDepo;
    }

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pKurokoLeader
     */
    void setSplineKurokoLeader(GgafLib::SplineKurokoLeader* prm_pKurokoLeader) {
        pKurokoLeader_ = prm_pKurokoLeader;
    }

    /**
     * ショット発射効果エフェクト設定 .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_ShotEffect_ = prm_pDepo;
    }

    virtual ~EnemyHisbe();
};

}
#endif /*ENEMYHISBE_H_*/

