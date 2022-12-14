#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"

using namespace GgafLib;

DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) :
        GgafDx::Spacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
    _pWorldLinearOctree = nullptr;
    _pWorldLinearQuadtree = nullptr;
    _is_done_processPreJudgement = false;

    if (CONFIG::IS_HIT_CHECK_3D) {
        //八分木作成
        _TRACE_("八分木作成開始");
        _pWorldLinearOctree = NEW GgafCore::LinearOctree<GgafCore::Actor>(CONFIG::OCTREE_LEVEL,
                                                    _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                                    _x_bound_right ,_y_bound_top   , _z_bound_far   );
        _TRACE_("八分木作成終了");
    } else {
        //四分木作成
        _TRACE_("四分木作成開始");
        _pWorldLinearQuadtree = NEW GgafCore::LinearQuadtree<GgafCore::Actor>(CONFIG::QUADTREE_LEVEL,
                                                        _x_bound_left  ,_y_bound_bottom,
                                                        _x_bound_right ,_y_bound_top    );
        _TRACE_("四分木作成終了");
    }

    //Board用四分木作成
    _TRACE_("Board用四分木作成開始");
    _pViewLinearQuadtree = NEW ViewLinearQuadtree(2, _x_bound_left_b  ,_y_bound_top_b,
                                                     _x_bound_right_b , _y_bound_bottom_b   );
    _TRACE_("Board用四分木作成終了");
}

void DefaultSpacetime::executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
    if (_is_done_processPreJudgement) {
        if (CONFIG::IS_HIT_CHECK_3D) {
            _pWorldLinearOctree->executeAll(&GgafCore::Actor::executeHitChk_MeAnd, prm_kind_groupA, prm_kind_groupB);
        } else {
            _pWorldLinearQuadtree->executeAll(&GgafCore::Actor::executeHitChk_MeAnd , prm_kind_groupA, prm_kind_groupB);
        }
    } else {
        throwCriticalException("DefaultSpacetime::executeWorldHitCheck() ツリーに要素が登録されていません。本メソッドは processJudgement() で実行してください。");
    }

}


void DefaultSpacetime::executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
    if (_is_done_processPreJudgement) {
        _pViewLinearQuadtree->executeAll(&GgafCore::Actor::executeHitChk_MeAnd, prm_kind_groupA, prm_kind_groupB);
    } else {
        throwCriticalException("DefaultSpacetime::executeViewHitCheck() ツリーに要素が登録されていません。本メソッドは processJudgement() で実行してください。");
    }
}

void DefaultSpacetime::processPreJudgement() {
    GgafDx::Spacetime::processPreJudgement();
    _is_done_processPreJudgement = true;
}
void DefaultSpacetime::processFinal() {
    if (CONFIG::IS_HIT_CHECK_3D) {
        _pWorldLinearOctree->clearAllElem();
    } else {
        _pWorldLinearQuadtree->clearAllElem();
    }
    _pViewLinearQuadtree->clearAllElem();
    _is_done_processPreJudgement = false;
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    if (CONFIG::IS_HIT_CHECK_3D) {
        _TRACE_("World八分木 -->");
        _pWorldLinearOctree->putTree();
        _TRACE_("<--World八分木");
    } else {
        _TRACE_("World四分木 -->");
        _pWorldLinearQuadtree->putTree();
        _TRACE_("<--World四分木");
    }
    _TRACE_("View四分木 -->");
    _pViewLinearQuadtree->putTree();
    _TRACE_("<--View四分木");
    WorldCollisionChecker::releaseHitArea();
    ViewCollisionChecker::releaseHitArea();
#endif
    if (CONFIG::IS_HIT_CHECK_3D) {
        GGAF_DELETE(_pWorldLinearOctree);
    } else {
        GGAF_DELETE(_pWorldLinearQuadtree);
    }
    GGAF_DELETE(_pViewLinearQuadtree);
}
