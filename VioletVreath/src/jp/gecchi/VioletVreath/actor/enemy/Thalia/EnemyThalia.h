#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_
namespace VioletVreath {


/**
 * 敵機タリア .
 * スペハリのトモスもどき
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyThalia :
  public GgafLib::DefaultMorphMeshActor {
//class EnemyThalia : public GgafLib::CubeMapMorphMeshActor {
    /** 移動スプラインプログラム */
    GgafLib::SplineSequence* pSplSeq_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

    /** 原点から初期カメラZ位置の距離 */
    int dZ_camera_init_;
public:
    enum {
        PROG_MOVE = 1  ,
        PROG_TURN_OPEN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_CLOSE     ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
        SE_FIRE,
    };
    /** 行動パターン番号 */
    int iMovePatternNo_;

    velo veloTopMv_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyThalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * タリアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * タリアがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * タリアの振る舞い .
     */
    void processBehavior() override;

    /**
     * タリアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * タリアの衝突時処理 .
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

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

