#ifndef ENEMYOZARTIASHOT01_H_
#define ENEMYOZARTIASHOT01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 3D“G’e001 .
 */
class EnemyOzartiaShot01 : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    EnemyOzartiaShot01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyOzartiaShot01();
};

}
#endif /*ENEMYOZARTIASHOT01_H_*/

