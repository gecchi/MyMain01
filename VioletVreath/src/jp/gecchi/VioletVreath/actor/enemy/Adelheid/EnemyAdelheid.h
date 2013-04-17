#ifndef ENEMYADELHEID_H_
#define ENEMYADELHEID_H_
namespace VioletVreath {

/**
 * 敵機アーデルハイド .
 * 超連射68Kの３面の連なった編隊の敵の改！
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyAdelheid : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        PROG_MOVE01_1 = 1  ,
        PROG_SPLINE_MOVE   ,
        PROG_MOVE02_1      ,
        PROG_MOVE02_2      ,
    };

    enum {
        SE_DAMAGED   = 0,
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
    EnemyAdelheid(const char* prm_name);

    void onCreateModel() override;

    /**
     * アーデルハイドの初期処理（インスタンス生成後保証）
     */
    void initialize() override;


    /**
     * アーデルハイドのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アーデルハイドの振る舞い .
     */
    void processBehavior() override;

    /**
     * アーデルハイドの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アーデルハイドの衝突時処理 .
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


    virtual ~EnemyAdelheid();
};

}
#endif /*ENEMYADELHEID_H_*/

