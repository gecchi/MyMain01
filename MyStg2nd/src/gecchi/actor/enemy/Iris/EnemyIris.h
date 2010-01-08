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
    /** スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMove;
    /** 弾ストック */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_Shot;
    /** 効果エフェクト */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_ShotEffect;

    EnemyIris(const char* prm_name);

    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

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

