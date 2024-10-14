#ifndef ENEMYOZARTIAPILLAR01_H_
#define ENEMYOZARTIAPILLAR01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * オーツァルティアの氷柱（地形続性） .
 * @version 1.00
 * @since 2013/10/16
 * @author Masatoshi Tsuge
 */
class EnemyOzartiaPillar01 : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    EnemyOzartiaPillar01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyOzartiaPillar01();
};

}
#endif /*ENEMYOZARTIAPILLAR01_H_*/

