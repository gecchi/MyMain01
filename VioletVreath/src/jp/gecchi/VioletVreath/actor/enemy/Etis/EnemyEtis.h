#ifndef ENEMYETIS_H_
#define ENEMYETIS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エティス .
 * バキュラ〜・・・
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class EnemyEtis : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_DAMAGED   ,
        SE_EXPLOSION ,
    };
    int width_X_;
    int height_Z_;
    int depth_Y_;

public:
    EnemyEtis(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyEtis();
};

}
#endif /*ENEMYETIS_H_*/

