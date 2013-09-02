#include "stdafx.h"
#include "MgrUniverse.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/GgafLibProperties.h"

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

    _TRACE_("再設定 Gone=X ("<<_X_gone_left<<" ~ "<<_X_gone_right<<") Y("<<_Y_gone_bottom<<" ~ "<<_Y_gone_top<<") Z("<<_Z_gone_near<<" ~ "<<_Z_gone_far<<")");
}

void MgrUniverse::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = createInFactory(Mogera::MgrWorld, "MOGERA_WORLD");
    addSubLast(pWorld_);
}

MgrUniverse::~MgrUniverse() {
}

