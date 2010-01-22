#ifndef ENEMYTAMAGO01_H_
#define ENEMYTAMAGO01_H_
namespace MyStg2nd {

/**
 * テスト用 .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyTamago01 : public GgafDx9LibStg::DefaultMeshActor {

public:
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** 移動スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_Tamago01Move;
    /** 弾ストック */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_Shot;
    /** 弾発射効果エフェクト */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_ShotEffect;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyTamago01(const char* prm_name);

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
    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

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

    virtual ~EnemyTamago01();
};

}
#endif /*ENEMYTAMAGO01_H_*/

