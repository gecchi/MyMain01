#include "HgrSpacetime.h"

#include "scene/HgrSpacetime/HgrWorld.h"
//#include "jp/ggaf/lib/LibConfig.h"
#include "util/HgrUtil.h"
#include "HgrCaretaker.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/SceneChief.h"
using namespace Hogera;


HgrSpacetime::HgrSpacetime(const char* prm_name, HgrCamera* prm_pCam) :
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

void HgrSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = desireScene(Hogera::HgrWorld);
    appendChild(pWorld_);
}

void HgrSpacetime::processBehavior() {
}

void HgrSpacetime::processJudgement() {
}

void HgrSpacetime::processHitCheck() {
    executeWorldHitCheck(HGR_MIKATA, HGR_TEKI);
}


HgrSpacetime::~HgrSpacetime() {
}

