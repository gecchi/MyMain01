#include "jp/ggaf/lib/util/CollisionChecker2D_b.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/LinearQuadtree.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/actor/BoardActor.h"
#include "jp/ggaf/dx/actor/BoardSetActor.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/model/BoardSetModel.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

CollisionChecker2D_b::CollisionChecker2D_b(GgafDx::GeometricActor* prm_pActor) : GgafDx::Checker(prm_pActor) ,
        _pLinearQuadtree_b(pCARETAKER->getSpacetime()->getLinearQuadtree_b()),
        _pElem(NEW GgafCore::TreeElem<2u>(_pLinearQuadtree_b->_paQuadrant, prm_pActor))
{
}

void CollisionChecker2D_b::updateHitArea() {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    if (pCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pActor;
    if (pActor->isActiveInTheTree()) {
        //四分木に登録！
        _pElem->_kind = pActor->lookUpKind();
#ifdef MY_DEBUG
        if (_pElem->_kind == 0) {
            _TRACE_("【警告】 CollisionChecker2D_b::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        pCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //最外域の境界AABB更新
        _pLinearQuadtree_b->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                               pActor->_y + pCollisionArea->_aabb_y1,
                                               pActor->_x + pCollisionArea->_aabb_x2,
                                               pActor->_y + pCollisionArea->_aabb_y2);

    }
}

bool CollisionChecker2D_b::isHit(const GgafDx::Checker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDx::GeometricActor* const pActor = _pActor;                //相手のアクター
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //相手のアクター

#ifdef MY_DEBUG
    CollisionChecker::_num_check++;
#endif
    if (pActor->_x + pCollisionArea->_aabb_x2 >= pOppActor->_x + pOppCollisionArea->_aabb_x1) {
        if (pActor->_x + pCollisionArea->_aabb_x1 <= pOppActor->_x + pOppCollisionArea->_aabb_x2) {
            if (pActor->_y + pCollisionArea->_aabb_y2 >= pOppActor->_y + pOppCollisionArea->_aabb_y1) {
                if (pActor->_y + pCollisionArea->_aabb_y1 <= pOppActor->_y + pOppCollisionArea->_aabb_y2) {
                    return true;
                }
            }
        }
    }
    return false;
}

void CollisionChecker2D_b::setColliAABox(int prm_index,
                                         coord x1,
                                         coord y1,
                                         coord x2,
                                         coord y2) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  まず createCollisionArea を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAABox();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AABOX) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はAABBでなかったため、更新はできません。");
    }
#endif
    ColliAABox* pAABox = (ColliAABox*)_pCollisionArea->_papColliPart[prm_index];
    pAABox->_shape_kind = COLLI_AABOX;
    pAABox->_is_valid_flg = true;
    pAABox->set(x1, y1, 0, x2, y2, 0, false, false, false);
//    _is_enable = true;
}

void CollisionChecker2D_b::setColliAABox(int prm_index, double per) {

//	Obj_GgafDx_BoardSetActor
    pixcoord w, h;
    Align a;
    Valign va;

//    GgafDx::Model* pModel = _pActor->getModel();
//    if (pModel->instanceOf(Obj_GgafDx_IPlaneModel)) {
//        GgafDx::IPlaneModel* pPlaneModel = (GgafDx::IPlaneModel*)pModel;
//        w = pPlaneModel->_model_width_px;
//        h = pPlaneModel->_model_height_px;
////        a = pActor->_align;
////        va = pActor->_valign;
//    }



    if (_pActor->instanceOf(Obj_GgafDx_BoardActor)) {
        GgafDx::BoardActor* pActor = (GgafDx::BoardActor*)_pActor;
        w = (pixcoord)pActor->getModelWidth();
        h = (pixcoord)pActor->getModelHeight();
        a = pActor->_align;
        va = pActor->_valign;
//        GgafDx::BoardModel* pModel= (GgafDx::BoardModel*)pActor->getModel();
    } else if (_pActor->instanceOf(Obj_GgafDx_BoardSetActor)) {
        GgafDx::BoardSetActor* pActor = (GgafDx::BoardSetActor*)_pActor;
        w = (pixcoord)pActor->getModelWidth();
        h = (pixcoord)pActor->getModelHeight();
//        GgafDx::BoardModel* pModel= (GgafDx::BoardModel*)pActor->getModel();
        a = pActor->_align;
        va = pActor->_valign;
    }

}

CollisionChecker2D_b::~CollisionChecker2D_b() {
    delete _pElem;
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
