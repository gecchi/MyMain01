#include "jp/ggaf/dxcore/scene/supporter/GgafDxSceneCurtain.h"

#include "jp/ggaf/dxcore/scene/GgafDxScene.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSceneCurtain::GgafDxSceneCurtain(GgafDxScene* prm_pScene,
                                       float prm_curtain_rail_length,
                                       float prm_min_position,
                                       float prm_max_position) : GgafCore::GgafCurtain<float>(prm_curtain_rail_length,
                                                                                              prm_min_position,
                                                                                              prm_max_position) {
    _pDxScene = prm_pScene;
}

float GgafDxSceneCurtain::getCurtainPositionFromTopScene() {
    float curtain_position_from_spacetime = _curtain_position;
    GgafScene* pParent = _pDxScene->getParent();
    while (pParent && pParent->instanceOf(Obj_GgafDxScene)) {
        GgafDxSceneCurtain* pParentSceneCurtain = ((GgafDxScene*)pParent)->getSceneCurtain();
        curtain_position_from_spacetime += ((1.0 - curtain_position_from_spacetime) * pParentSceneCurtain->getClosingRatio());
        pParent = pParent->getParent();
    }
    return curtain_position_from_spacetime;
}

void GgafDxSceneCurtain::behave() {
    GgafCurtain::behave();
}

GgafDxSceneCurtain::~GgafDxSceneCurtain() {
}
