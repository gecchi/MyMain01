#ifndef ENEMYEUNOMIA_H_
#define ENEMYEUNOMIA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エウノミア .
 * n * m の編隊。
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyEunomia : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_ENTRY      ,
        PROG_SPLINE_MOVE,
        PROG_MOVE01_1   ,
        PROG_MOVE01_2   ,
        PROG_LEAVE      ,
    };

    enum {
        SE_EXPLOSION ,
    };

    /** 移動スプラインのシークエンスプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

    /** 行動パターン番号 */
    int iMovePatternNo_;
public:
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
     * @param prm_pKurokoLeader
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            );


    virtual ~EnemyEunomia();
};

}
#endif /*ENEMYEUNOMIA_H_*/

