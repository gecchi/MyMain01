#ifndef ENEMYTORUSEYE_H_
#define ENEMYTORUSEYE_H_
namespace VioletVreath {


/**
 * トーラスの目玉 .
 * @version 1.00
 * @since 2012/10/16
 * @author Masatoshi Tsuge
 */
class EnemyTorusEye :
  public GgafLib::DefaultMorphMeshActor {
    /** 弾発射前溜め効果エフェクト */
    EffectTorusEye001* pEffect_;

public:
    enum {
        PROG_MOVE = 1  ,
        PROG_OPEN ,
        PROG_TURN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_FIRE_END,
        PROG_CLOSE     ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
        SE_FIRE,
    };
    bool is_wake_;
    Torus* pTorus_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyTorusEye(const char* prm_name, Torus* prm_pTorus);

    void onCreateModel() override;

    /**
     * トーラスアイの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * トーラスアイがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * トーラスアイの振る舞い .
     */
    void processBehavior() override;

    /**
     * トーラスアイの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * トーラスアイの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void wake();

    virtual ~EnemyTorusEye();
};

}
#endif /*ENEMYTORUSEYE_H_*/

