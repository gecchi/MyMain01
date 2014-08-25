#ifndef ENEMYDELHEID_H_
#define ENEMYDELHEID_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機デルヘイド .
 * 超連射68Kの３面の連なった編隊の敵の改！
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyDelheid : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT,
        PROG_SPLINE_MOVING,
        PROG_AFTER_LEAD,
        PROG_AFTER_LEAD_MOVING,
        PROG_BANPEI,
    };
    enum {
        PROG2_WAIT,
        PROG2_OPEN,
        PROG2_SHOT,
        PROG2_CLOSE,
        PROG2_BANPEI,
    };
    enum {
        MPH_CLOSE,
        MPH_OPEN,
    };
    enum {
        SE_DAMAGED  ,
        SE_UNDAMAGED,
        SE_EXPLOSION,
    };

    /** スプライン移動のシークエンス */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
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

    void config(GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
                GgafCore::GgafActorDepository* prm_pDepoShot);

    /**
     * デルヘイドの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * デルヘイドのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * デルヘイドの振る舞い .
     */
    void processBehavior() override;

    /**
     * デルヘイドの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * デルヘイドの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ショットを撃つ .
     */
    void open_shot();



    virtual ~EnemyDelheid();
};

}
#endif /*ENEMYDELHEID_H_*/

