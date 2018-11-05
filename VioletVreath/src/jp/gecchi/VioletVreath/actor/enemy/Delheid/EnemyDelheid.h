#ifndef ENEMYDELHEID_H_
#define ENEMYDELHEID_H_

#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機デルヘイド .
 * 超連射68Kの３面の連なった編隊の敵の改！
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyDelheid : public GgafLib::DefaultMassMorphMeshActor {

public:
    /** スプライン移動のシークエンス */
    GgafLib::SplineLeader* pKurokoLeader_;
    /** ショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepoShot_;
    /** ショット開始時間 */
    frame shot_begin_frame_;
    /** ショット関連の進捗状態 */
    GgafCore::GgafProgress* pProg2_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyDelheid(const char* prm_name);

    void onCreateModel() override;

    void nextFrame() override;

    void config(GgafLib::SplineLeader* prm_pKurokoLeader,
                GgafCore::GgafActorDepository* prm_pDepoShot);

    /**
     * デルヘイドの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * デルヘイドがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * デルヘイドの振る舞い .
     */
    void processBehavior() override;
    void processSettlementBehavior() override;
    /**
     * デルヘイドの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * デルヘイドの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ショットを撃つ .
     */
    void open_shot();



    virtual ~EnemyDelheid();
};

}
#endif /*ENEMYDELHEID_H_*/

