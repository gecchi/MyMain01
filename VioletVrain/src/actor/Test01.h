#ifndef TEST01_H_
#define TEST01_H_
#include "VioletVrain.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVrain {

/**
 * �e�X�g
 * @author Masatoshi Tsuge
 */
class Test01 : public GgafLib::DefaultSpriteActor {

public:
    Test01(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onReset() override;

    void onInactive() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor);

    virtual ~Test01();


};

}
#endif /*TEST01_H_*/

