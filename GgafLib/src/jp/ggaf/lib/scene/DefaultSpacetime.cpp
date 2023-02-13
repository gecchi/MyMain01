#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"

using namespace GgafLib;


WorldOctree* DefaultSpacetime::_pWorldOctree = nullptr;
WorldOctreeRounder* DefaultSpacetime::_pWorldOctreeRounder = nullptr;
WorldQuadtree* DefaultSpacetime::_pWorldQuadtree = nullptr;
WorldQuadtreeRounder* DefaultSpacetime::_pWorldQuadtreeRounder = nullptr;
ViewQuadtree* DefaultSpacetime::_pViewQuadtree = nullptr;
ViewQuadtreeRounder* DefaultSpacetime::_pViewQuadtreeRounder = nullptr;


DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) :
        GgafDx::Spacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
#ifdef MY_DEBUG
    _is_done_processSettlementBehavior = false;
#endif

    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        //四分木作成
        _TRACE_("四分木作成開始");
        DefaultSpacetime::_pWorldQuadtree = NEW WorldQuadtree(CONFIG::WORLD_HIT_CHECK_QUADTREE_LEVEL,
                                                              _x_bound_left  ,_y_bound_bottom,
                                                              _x_bound_right ,_y_bound_top    );
        DefaultSpacetime::_pWorldQuadtreeRounder =
                _pWorldQuadtree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("四分木作成終了");
    } else {
        //八分木作成
        _TRACE_("八分木作成開始");
        DefaultSpacetime::_pWorldOctree = NEW WorldOctree(CONFIG::WORLD_HIT_CHECK_OCTREE_LEVEL,
                                                          _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                                          _x_bound_right ,_y_bound_top   , _z_bound_far   );
        DefaultSpacetime::_pWorldOctreeRounder =
                _pWorldOctree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("八分木作成終了");
    }

    //Board用四分木作成
    _TRACE_("Board用四分木作成開始");
    DefaultSpacetime::_pViewQuadtree = NEW ViewQuadtree(CONFIG::VIEW_HIT_CHECK_QUADTREE_LEVEL,
                                                        _x_bound_left_b  ,_y_bound_top_b,
                                                        _x_bound_right_b , _y_bound_bottom_b   );
    DefaultSpacetime::_pViewQuadtreeRounder =
            _pViewQuadtree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
    _TRACE_("Board用四分木作成終了");
}

void DefaultSpacetime::executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
#ifdef MY_DEBUG
    if (!_is_done_processSettlementBehavior) {
        throwCriticalException("DefaultSpacetime::executeWorldHitCheck() ツリーに要素がまだ登録されていません。本メソッドは processJudgement() で実行してください。");
    }
#endif
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        DefaultSpacetime::_pWorldQuadtreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    } else {
        DefaultSpacetime::_pWorldOctreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    }
}


void DefaultSpacetime::executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
#ifdef MY_DEBUG
    if (!_is_done_processSettlementBehavior) {
        throwCriticalException("DefaultSpacetime::executeViewHitCheck() ツリーに要素がまだ登録されていません。本メソッドは processJudgement() で実行してください。");
    }
#endif
    DefaultSpacetime::_pViewQuadtreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
}

void DefaultSpacetime::processSettlementBehavior() {
    GgafDx::Spacetime::processSettlementBehavior();
#ifdef MY_DEBUG
    _is_done_processSettlementBehavior = true;
    ViewCollisionChecker::_num_check_actors = 0;
    WorldCollisionChecker::_num_otoku_check = 0;
    WorldCollisionChecker::_num_zannen_check = 0;
    WorldCollisionChecker::_num_check_actors = 0;
#endif
}
void DefaultSpacetime::processJudgement() {
    GgafDx::Spacetime::processJudgement();
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check = 0;
        ViewCollisionChecker::_num_check = 0;
#endif
}

void DefaultSpacetime::processFinal() {
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        DefaultSpacetime::_pWorldQuadtree->clearAllElem();
    } else {
        DefaultSpacetime::_pWorldOctree->clearAllElem();
    }
    DefaultSpacetime::_pViewQuadtree->clearAllElem();
#ifdef MY_DEBUG
    _is_done_processSettlementBehavior = false;
#endif
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        _TRACE_("World四分木 -->");
        DefaultSpacetime::_pWorldQuadtree->putTree();
        _TRACE_("<--World四分木");
    } else {
        _TRACE_("World八分木 -->");
        DefaultSpacetime::_pWorldOctree->putTree();
        _TRACE_("<--World八分木");
    }
    _TRACE_("View四分木 -->");
    DefaultSpacetime::_pViewQuadtree->putTree();
    _TRACE_("<--View四分木");
    WorldCollisionChecker::releaseHitArea();
    ViewCollisionChecker::releaseHitArea();
#endif
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        GGAF_DELETE(DefaultSpacetime::_pWorldQuadtree);
        GGAF_DELETE(DefaultSpacetime::_pWorldQuadtreeRounder);
    } else {
        GGAF_DELETE(DefaultSpacetime::_pWorldOctree);
        GGAF_DELETE(DefaultSpacetime::_pWorldOctreeRounder);
    }
    GGAF_DELETE(DefaultSpacetime::_pViewQuadtree);
    GGAF_DELETE(DefaultSpacetime::_pViewQuadtreeRounder);
}
