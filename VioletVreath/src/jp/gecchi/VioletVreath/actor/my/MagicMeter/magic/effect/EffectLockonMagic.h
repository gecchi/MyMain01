#ifndef LOCKONCURSORMAGIC_H_
#define LOCKONCURSORMAGIC_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * ロックオン魔法装備時のエフェクト .
 * @version 1.00
 * @since 2012/07/30
 * @author Masatoshi Tsuge
 */
class EffectLockonMagic : public GgafLib::DefaultSpriteActor {

public:
    EffectLockonMagic(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectLockonMagic();
};

}
#endif /*LOCKONCURSORMAGIC_H_*/

