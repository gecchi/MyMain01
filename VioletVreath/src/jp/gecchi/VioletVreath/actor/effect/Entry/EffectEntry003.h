#ifndef EFFECTENTRANCE003_H_
#define EFFECTENTRANCE003_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/effect/Entry/EffectEntry.h"

namespace VioletVreath {

/**
 * �o��G�t�F�N�g�A����3 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectEntry003 : public EffectEntry {

public:
    EffectEntry003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    virtual ~EffectEntry003();
};

}
#endif /*EFFECTENTRANCE003_H_*/

