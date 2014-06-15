#ifndef EFFECTENTRANCE001_H_
#define EFFECTENTRANCE001_H_
#include "jp/gecchi/VioletVreath/actor/effect/Entry/EffectEntry.h"

namespace VioletVreath {

/**
 * 登場エフェクト、その1 .
 * @version 1.00
 * @since 2012/06/11
 * @author Masatoshi Tsuge
 */
class EffectEntry001 : public EffectEntry {

public:
    EffectEntry001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~EffectEntry001();
};

}
#endif /*EFFECTENTRANCE001_H_*/

