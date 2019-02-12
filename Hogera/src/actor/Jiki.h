#ifndef JIKI_H_
#define JIKI_H_
#include "Hogera.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace Hogera {

/**
 * �e�X�g
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

    void onHit(const GgafCore::Actor* prm_pOtherActor);

    virtual ~Jiki();


};

}
#endif /*TEST01_H_*/

