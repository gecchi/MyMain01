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
        PROG_INIT,
        PROG_MOVING,
        PROG_MOVING_AFTER_LEAD,
    };

    enum {
        PROG2_WAIT,
        PROG2_OPEN,
        PROG2_SHOT,
        PROG2_CLOSE,
    };


    enum {
        MPH_CLOSE,
        MPH_OPEN,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    GgafCore::GgafProgress* pProg2_;

    /** 移動スプラインのシークエンスプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;

    FormationAdelheid* pFormation_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAdelheid(const char* prm_name);

    void onCreateModel() override;


    void nextFrame() override;
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
     * @param prm_pKurokoLeader
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_Shot
            );

    void open_shot();

    virtual ~EnemyAdelheid();
};

}
#endif /*ENEMYADELHEID_H_*/

