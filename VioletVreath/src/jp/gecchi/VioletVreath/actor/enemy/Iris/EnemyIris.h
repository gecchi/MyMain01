#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace VioletVreath {

/**
 * 敵機イリス .
 * フローラを弾として出す。
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyIris :
  public GgafLib::DefaultMeshSetActor {

//    /** フォーメーション(非フォーメーション時はNULL) */
//    GgafLib::TreeFormation* pFormation_;
    /** 移動スプラインプログラム */
    GgafLib::SplineSequence* pSplSeq_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;
public:

    enum {
        SE_EXPLOSION = 0,
    };

    /** 行動パターン番号 */
    int iMovePatternNo_;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    void onCreateModel() override;

    /**
     * イリスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * イリスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * イリスの振る舞い .
     */
    void processBehavior() override;

    /**
     * イリスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * イリスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual void config(
            GgafLib::SplineSequence* prm_pSplSeq,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        pSplSeq_ = prm_pSplSeq;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

