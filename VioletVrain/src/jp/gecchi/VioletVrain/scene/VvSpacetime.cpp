#include "VvSpacetime.h"

#include "jp/gecchi/VioletVrain/scene/VvSpacetime/World.h"
#include "jp/gecchi/VioletVrain/util/VvUtil.h"
#include "jp/gecchi/VioletVrain/VvCaretaker.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"

using namespace VioletVrain;

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

VvSpacetime::VvSpacetime(const char* prm_name, VvCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::DUAL_VIEW ? PX_C(pCARETAKER->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left) :
                                              PX_C(pCARETAKER->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = CONFIG::DUAL_VIEW ? PX_C(pCARETAKER->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top) :
                                                      PX_C(pCARETAKER->_rectRenderTargetBuffer.top);
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

void VvSpacetime::processJudgement() {
    executeWorldHitCheck(VV_MIKATA, VV_TEKI);
    //executeWorldHitCheck ‚Í processJudgement() ‚ÅŒÄ‚Ô•K—v‚ ‚è
    //(processBehavior())‚Å‚Í‚Ü‚¾“o˜^‚³‚ê‚Ä‚¢‚È‚¢)
    if (GgafDx::Input::isPushedDownKey(DIK_I)) {
        _TRACE_("----------------------------------");
        VvSpacetime::_pWorldQuadtree->putTree();
        _TRACE_("----------------------------------");
    }
}

VvSpacetime::~VvSpacetime() {
}

