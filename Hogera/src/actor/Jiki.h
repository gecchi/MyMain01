#ifndef JIKI_H_
#define JIKI_H_
#include "Hogera.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace Hogera {

/**
 * ƒeƒXƒg
 * @author Masatoshi Tsuge
 */
class Jiki : public GgafLib::DefaultSpriteActor {

public:
    Jiki(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onReset() override;

    void onInactive() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker);

    virtual ~Jiki();


};

}
#endif /*TEST01_H_*/

