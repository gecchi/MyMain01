#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_
namespace MyStg2nd {


/**
 * 敵機タリア .
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyThalia : public GgafDx9LibStg::DefaultMorphMeshActor {
//class EnemyThalia : public GgafDx9LibStg::CubeMapMorphMeshActor {
    /** 移動スプラインプログラム */
    GgafDx9LibStg::SplineSequence* _pSplSeq;
    /** 弾ストック */
    GgafCore::GgafActorDepository* _pDepo_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* _pDepo_ShotEffect;

    /** 原点から初期カメラZ位置の距離 */
    int _dZ_camera_init;
public:
    /** 行動パターン番号 */
    int _iMovePatternNo;

    velo _veloTopMv;

    GgafDx9LibStg::LaserChipDepository* _pLaserChipDepo;
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
        _pDepo_Shot = prm_pDepo;
    }

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pSplSeq
     */
    void setSplineSequence(GgafDx9LibStg::SplineSequence* prm_pSplSeq) {
        _pSplSeq = prm_pSplSeq;
    }

    /**
     * ショット発射効果エフェクト設定 .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        _pDepo_ShotEffect = prm_pDepo;
    }

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

