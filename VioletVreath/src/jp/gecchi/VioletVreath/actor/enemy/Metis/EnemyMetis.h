#ifndef ENEMYMETIS_H_
#define ENEMYMETIS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機メティス .
 * バキュラ～・・・
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class EnemyMetis : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_DAMAGED   ,
        SE_EXPLOSION ,
    };
    DepositoryConnection* pConn_ShotDepo_;
    GgafCore::GgafActorDepository* pDepo_Shot_;
    int width_X_;
    int height_Z_;
    int depth_Y_;

public:
    EnemyMetis(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyMetis();
};

}
#endif /*ENEMYMETIS_H_*/

