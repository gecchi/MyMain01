#ifndef ENEMYGLAJALANCE001_H_
#define ENEMYGLAJALANCE001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * åıëÑíe(çÏê¨íÜÅI) .
 * @version 1.00
 * @since 2013/08/19
 * @author Masatoshi Tsuge
 */
class EnemyGlajaLance001 : public GgafLib::DefaultMeshSetActor {
public:
    //GgafDxCore::GgafDxGeoElem turning_pos_;

public:
    EnemyGlajaLance001(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyGlajaLance001();
};

}
#endif /*ENEMYGLAJALANCE001_H_*/

