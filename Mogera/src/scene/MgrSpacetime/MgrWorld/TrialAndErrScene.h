#ifndef TRIALANDERRSCENE_H_
#define TRIALANDERRSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

class TrialAndErrScene : public GgafLib::DefaultScene {

public:

public:
    TrialAndErrScene(const char* prm_name);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~TrialAndErrScene();
};

}
#endif /*TRIALANDERRSCENE_H_*/
