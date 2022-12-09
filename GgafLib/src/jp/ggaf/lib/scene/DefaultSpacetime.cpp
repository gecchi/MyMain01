#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/core/util/LinearOctree.h"
#include "jp/ggaf/core/util/LinearQuadtree.h"



using namespace GgafLib;

DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) :
        GgafDx::Spacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
    _pLinearOctree = nullptr;
    _pLinearQuadtree = nullptr;
    _pLinearOctreeHitCheckRounder = nullptr;
    _pLinearQuadtreeHitCheckRounder = nullptr;

    if (CONFIG::IS_HIT_CHECK_3D) {
        //八分木作成
        _TRACE_("八分木作成開始");
        _pLinearOctree = NEW GgafCore::LinearOctree(CONFIG::OCTREE_LEVEL,
                                                    _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                                    _x_bound_right ,_y_bound_top   , _z_bound_far   );
        _pLinearOctreeHitCheckRounder = NEW OctreeRounder(_pLinearOctree->_paTreeSpaceArray,
                                                          _pLinearOctree->_num_space,
                                                          &GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("八分木作成終了");
    } else {
        //四分木作成
        _TRACE_("四分木作成開始");
        _pLinearQuadtree = NEW GgafCore::LinearQuadtree(CONFIG::QUADTREE_LEVEL,
                                                        _x_bound_left  ,_y_bound_bottom,
                                                        _x_bound_right ,_y_bound_top    );
        _pLinearQuadtreeHitCheckRounder = NEW QuadtreeRounder(_pLinearQuadtree->_paTreeSpaceArray,
                                                              _pLinearQuadtree->_num_space,
                                                              &GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("四分木作成終了");
    }

    //Board用四分木作成
    _TRACE_("Board用四分木作成開始");
    _pLinearQuadtree_b = NEW GgafCore::LinearQuadtree_b(2, _x_bound_left_b  ,_y_bound_top_b,
                                                           _x_bound_right_b , _y_bound_bottom_b   );
    _pLinearQuadtreeHitCheckRounder_b = NEW QuadtreeRounder(_pLinearQuadtree_b->_paTreeSpaceArray,
                                                            _pLinearQuadtree_b->_num_space,
                                                            &GgafCore::Actor::executeHitChk_MeAnd);
    _TRACE_("Board用四分木作成終了");
}

void DefaultSpacetime::executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
    if (CONFIG::IS_HIT_CHECK_3D) {
       OctreeRounder* pHitCheckRounder = getLinearOctreeHitCheckRounder();
       pHitCheckRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    } else {
       QuadtreeRounder* pHitCheckRounder = getLinearQuadtreeHitCheckRounder();
       pHitCheckRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    }
}

void DefaultSpacetime::executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
    QuadtreeRounder_b* pHitCheckRounder_b = getLinearQuadtreeHitCheckRounder_b();
    pHitCheckRounder_b->executeAll(prm_kind_groupA, prm_kind_groupB);
}


void DefaultSpacetime::processFinal() {
    if (CONFIG::IS_HIT_CHECK_3D) {
        _pLinearOctree->clearAllElem();
    } else {
        _pLinearQuadtree->clearAllElem();
    }
    _pLinearQuadtree_b->clearAllElem();
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    if (CONFIG::IS_HIT_CHECK_3D) {
        _pLinearOctree->putTree();
    } else {
        _pLinearQuadtree->putTree();
    }
    _TRACE_("Board用四分木 -->");
    _pLinearQuadtree_b->putTree();
    _TRACE_("<--Board用四分木");
    WorldCollisionChecker::releaseHitArea();
    ViewCollisionChecker::releaseHitArea();
#endif
    if (CONFIG::IS_HIT_CHECK_3D) {
        GGAF_DELETE(_pLinearOctree);
        GGAF_DELETE(_pLinearOctreeHitCheckRounder);
    } else {
        GGAF_DELETE(_pLinearQuadtree);
        GGAF_DELETE(_pLinearQuadtreeHitCheckRounder);
    }
    GGAF_DELETE(_pLinearQuadtree_b);
    GGAF_DELETE(_pLinearQuadtreeHitCheckRounder_b);
}
