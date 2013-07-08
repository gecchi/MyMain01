#ifndef ENEMYRIS_H_
#define ENEMYRIS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機リス .
 * フローラを弾として出す。
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyRis : public GgafLib::DefaultMeshSetActor {

//    /** フォーメーション(非フォーメーション時はnullptr) */
//    GgafLib::TreeFormation* pFormation_;
    /** 移動スプラインプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:
    enum {
        SE_EXPLOSION,
    };

    /** 行動パターン番号 */
    int iMovePatternNo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyRis(const char* prm_name);

    void onCreateModel() override;

    /**
     * リスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * リスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * リスの振る舞い .
     */
    void processBehavior() override;

    /**
     * リスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * リスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        pKurokoLeader_ = prm_pKurokoLeader;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }

    virtual ~EnemyRis();
};

}
#endif /*ENEMYRIS_H_*/

