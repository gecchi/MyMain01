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
    /** フォーメーション(非フォーメーション時はNULL) */
    GgafDx9LibStg::FormationActor* _pFormation;
    /** 移動スプラインプログラム */
    GgafDx9LibStg::SplineSequence* _pSplSeq;
    /** 弾ストック */
    GgafCore::GgafActorDepository* _pDepo_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* _pDepo_ShotEffect;
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


    virtual void config(
            GgafDx9LibStg::FormationActor* prm_pFormation,
            GgafDx9LibStg::SplineSequence* prm_pSplSeq,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        _pFormation = prm_pFormation;
        _pSplSeq = prm_pSplSeq;
        _pDepo_Shot = prm_pDepo_Shot;
        _pDepo_ShotEffect = prm_pDepo_ShotEffect;
    }

//    /**
//     * 発射弾Depository設定 .
//     * initialize() までに設定して下さい。
//     * @param prm_pDepo
//     */
//    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
//        _pDepo_Shot = prm_pDepo;
//    }
//
//    /**
//     * スプライン移動設定 .
//     * initialize() までに設定して下さい。
//     * @param prm_pSplSeq
//     */
//    void setSplineSequence(GgafDx9LibStg::SplineSequence* prm_pSplSeq) {
//        _pSplSeq = prm_pSplSeq;
//    }
//
//    /**
//     * ショット発射効果エフェクト設定 .
//     * @param prm_pDepo
//     */
//    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
//        _pDepo_ShotEffect = prm_pDepo;
//    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

