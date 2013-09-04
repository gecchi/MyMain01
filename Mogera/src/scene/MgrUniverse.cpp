#include "stdafx.h"
#include "MgrUniverse.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "util/MgrUtil.h"
#include "MgrGod.h"
#include "GgafDxCommonHeader.h"

using namespace Mogera;

MgrUniverse::MgrUniverse(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    coord F = PX_C((PROPERTY::RENDER_TARGET_BUFFER_WIDTH / 2) * 3);
    _X_gone_left    = -F;
    _X_gone_right   = +F;
    _Y_gone_bottom  = -F;
    _Y_gone_top     = +F;
    _Z_gone_near    = -F/3;
    _Z_gone_far     = +F;
    _pLinearOctree->setRootSpace(_X_gone_left  ,_Y_gone_bottom, _Z_gone_near ,
                                 _X_gone_right ,_Y_gone_top   , _Z_gone_far   );
    UTIL::left_top_X_ = PROPERTY::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[0].left) :
                                              PX_C(P_GOD->_rectRenderTargetBuffer.left);
    UTIL::left_top_Y_ = PROPERTY::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[0].top) :
                                                      PX_C(P_GOD->_rectRenderTargetBuffer.top);
    UTIL::center_X_ = PX_C(PROPERTY::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_Y_ = PX_C(PROPERTY::RENDER_TARGET_BUFFER_HEIGHT / 2);


    _TRACE_("再設定 Gone=X ("<<_X_gone_left<<" ~ "<<_X_gone_right<<") Y("<<_Y_gone_bottom<<" ~ "<<_Y_gone_top<<") Z("<<_Z_gone_near<<" ~ "<<_Z_gone_far<<")");
}

void MgrUniverse::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = createInFactory(Mogera::MgrWorld, "MOGERA_WORLD");
    addSubLast(pWorld_);
}

void MgrUniverse::processBehavior() {
}

MgrUniverse::~MgrUniverse() {
}

