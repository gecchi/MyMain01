#include "HgrSpacetime.h"

#include "scene/HgrSpacetime/HgrWorld.h"
#include "jp/ggaf/lib/GgafLibConfig.h"
#include "util/HgrUtil.h"
#include "HgrGod.h"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
using namespace Hogera;

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

HgrSpacetime::HgrSpacetime(const char* prm_name, HgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left) :
                                              PX_C(P_GOD->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = CONFIG::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top) :
                                                      PX_C(P_GOD->_rectRenderTargetBuffer.top);
    UTIL::center_x_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2);


    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}

void HgrSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = keepWishing(Hogera::HgrWorld, "HOGERA_WORLD");
    addSubLast(pWorld_);
}

void HgrSpacetime::processBehavior() {
}

HgrSpacetime::~HgrSpacetime() {
}

