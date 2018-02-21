#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearQuadtree.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) :
        GgafDxSpacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
    _pLinearOctree = nullptr;
    _pLinearQuadtree = nullptr;
    _pLinearOctreeHitCheckRounder = nullptr;
    _pLinearQuadtreeHitCheckRounder = nullptr;

    if (CONFIG::IS_HIT_CHECK_3D) {
        //八分木作成
        _TRACE_("八分木作成開始");
        _pLinearOctree = NEW GgafLinearOctree(CONFIG::OCTREE_LEVEL,
                                              _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                              _x_bound_right ,_y_bound_top   , _z_bound_far   );
        _pLinearOctreeHitCheckRounder = NEW OctreeRounder(_pLinearOctree->_paOctant, _pLinearOctree->_num_space, &GgafActor::executeHitChk_MeAnd);
        _TRACE_("八分木作成終了");
    } else {
        //四分木作成
        _TRACE_("四分木作成開始");
        _pLinearQuadtree = NEW GgafLinearQuadtree(CONFIG::QUADTREE_LEVEL,
                                                  _x_bound_left  ,_y_bound_bottom,
                                                  _x_bound_right ,_y_bound_top    );
        _pLinearQuadtreeHitCheckRounder = NEW QuadtreeRounder(_pLinearQuadtree->_paQuadrant,_pLinearQuadtree->_num_space, &GgafActor::executeHitChk_MeAnd);
        _TRACE_("四分木作成終了");
    }
}

void DefaultSpacetime::processFinal() {
    if (CONFIG::IS_HIT_CHECK_3D) {
        _pLinearOctree->clearAllElem();
    } else {
        _pLinearQuadtree->clearAllElem();
    }
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    if (CONFIG::IS_HIT_CHECK_3D) {
        _pLinearOctree->putTree();
    } else {
        _pLinearQuadtree->putTree();
    }
    ColliAABoxActor::release();
    ColliAAPrismActor::release();
    ColliAAPyramidActor::release();
    ColliSphereActor::release();
#endif
    if (CONFIG::IS_HIT_CHECK_3D) {
        GGAF_DELETE(_pLinearOctree);
        GGAF_DELETE(_pLinearOctreeHitCheckRounder);
    } else {
        GGAF_DELETE(_pLinearQuadtree);
        GGAF_DELETE(_pLinearQuadtreeHitCheckRounder);
    }
}
