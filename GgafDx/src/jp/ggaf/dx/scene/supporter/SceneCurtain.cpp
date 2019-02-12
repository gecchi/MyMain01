#include "jp/ggaf/dx/scene/supporter/SceneCurtain.h"

#include "jp/ggaf/dx/scene/Scene.h"


using namespace GgafDx;

SceneCurtain::SceneCurtain(Scene* prm_pScene,
                                       float prm_curtain_rail_length,
                                       float prm_min_position,
                                       float prm_max_position) : GgafCore::Curtain<float>(prm_curtain_rail_length,
                                                                                              prm_min_position,
                                                                                              prm_max_position) {
    _pDxScene = prm_pScene;
}

float SceneCurtain::getCurtainPositionFromTopScene() {
    float curtain_position_from_spacetime = _curtain_position;
    GgafCore::Scene* pParent = _pDxScene->getParent();
    while (pParent && pParent->instanceOf(Obj_GgafDx_Scene)) {
        SceneCurtain* pParentSceneCurtain = ((Scene*)pParent)->getSceneCurtain();
        curtain_position_from_spacetime += ((1.0 - curtain_position_from_spacetime) * pParentSceneCurtain->getClosingRatio());
        pParent = pParent->getParent();
    }
    return curtain_position_from_spacetime;
}

void SceneCurtain::behave() {
    GgafCore::Curtain<float>::behave();
}

SceneCurtain::~SceneCurtain() {
}
