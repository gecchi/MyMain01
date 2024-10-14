#ifndef BOARDTEST_H_
#define BOARDTEST_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"

namespace Mogera {

class BoardTest : public GgafLib::DefaultFramedBoardActor {

public:
    BoardTest(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~BoardTest();
};

}
#endif /*BOARDTEST_H_*/

