#ifndef ENEMYOZARTIASHOT01_H_
#define ENEMYOZARTIASHOT01_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 3D“G’e001 .
 */
class EnemyOzartiaShot01 : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_LEAVE  ,
        PROG_BANPEI,
    };
public:
    EnemyOzartiaShot01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyOzartiaShot01();
};

}
#endif /*ENEMYOZARTIASHOT01_H_*/

