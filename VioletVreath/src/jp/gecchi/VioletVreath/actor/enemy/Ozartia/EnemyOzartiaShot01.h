#ifndef ENEMYOZARTIASHOT01_H_
#define ENEMYOZARTIASHOT01_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 3D敵弾001 .
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

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

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

