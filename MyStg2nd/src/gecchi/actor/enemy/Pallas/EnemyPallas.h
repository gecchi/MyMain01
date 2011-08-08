#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace MyStg2nd {

/**
 * 敵機パラス .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyPallas : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** 移動スプラインプログラム */
    GgafDx9LibStg::SplineProgram* _pSplProgram;
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
    EnemyPallas(const char* prm_name);

    void onCreateModel() override;

    /**
     * パラスのが初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * パラスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * パラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * パラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * パラスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pSplProgram
     * @param prm_pStore_Shot
     * @param prm_pStore_ShotEffect
     */
    virtual void config(
            GgafDx9LibStg::SplineProgram* prm_pSplProgram,
            GgafCore::GgafActorStore* prm_pStore_Shot,
            GgafCore::GgafActorStore* prm_pStore_ShotEffect
            ) {
        _pSplProgram = prm_pSplProgram;
        _pStore_Shot = prm_pStore_Shot;
        _pStore_ShotEffect = prm_pStore_ShotEffect;
    }


    virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

