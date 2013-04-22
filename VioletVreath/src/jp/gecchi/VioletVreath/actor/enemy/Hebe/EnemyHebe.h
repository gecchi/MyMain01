#ifndef ENEMYHEBE_H_
#define ENEMYHEBE_H_
namespace VioletVreath {

/**
 * 敵機ヘーベ .
 * フェルマー螺旋。
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class EnemyHebe : public GgafLib::DefaultMeshSetActor {

public:

    enum {
        PROG_MOVE01_1   ,
        PROG_SPLINE_MOVE,
        PROG_MOVE02_1   ,
        PROG_MOVE02_2   ,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** 移動スプラインのシークエンスプログラム */
    GgafLib::SplineKurokoStepper* pKurokoStepper_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHebe(const char* prm_name);

    void onCreateModel() override;

    /**
     * ヘーベの初期処理（インスタンス生成後保証）
     */
    void initialize() override;


    /**
     * ヘーベのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ヘーベの振る舞い .
     */
    void processBehavior() override;

    /**
     * ヘーベの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ヘーベの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoStepper
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoStepper* prm_pKurokoStepper,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            );


    virtual ~EnemyHebe();
};

}
#endif /*ENEMYHEBE_H_*/

