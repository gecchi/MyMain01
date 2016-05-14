#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

class TrialAndErrScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT ,
        PROG_CALM ,
        PROG_WAIT ,
        PROG_BANPEI,
    };
    PointSpriteTest* pTest_;

public:
    TrialAndErrScene(const char* prm_name);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~TrialAndErrScene();
};

}
#endif /*PREDRAWSCENE_H_*/
