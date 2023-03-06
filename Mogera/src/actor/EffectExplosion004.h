#ifndef EFFECTEXPLOSION004_H_
#define EFFECTEXPLOSION004_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace Mogera {

/**
 * 爆発エフェクトスプライト004
 * トーラス用爆発大
 * @version 1.00
 * @since 2012/10/19
 * @author Masatoshi Tsuge
 */
class EffectExplosion004 : public GgafLib::DefaultSpriteActor {
//	class EffectExplosion004 : public GgafLib::DefaultMassSpriteActor {
public:
    EffectExplosion004(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~EffectExplosion004();
};

}
#endif /*EFFECTEXPLOSION004_H_*/

