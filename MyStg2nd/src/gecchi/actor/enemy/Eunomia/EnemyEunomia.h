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
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** 弾ストック */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;

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
     * @param prm_pDispatcher_Shot
     * @param prm_pDispatcher_ShotEffect
     */
    virtual void config(
            GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_Shot,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_ShotEffect
            ) {
        _pSplineProgram = prm_pSplineProgram;
        _pDispatcher_Shot = prm_pDispatcher_Shot;
        _pDispatcher_ShotEffect = prm_pDispatcher_ShotEffect;
    }


    virtual ~EnemyEunomia();
};

}
#endif /*ENEMYEUNOMIA_H_*/

