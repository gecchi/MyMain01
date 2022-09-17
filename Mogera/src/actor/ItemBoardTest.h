#ifndef ITEMBOARDTEST_H_
#define ITEMBOARDTEST_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace Mogera {

class ItemBoardTest : public GgafLib::DefaultBoardActor {

public:
    ItemBoardTest(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~ItemBoardTest();
};

}
#endif /*ITEMBOARDTEST_H_*/

