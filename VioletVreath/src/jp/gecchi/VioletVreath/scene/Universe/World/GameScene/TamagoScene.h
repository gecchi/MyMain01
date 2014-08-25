#ifndef TAMAGOSCENE_H_
#define TAMAGOSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"


namespace VioletVreath {

class TamagoScene : public GgafLib::DefaultScene {

public:
    TurboMeter* pTurboMeter001_;

public:
    TamagoScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~TamagoScene();
};

}
#endif /*TAMAGOSCENE_H_*/
