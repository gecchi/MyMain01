#ifndef EFFECTBLINK003_H_
#define EFFECTBLINK003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

namespace VioletVreath {

/**
 * 登場エフェクト、その3 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectBlink003 : public EffectBlink {

public:
    EffectBlink003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    virtual ~EffectBlink003();
};

}
#endif /*EFFECTBLINK003_H_*/

