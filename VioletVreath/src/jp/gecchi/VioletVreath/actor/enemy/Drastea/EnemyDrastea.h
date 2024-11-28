#ifndef ENEMYDRASTEA_H_
#define ENEMYDRASTEA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機ドラステア .
 * 横回転も自由にできるバキュラ～・・・
 * @version 1.00
 * @since 2012/08/06
 * @author Masatoshi Tsuge
 */
class EnemyDrastea : public VvEnemyActor<GgafLib::CubeMapMeshSetActor> {

public:
    EnemyDrastea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~EnemyDrastea();
};

}
#endif /*ENEMYDRASTEA_H_*/

