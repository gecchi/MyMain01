#ifndef ENEMYALLAS_H_
#define ENEMYALLAS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機アラス .
 * 羽の多いファン
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyAllas : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    /** 移動スプラインプログラム */
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
    EnemyAllas(const char* prm_name);

    void onCreateModel() override;

    /**
     * アラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アラスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * アラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アラスの衝突時処理 .
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
            ) {
        pKurokoLeader_ = prm_pKurokoLeader;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }


    virtual ~EnemyAllas();
};

}
#endif /*ENEMYALLAS_H_*/

