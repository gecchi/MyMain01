#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) : GgafDxSpacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
    //八分木作成
    _TRACE_("八分木作成開始");
    _pLinearOctree = NEW LinearOctreeForActor(PROPERTY::OCTREE_LEVEL);
    _pLinearOctree->setRootOctant(_x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                  _x_bound_right ,_y_bound_top   , _z_bound_far   );
    _TRACE_("八分木作成終了");
}

void DefaultSpacetime::processFinal() {
    _pLinearOctree->clearElem();
    //ルート空間更新
//    _pLinearOctree->setRootOctant(_x_bound_left  ,_y_bound_bottom, _z_bound_near ,
//                                     _x_bound_right ,_y_bound_top   , _z_bound_far   );
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    _pLinearOctree->putTree();
    ColliAABoxActor::release();
    ColliAAPrismActor::release();
    ColliAAPyramidActor::release();
    ColliSphereActor::release();
#endif
    GGAF_DELETE(_pLinearOctree);
}
