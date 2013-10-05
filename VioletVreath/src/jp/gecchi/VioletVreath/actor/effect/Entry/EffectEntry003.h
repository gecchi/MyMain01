#ifndef EFFECTENTRANCE003_H_
#define EFFECTENTRANCE003_H_
#include "jp/gecchi/VioletVreath/actor/effect/Entry/EffectEntry.h"

namespace VioletVreath {

/**
 * 登場エフェクト、その3 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectEntry003 : public EffectEntry {

    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
        _BANPEI_,
    };

public:
    EffectEntry003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    virtual ~EffectEntry003();
};

}
#endif /*EFFECTENTRANCE003_H_*/

