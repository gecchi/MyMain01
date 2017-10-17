#ifndef EFFECTMYSHIPEXPLOSION_H_
#define EFFECTMYSHIPEXPLOSION_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

namespace VioletVreath {

/**
 * ���@����
 * @version 1.00
 * @since 2010/11/10
 * @author Masatoshi Tsuge
 */
class EffectMyShipExplosion : public GgafLib::DefaultSpriteSetActor {

public:
    EffectMyShipExplosion(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void processJudgement() override;

    virtual ~EffectMyShipExplosion();
};

}
#endif /*EFFECTMYSHIPEXPLOSION_H_*/

