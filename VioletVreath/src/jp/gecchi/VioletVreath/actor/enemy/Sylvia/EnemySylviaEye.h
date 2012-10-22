#ifndef ENEMYSYLVIAEYE_H_
#define ENEMYSYLVIAEYE_H_
namespace VioletVreath {


/**
 * トーラスの目玉 .
 * @version 1.00
 * @since 2012/10/16
 * @author Masatoshi Tsuge
 */
class EnemySylviaEye :
  public GgafLib::DefaultMorphMeshActor {
    /** 弾発射前溜め効果エフェクト */
    EffectSylviaEye001* pEffect_;

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
    EnemySylvia* pSylvia_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemySylviaEye(const char* prm_name, EnemySylvia* prm_pSylvia);

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

    virtual ~EnemySylviaEye();
};

}
#endif /*ENEMYSYLVIAEYE_H_*/

