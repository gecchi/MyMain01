#ifndef ENEMYEBE_H_
#define ENEMYEBE_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エーベ .
 * フェルマー螺旋。
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class EnemyEbe : public GgafLib::DefaultMeshSetActor {

public:

    enum {
        PROG_MOVE01_1   ,
        PROG_SPLINE_MOVE,
        PROG_MOVE02_1   ,
        PROG_MOVE02_2   ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** 移動スプラインのシークエンスプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyEbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * エーベの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エーベのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エーベの振る舞い .
     */
    void processBehavior() override;

    /**
     * エーベの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エーベの衝突時処理 .
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


    virtual ~EnemyEbe();
};

}
#endif /*ENEMYEBE_H_*/

