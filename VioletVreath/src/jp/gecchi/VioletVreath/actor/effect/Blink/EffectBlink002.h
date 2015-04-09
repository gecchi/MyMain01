#ifndef EFFECTBLINK002_H_
#define EFFECTBLINK002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

namespace VioletVreath {

/**
 * �o��G�t�F�N�g�A����2 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectBlink002 : public EffectBlink {

public:
    EffectBlink002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    virtual ~EffectBlink002();
};

}
#endif /*EFFECTBLINK002_H_*/

