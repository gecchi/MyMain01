#include "VvSpacetime.h"

#include "jp/gecchi/VioletVrain/scene/VvSpacetime/World.h"
#include "jp/gecchi/VioletVrain/util/VvUtil.h"
#include "jp/gecchi/VioletVrain/VvCaretaker.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"

using namespace VioletVrain;

VvSpacetime::VvSpacetime(const char* prm_name, VvCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::NUMBER_OF_SCREENS_USED > 1 ? PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].left) :
                                              PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].left);
    UTIL::left_top_y_ = CONFIG::NUMBER_OF_SCREENS_USED > 1 ? PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].top) :
                                                      PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].top);
    UTIL::center_x_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2);


    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}

void VvSpacetime::initialize() {
    pWorld_ = desireScene(VioletVrain::World);
    appendChild(pWorld_);
}

void VvSpacetime::processBehavior() {
}

void VvSpacetime::processHitCheck() {
    executeWorldHitCheck(VV_MIKATA, VV_TEKI);
    if (GgafDx::Input::isPushedDownKey(DIK_I)) {
        _TRACE_("----------------------------------");
        VvSpacetime::_pWorldQuadtree->putTree();
        _TRACE_("----------------------------------");
    }
}

VvSpacetime::~VvSpacetime() {
}

