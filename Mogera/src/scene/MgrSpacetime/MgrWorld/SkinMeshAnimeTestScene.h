#ifndef SKINMESHANIMETESTSCENE_H_
#define SKINMESHANIMETESTSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

class SkinMeshAnimeTestScene : public GgafLib::DefaultScene {

public:
    PointSpriteTest* pTest_;

public:
    SkinMeshAnimeTestScene(const char* prm_name);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~SkinMeshAnimeTestScene();
};

}
#endif /*PREDRAWSCENE_H_*/
