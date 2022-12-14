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
        //�����؍쐬
        _TRACE_("�����؍쐬�J�n");
        _pWorldLinearOctree = NEW GgafCore::LinearOctree<GgafCore::Actor>(CONFIG::OCTREE_LEVEL,
                                                    _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                                    _x_bound_right ,_y_bound_top   , _z_bound_far   );
        _TRACE_("�����؍쐬�I��");
    } else {
        //�l���؍쐬
        _TRACE_("�l���؍쐬�J�n");
        _pWorldLinearQuadtree = NEW GgafCore::LinearQuadtree<GgafCore::Actor>(CONFIG::QUADTREE_LEVEL,
                                                        _x_bound_left  ,_y_bound_bottom,
                                                        _x_bound_right ,_y_bound_top    );
        _TRACE_("�l���؍쐬�I��");
    }

    //Board�p�l���؍쐬
    _TRACE_("Board�p�l���؍쐬�J�n");
    _pViewLinearQuadtree = NEW ViewLinearQuadtree(2, _x_bound_left_b  ,_y_bound_top_b,
                                                     _x_bound_right_b , _y_bound_bottom_b   );
    _TRACE_("Board�p�l���؍쐬�I��");
}

void DefaultSpacetime::executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
    if (_is_done_processPreJudgement) {
        if (CONFIG::IS_HIT_CHECK_3D) {
            _pWorldLinearOctree->executeAll(&GgafCore::Actor::executeHitChk_MeAnd, prm_kind_groupA, prm_kind_groupB);
        } else {
            _pWorldLinearQuadtree->executeAll(&GgafCore::Actor::executeHitChk_MeAnd , prm_kind_groupA, prm_kind_groupB);
        }
    } else {
        throwCriticalException("DefaultSpacetime::executeWorldHitCheck() �c���[�ɗv�f���o�^����Ă��܂���B�{���\�b�h�� processJudgement() �Ŏ��s���Ă��������B");
    }

}


void DefaultSpacetime::executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
    if (_is_done_processPreJudgement) {
        _pViewLinearQuadtree->executeAll(&GgafCore::Actor::executeHitChk_MeAnd, prm_kind_groupA, prm_kind_groupB);
    } else {
        throwCriticalException("DefaultSpacetime::executeViewHitCheck() �c���[�ɗv�f���o�^����Ă��܂���B�{���\�b�h�� processJudgement() �Ŏ��s���Ă��������B");
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
        _TRACE_("World������ -->");
        _pWorldLinearOctree->putTree();
        _TRACE_("<--World������");
    } else {
        _TRACE_("World�l���� -->");
        _pWorldLinearQuadtree->putTree();
        _TRACE_("<--World�l����");
    }
    _TRACE_("View�l���� -->");
    _pViewLinearQuadtree->putTree();
    _TRACE_("<--View�l����");
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
