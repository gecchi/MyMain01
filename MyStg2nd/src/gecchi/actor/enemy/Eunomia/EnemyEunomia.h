#ifndef ENEMYEUNOMIA_H_
#define ENEMYEUNOMIA_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyEunomia : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** 移動スプラインプログラム */
    GgafDx9Core::SplineProgram* _pSplineProgram;
    /** 弾ストック */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorStore* _pStore_ShotEffect;

    /** 行動パターン番号 */
    int _iMovePatternNo;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyEunomia(const char* prm_name);

    void onCreateModel() override;

    /**
     * エウノミアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エウノミアの状態リセット処理 .
     */
    void onReset() override;

    /**
     * エウノミアのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エウノミアの振る舞い .
     */
    void processBehavior() override;

    /**
     * エウノミアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エウノミアの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pSplineProgram
     * @param prm_pStore_Shot
     * @param prm_pStore_ShotEffect
     */
    virtual void config(
            GgafDx9Core::SplineProgram* prm_pSplineProgram,
            GgafCore::GgafActorStore* prm_pStore_Shot,
            GgafCore::GgafActorStore* prm_pStore_ShotEffect
            ) {
        _pSplineProgram = prm_pSplineProgram;
        _pStore_Shot = prm_pStore_Shot;
        _pStore_ShotEffect = prm_pStore_ShotEffect;
    }


    virtual ~EnemyEunomia();
};

}
#endif /*ENEMYEUNOMIA_H_*/

