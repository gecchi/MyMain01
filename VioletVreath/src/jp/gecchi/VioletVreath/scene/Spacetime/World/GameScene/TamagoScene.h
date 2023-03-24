#ifndef TAMAGOSCENE_H_
#define TAMAGOSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

class TamagoScene : public VvScene<GgafLib::DefaultScene> {

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
