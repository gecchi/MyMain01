#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultUniverse::DefaultUniverse(const char* prm_name, DefaultCamera* prm_pCamera) : GgafDxUniverse(prm_name, prm_pCamera) {
    _class_name = "DefaultUniverse";
    //８分木作成
    _TRACE_("８分木作成開始");
    _pLinearOctree = NEW LinearOctreeForActor(PROPERTY::OCTREE_LEVEL);
    _pLinearOctree->setRootSpace(_x_gone_left  ,_y_gone_bottom, _z_gone_near ,
                                 _x_gone_right ,_y_gone_top   , _z_gone_far   );
    _TRACE_("８分木作成終了");
}

void DefaultUniverse::processFinal() {
    _pLinearOctree->clearElem();
    //ルート空間更新
//    _pLinearOctree->setRootSpace(_x_gone_left  ,_y_gone_bottom, _z_gone_near ,
//                                     _x_gone_right ,_y_gone_top   , _z_gone_far   );
}

DefaultUniverse::~DefaultUniverse() {
#ifdef MY_DEBUG
    _pLinearOctree->putTree();
    ColliAABActor::release();
    ColliAAPrismActor::release();
    ColliSphereActor::release();
#endif
    GGAF_DELETE(_pLinearOctree);
}
