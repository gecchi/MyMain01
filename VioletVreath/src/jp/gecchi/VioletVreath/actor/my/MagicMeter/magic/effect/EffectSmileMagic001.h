#ifndef EFFECTSMILEMAGIC001_H_
#define EFFECTSMILEMAGIC001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * スピードアップのエフェクト .
 * @version 1.00
 * @since 2012/05/15
 * @author Masatoshi Tsuge
 */
class EffectSmileMagic001 : public GgafLib::DefaultSpriteActor {

public:
    EffectSmileMagic001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectSmileMagic001();
};

}
#endif /*EFFECTSMILEMAGIC001_H_*/

