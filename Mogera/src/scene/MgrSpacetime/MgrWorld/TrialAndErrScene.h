#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

class TrialAndErrScene : public GgafLib::DefaultScene {

public:
    PointSpriteTest* pTest_;

public:
    TrialAndErrScene(const char* prm_name);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~TrialAndErrScene();
};

}
#endif /*PREDRAWSCENE_H_*/
