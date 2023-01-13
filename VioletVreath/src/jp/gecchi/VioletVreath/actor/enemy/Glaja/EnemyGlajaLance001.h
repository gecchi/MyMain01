#ifndef ENEMYGLAJALANCE001_H_
#define ENEMYGLAJALANCE001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * åıëÑíe(çÏê¨íÜÅI) .
 * @version 1.00
 * @since 2013/08/19
 * @author Masatoshi Tsuge
 */
class EnemyGlajaLance001 : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {
public:
    //GgafDx::GeoElem turning_pos_;

public:
    EnemyGlajaLance001(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~EnemyGlajaLance001();
};

}
#endif /*ENEMYGLAJALANCE001_H_*/

