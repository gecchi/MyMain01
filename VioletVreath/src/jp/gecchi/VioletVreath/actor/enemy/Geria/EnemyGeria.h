#ifndef ENEMYGERIA_H_
#define ENEMYGERIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

//ÉQÉäÉA
class EnemyGeria : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    int iMovePatternNo_;
    bool will_shot_;
    bool can_Shot_;
    frame frame_when_shot_;
    int max_shots_;
    int shot_num_;
    velo velo_mv_begin_;
    coord migration_length_;
    coord mvd_;

public:
    EnemyGeria(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~EnemyGeria();

    void setMigrationLength(coord prm_migration_length) {
        migration_length_ = prm_migration_length;
    }
    static void callbackDispatched(GgafDx::FigureActor* prm_pDispatched,
                                   int prm_dispatched_seq,
                                   int prm_set_seq);
};

}
#endif /*ENEMYGERIA_H_*/

