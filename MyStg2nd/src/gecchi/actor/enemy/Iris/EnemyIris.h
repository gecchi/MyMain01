#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * 敵機イリス .
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** 初期処理(同クラスで全体で１回実行)フラグ */
    static bool _is_init_class;
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** 移動スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMove;
    /** 弾ストック */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    void initEnemyIrisClass();

    /**
     * イリスのが初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * イリスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * イリスの振る舞い .
     */
    void processBehavior() override;

    /**
     * イリスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * イリスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 発射弾設定 .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つディスパッチャーのポインタ
     */
    void setDispatcher_Shot(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * 効果エフェクト設定 .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つディスパッチャーのポインタ
     */
    void setDispatcher_ShotEffect(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

