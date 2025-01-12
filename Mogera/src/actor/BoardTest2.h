#ifndef BOARDTEST2_H_
#define BOARDTEST2_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultRegularPolygonBoardActor.h"

namespace Mogera {

class BoardTest2 : public GgafLib::DefaultRegularPolygonBoardActor {

public:
    BoardTest2(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    void onInactive() override;

    virtual ~BoardTest2();
};

}
#endif /*BOARDTEST2_H_*/

