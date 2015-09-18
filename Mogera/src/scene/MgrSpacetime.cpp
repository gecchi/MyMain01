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

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = PROPERTY::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left) :
                                              PX_C(P_GOD->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = PROPERTY::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top) :
                                                      PX_C(P_GOD->_rectRenderTargetBuffer.top);
    UTIL::center_x_ = PX_C(PROPERTY::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(PROPERTY::RENDER_TARGET_BUFFER_HEIGHT / 2);

    pActiveCamWorker_ = NEW MgrMouseCamWorker("MgrMouseCamWorker");
    bringDirector()->addSubGroup(pActiveCamWorker_); //基底デフォルトカメラワーク

    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}

void MgrSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = createInFactory(Mogera::MgrWorld, "MOGERA_WORLD");
    addSubLast(pWorld_);


//    angle rz,ry;
//    UTIL::convVectorToRzRy(1.0,1.0,0.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,-1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,-1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,-1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,-1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");

}

void MgrSpacetime::processBehavior() {
}

MgrSpacetime::~MgrSpacetime() {
}

