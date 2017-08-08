#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearQuadtree.h"
#include "jp/ggaf/core/util/GgafLinearOctreeForActor.h"
#include "jp/ggaf/core/util/GgafLinearQuadtreeForActor.h"
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
    if (PROPERTY::IS_HIT_CHECK_3D) {
        //八分木作成
        _TRACE_("八分木作成開始");
        _pLinearOctree = NEW GgafLinearOctree(PROPERTY::OCTREE_LEVEL);
        _pLinearOctree->setRootOctant(_x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                      _x_bound_right ,_y_bound_top   , _z_bound_far   );
        void (GgafActor::*pFunc)(GgafActor*) = &GgafActor::executeHitChk_MeAnd;
        _pLinearOctreeForActor = NEW GgafLinearOctreeForActor(_pLinearOctree, pFunc);
        _pLinearQuadtree = nullptr;
        _TRACE_("八分木作成終了");
    } else {
        //四分木作成
        _TRACE_("四分木作成開始");
        _pLinearQuadtree = NEW GgafLinearQuadtree(PROPERTY::OCTREE_LEVEL);
        _pLinearQuadtree->setRootQuadrant(_x_bound_left  ,_y_bound_bottom,
                                          _x_bound_right ,_y_bound_top    );
        void (GgafActor::*pFunc)(GgafActor*) = &GgafActor::executeHitChk_MeAnd;
        _pLinearQuadtreeForActor = NEW GgafLinearQuadtreeForActor(_pLinearQuadtree, pFunc);
        _pLinearOctree = nullptr;
        _TRACE_("四分木作成終了");
    }
}

void DefaultSpacetime::processFinal() {
    if (PROPERTY::IS_HIT_CHECK_3D) {
        _pLinearOctree->clearAllElem();
    } else {
        _pLinearQuadtree->clearAllElem();
    }
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    if (PROPERTY::IS_HIT_CHECK_3D) {
        _pLinearOctree->putTree();
    } else {
        _pLinearQuadtree->putTree();
    }
    ColliAABoxActor::release();
    ColliAAPrismActor::release();
    ColliAAPyramidActor::release();
    ColliSphereActor::release();
#endif
    if (PROPERTY::IS_HIT_CHECK_3D) {
        GGAF_DELETE(_pLinearOctree);
    } else {
        GGAF_DELETE(_pLinearQuadtree);
    }
}
