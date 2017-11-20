#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"

#include "jp/ggaf/dxcore/scene/GgafDxScene.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAlphaCurtain::GgafDxAlphaCurtain(GgafDxScene* prm_pDxScene) : GgafDxSceneCurtain(prm_pDxScene, 1.0f, 0.0f, 1.0f) {
}

void GgafDxAlphaCurtain::behave() {
    GgafDxSceneCurtain::behave(); //_curtain_positionXV
    GgafDxScene* pDxScene = getScene();
    pDxScene->setSceneAlpha(1.0f - getCurtainPosition());
    pDxScene->setSceneAlphaFromTop(1.0f - getCurtainPositionFromTopScene());
}

GgafDxAlphaCurtain::~GgafDxAlphaCurtain() {
}
