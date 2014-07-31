#ifndef ENEMYGERIA_H_
#define ENEMYGERIA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

//ゲリア
class EnemyGeria : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION,
        SE_FIRE     ,
    };
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    int iMovePatternNo_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_shotEffect_;
    bool do_Shot_;
    bool can_Shot_;
    frame frame_when_shot_;
    int max_shots_;
    int shot_num_;
    velo velo_mv_begin_;

public:
    EnemyGeria(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyGeria();

    static void callbackDispatched(GgafDxCore::GgafDxDrawableActor* prm_pDispatched,
                                   int prm_dispatched_seq,
                                   int prm_set_seq);
};

}
#endif /*ENEMYGERIA_H_*/

