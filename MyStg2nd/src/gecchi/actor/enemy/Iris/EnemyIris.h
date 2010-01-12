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
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** 移動スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMove;
    /** 弾ストック */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_Shot;
    /** 弾発射効果エフェクト */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_ShotEffect;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    /**
     * イリスのが初期処理（インスタンス生成後保証）
     */
    void initialize();

    /**
     * イリスのがアクティブになった瞬間の処理 .
     */
    void onActive();

    /**
     * イリスの振る舞い .
     */
    void processBehavior();

    /**
     * イリスの振る舞い後の判定処理 .
     */
    void processJudgement();

    /**
     * イリスの衝突時処理 .
     * @param prm_pActor_Opponent 衝突対象
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    /**
     * 発射弾設定 .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つディスパッチャーのポインタ
     */
    void setDispatcher_Shot(GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * 効果エフェクト設定 .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つディスパッチャーのポインタ
     */
    void setDispatcher_ShotEffect(GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

