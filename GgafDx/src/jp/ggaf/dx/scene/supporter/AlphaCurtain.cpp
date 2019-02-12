#include "jp/ggaf/dx/scene/supporter/AlphaCurtain.h"

#include "jp/ggaf/dx/scene/Scene.h"


using namespace GgafDx;

AlphaCurtain::AlphaCurtain(Scene* prm_pDxScene) : SceneCurtain(prm_pDxScene, 1.0f, 0.0f, 1.0f) {
}

void AlphaCurtain::behave() {
    SceneCurtain::behave(); //_curtain_positionXV
    Scene* pDxScene = getScene();
    pDxScene->setSceneAlpha(1.0f - getCurtainPosition());
    pDxScene->setSceneAlphaFromTop(1.0f - getCurtainPositionFromTopScene());
}

AlphaCurtain::~AlphaCurtain() {
}
