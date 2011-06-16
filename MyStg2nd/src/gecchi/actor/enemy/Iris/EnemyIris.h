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

    /** 移動スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** 弾ストック */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorStore* _pStore_ShotEffect;
public:
    /** 行動パターン番号 */
    int _iMovePatternNo;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    void onCreateModel() override;

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
     * 発射弾Store設定 .
     * initialize() までに設定して下さい。
     * @param prm_pStore
     */
    void setStore_Shot(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_Shot = prm_pStore;
    }

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pSplineProgram
     */
    void setSplineProgram(GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram) {
        _pSplineProgram = prm_pSplineProgram;
    }

    /**
     * ショット発射効果エフェクト設定 .
     * @param prm_pStore
     */
    void setStore_ShotEffect(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_ShotEffect = prm_pStore;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

