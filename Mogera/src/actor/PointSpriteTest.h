#ifndef POINTSPRITETEST_H_
#define POINTSPRITETEST_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteSetActor.h"

namespace Mogera {

/**
 */
class PointSpriteTest : public GgafLib::DefaultPointSpriteSetActor {

public:
    PointSpriteTest(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    int isOutOfView() override;

    bool isOutOfSpacetime() const override;

    virtual ~PointSpriteTest();
};

}
#endif /*POINTSPRITETEST_H_*/

