#ifndef PARALLELCURVETESTSCENE_H_
#define PARALLELCURVETESTSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

class ParallelCurveTestScene : public GgafLib::DefaultScene {

public:
    PointSpriteTest* pTest_;

public:
    ParallelCurveTestScene(const char* prm_name);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~ParallelCurveTestScene();
};

}
#endif /*PARALLELCURVETESTSCENE_H_*/
