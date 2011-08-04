#ifndef ENEMYTAMAGO01_H_
#define ENEMYTAMAGO01_H_
namespace MyStg2nd {

/**
 * テスト用 .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyTamago01 : public GgafDx9LibStg::SpriteMeshSetActor {

public:
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** 移動スプラインプログラム */
    GgafDx9Core::SplineProgram* _pProgram_Tamago01Move;
    /** 弾ストック */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorStore* _pStore_ShotEffect;

    StoreConnection* _pStoreCon;


    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyTamago01(const char* prm_name);

    /**
     * たまごモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * たまごの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * たまごのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * たまごの振る舞い .
     */
    void processBehavior() override;

    /**
     * たまごの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * たまごの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 発射弾設定 .
     * @param prm_pStore (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つストアーのポインタ
     */
    void setStore_Shot(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_Shot = prm_pStore;
    }

    /**
     * 効果エフェクト設定 .
     * @param prm_pStore (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つストアーのポインタ
     */
    void setStore_ShotEffect(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_ShotEffect = prm_pStore;
    }

    virtual ~EnemyTamago01();
};

}
#endif /*ENEMYTAMAGO01_H_*/

