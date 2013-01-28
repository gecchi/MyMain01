#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace VioletVreath {

/**
 * 敵機パラス .
 * 羽の多いファン
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyPallas :
    public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION = 0,
    };

    /** 移動スプラインプログラム */
    GgafLib::SplineSequence* pSplSeq_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;
    /** 行動パターン番号 */
    int iMovePatternNo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyPallas(const char* prm_name);

    void onCreateModel() override;

    /**
     * パラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * パラスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * パラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * パラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * パラスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pSplSeq
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineSequence* prm_pSplSeq,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        pSplSeq_ = prm_pSplSeq;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }


    virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

