#ifndef EFFECTBLINK001_H_
#define EFFECTBLINK001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

namespace VioletVreath {

/**
 * 登場エフェクト、その1 .
 * @version 1.00
 * @since 2012/06/11
 * @author Masatoshi Tsuge
 */
class EffectBlink001 : public EffectBlink {

public:
    EffectBlink001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~EffectBlink001();
};

}
#endif /*EFFECTBLINK001_H_*/

