#include "MgrSpacetime.h"

#include <actor/camera/MgrMouseCamWorker.h>
#include "jp/ggaf/core/GgafFactory.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "util/MgrUtil.h"
#include "MgrGod.h"
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/scene/GgafScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
using namespace Mogera;

MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = PROPERTY::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[0].left) :
                                              PX_C(P_GOD->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = PROPERTY::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[0].top) :
                                                      PX_C(P_GOD->_rectRenderTargetBuffer.top);
    UTIL::center_x_ = PX_C(PROPERTY::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(PROPERTY::RENDER_TARGET_BUFFER_HEIGHT / 2);

    pActiveCamWorker_ = NEW MgrMouseCamWorker("MgrMouseCamWorker");
    bringDirector()->addSubGroup(pActiveCamWorker_); //基底デフォルトカメラワーク

    _TRACE_("再設定 Gone=X ("<<_x_gone_left<<" ~ "<<_x_gone_right<<") Y("<<_y_gone_bottom<<" ~ "<<_y_gone_top<<") Z("<<_z_gone_near<<" ~ "<<_z_gone_far<<")");
}

void MgrSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = createInFactory(Mogera::MgrWorld, "MOGERA_WORLD");
    addSubLast(pWorld_);
}

void MgrSpacetime::processBehavior() {
}

MgrSpacetime::~MgrSpacetime() {
}

