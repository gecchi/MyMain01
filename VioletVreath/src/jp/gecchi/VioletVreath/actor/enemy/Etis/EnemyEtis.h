#ifndef ENEMYETIS_H_
#define ENEMYETIS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 敵機エティス .
 * バキュラ～・・・
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class EnemyEtis : public GgafLib::DefaultMassMeshActor {

public:
    int width_x_;
    int height_z_;
    int depth_y_;

public:
    EnemyEtis(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyEtis();
};

}
#endif /*ENEMYETIS_H_*/

