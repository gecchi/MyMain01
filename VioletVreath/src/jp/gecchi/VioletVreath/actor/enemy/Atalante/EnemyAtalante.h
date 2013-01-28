#ifndef ENEMYATALANTE_H_
#define ENEMYATALANTE_H_
namespace VioletVreath {

/**
 * 敵機アタランテ .
 * ハッチ雑魚その１
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyAtalante : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT = 1  ,
        PROG_MOVE01_1,
        PROG_MOVE01_2,
        PROG_MOVE01_3,
        PROG_MOVE01_4,
        PROG_FINISH  ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;

    /** Y軸揃ったよフラグ */
    bool Y_ok_;
    /** Z軸揃ったよフラグ */
    bool Z_ok_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAtalante(const char* prm_name);

    void onCreateModel() override;

    /**
     * アタランテの初期処理（インスタンス生成後保証）
     */
    void initialize() override;


    /**
     * アタランテのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アタランテの振る舞い .
     */
    void processBehavior() override;

    /**
     * アタランテの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アタランテの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pDepo_Shot
     */
    virtual void config(
            GgafCore::GgafActorDepository* prm_pDepo_Shot
            );


    virtual ~EnemyAtalante();
};

}
#endif /*ENEMYATALANTE_H_*/

