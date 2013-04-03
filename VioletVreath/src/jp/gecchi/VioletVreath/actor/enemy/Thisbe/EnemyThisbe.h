#ifndef ENEMYTHISBE_H_
#define ENEMYTHISBE_H_
namespace VioletVreath {


/**
 * 敵機シズビー .
 * ヒルベルトレーザーを撃ちます。
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyThisbe :  public GgafLib::DefaultMorphMeshActor {
//class EnemyThisbe : public GgafLib::CubeMapMorphMeshActor {

    /** 移動スプラインプログラム */
    GgafLib::SplineSequence* pSplSeq_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;


    DepositoryConnection* pConnection_LaserChipDepoStore_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    enum {
        PROG_WAIT = 1,
        PROG_OPEN,
        PROG_FIRE,
        PROG_CLOSE,
    };
    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
        SE_FIRE,
    };


public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyThisbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * シズビーの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * シズビーがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * シズビーの振る舞い .
     */
    void processBehavior() override;

    /**
     * シズビーの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * シズビーの衝突時処理 .
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
     * @param prm_pSplSeq
     */
    void setSplineSequence(GgafLib::SplineSequence* prm_pSplSeq) {
        pSplSeq_ = prm_pSplSeq;
    }

    /**
     * ショット発射効果エフェクト設定 .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_ShotEffect_ = prm_pDepo;
    }

    virtual ~EnemyThisbe();
};

}
#endif /*ENEMYTHISBE_H_*/

