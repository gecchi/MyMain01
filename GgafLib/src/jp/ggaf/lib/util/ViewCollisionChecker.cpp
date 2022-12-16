#include "jp/ggaf/lib/util/ViewCollisionChecker.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/actor/BoardActor.h"
#include "jp/ggaf/dx/actor/BoardSetActor.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/model/BoardSetModel.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/debug/ColliAABoardRectActor.h"
#endif

using namespace GgafLib;

ViewCollisionChecker::ViewCollisionChecker(GgafDx::GeometricActor* prm_pActor) : GgafDx::CollisionChecker(prm_pActor) ,
        _pViewLinearQuadtree(pCARETAKER->getSpacetime()->getViewLinearQuadtree())
{
}

void ViewCollisionChecker::updateHitArea() {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    if (pCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pActor;
    if (pActor->isActiveInTheTree()) {
        //四分木に登録！
//        _pNodeElem->_kind = pActor->lookUpKind();
#ifdef MY_DEBUG
        if (pActor->_kind == 0) {
            _TRACE_("【警告】 ViewCollisionChecker::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        pCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //最外域の境界AABB更新
        _pViewLinearQuadtree->registerElem(pActor, pActor->_x + pCollisionArea->_aabb_x1,
                                                       pActor->_y + pCollisionArea->_aabb_y1,
                                                       pActor->_x + pCollisionArea->_aabb_x2,
                                                       pActor->_y + pCollisionArea->_aabb_y2);

    }
}

bool ViewCollisionChecker::isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDx::GeometricActor* const pActor = _pActor;                //相手のアクター
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //相手のアクター

#ifdef MY_DEBUG
    WorldCollisionChecker::_num_check++;
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

void ViewCollisionChecker::setColliAABox(int prm_index,
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

void ViewCollisionChecker::setColliAABox(int prm_index, double prm_per) {
    setColliAABox(prm_index, prm_per, prm_per);
}
void ViewCollisionChecker::setColliAABox(int prm_index, double per_x, double pre_y) {
    pixcoord model_width = 0;
    pixcoord model_height = 0;
    Align align;
    Valign valign;
    if (_pActor->instanceOf(Obj_GgafDx_IAlignAbleActor)) {
        GgafDx::IAlignAbleActor* pIAlignAbleActor = dynamic_cast<GgafDx::IAlignAbleActor*>(_pActor); //成立するcrosscast
#ifdef MY_DEBUG
        if (!pIAlignAbleActor) {
            throwCriticalException("["<<getTargetActor()->getName()<<"]  IAlignAbleActorにキャストできません。おかしい。");
        }
#endif
        GgafDx::FigureActor* pFigureActor = dynamic_cast<GgafDx::FigureActor*>(_pActor);
        align = pIAlignAbleActor->_align;
        valign = pIAlignAbleActor->_valign;
        GgafDx::Model* pModel = pFigureActor->getModel();
        if (pModel->instanceOf(Obj_GgafDx_IPlaneModel)) {
            GgafDx::IPlaneModel* pPlaneModel = dynamic_cast<GgafDx::IPlaneModel*>(pModel); //成立するcrosscast
#ifdef MY_DEBUG
            if (!pPlaneModel) {
                throwCriticalException("["<<getTargetActor()->getName()<<"]  モデルが、IPlaneModelにキャストできません。おかしい。");
            }
#endif
            model_width = pPlaneModel->_model_width_px;
            model_height = pPlaneModel->_model_height_px;
        }
    }

    if (_pActor->instanceOf(Obj_FontBoardActor)) {
        FontBoardActor* pFontBoardActor = dynamic_cast<FontBoardActor*>(_pActor);
#ifdef MY_DEBUG
        if (!pFontBoardActor) {
            throwCriticalException("["<<getTargetActor()->getName()<<"]  FontBoardActor にキャストできません。おかしい。");
        }
#endif
        model_width = pFontBoardActor->_px_total_width;
        model_height = pFontBoardActor->_px_total_height;
    }

    if (model_width == 0 && model_height == 0) {
        throwCriticalException("["<<getTargetActor()->getName()<<"] このアクターは、ヒットエリアの割合指定の setColliAABox() ができません。");
    }
    coord x1, y1, x2, y2;
    if (align == ALIGN_LEFT) {
        x1 = PX_C((model_width - (model_width*per_x)) / 2.0);
    } else if (align == ALIGN_CENTER) {
        x1 = PX_C(-model_width*per_x/ 2.0);
    } else  {  //ALIGN_RIGHT
        x1 = PX_C(-model_width + ((model_width - (model_width*per_x)) / 2.0));
    }
    x2 = x1 + PX_C(model_width*per_x);

    if (valign == VALIGN_TOP) {
        y1 = PX_C((model_height - (model_height*pre_y)) / 2.0);
    } else if (valign == VALIGN_MIDDLE) {
        y1 = PX_C(-model_height*pre_y/ 2.0);
    } else { //VALIGN_BOTTOM
        y1 = PX_C(-model_height + ((model_height - (model_height*pre_y)) / 2.0));
    }
    y2 = y1 + PX_C(model_height*pre_y);
    setColliAABox(prm_index, x1, y1, x2, y2);
}

void ViewCollisionChecker::setColliSquare(int prm_index, coord prm_edge) {
    pixcoord model_width = 0;
    pixcoord model_height = 0;
    Align align;
    Valign valign;
    if (_pActor->instanceOf(Obj_GgafDx_IAlignAbleActor)) {
        GgafDx::IAlignAbleActor* pIAlignAbleActor = dynamic_cast<GgafDx::IAlignAbleActor*>(_pActor); //成立するcrosscast
#ifdef MY_DEBUG
        if (!pIAlignAbleActor) {
            throwCriticalException("["<<getTargetActor()->getName()<<"]  IAlignAbleActorにキャストできません。おかしい。");
        }
#endif
        GgafDx::FigureActor* pFigureActor = dynamic_cast<GgafDx::FigureActor*>(_pActor);
        align = pIAlignAbleActor->_align;
        valign = pIAlignAbleActor->_valign;
        GgafDx::Model* pModel = pFigureActor->getModel();
        if (pModel->instanceOf(Obj_GgafDx_IPlaneModel)) {
            GgafDx::IPlaneModel* pPlaneModel = dynamic_cast<GgafDx::IPlaneModel*>(pModel); //成立するcrosscast
#ifdef MY_DEBUG
            if (!pPlaneModel) {
                throwCriticalException("["<<getTargetActor()->getName()<<"]  モデルが、IPlaneModelにキャストできません。おかしい。");
            }
#endif
            model_width = pPlaneModel->_model_width_px;
            model_height = pPlaneModel->_model_height_px;
        }
    }
    if (model_width == 0 && model_height == 0) {
        throwCriticalException("["<<getTargetActor()->getName()<<"] このアクターは、ヒットエリアの割合指定の setColliAABox() ができません。");
    }
    coord x1, y1, x2, y2;
    if (align == ALIGN_LEFT) {
        x1 = PX_C((model_width - C_PX(prm_edge)) / 2.0);
    } else if (align == ALIGN_CENTER) {
        x1 = PX_C(-C_PX(prm_edge) / 2.0);
    } else  {  //ALIGN_RIGHT
        x1 = PX_C(-model_width + ((model_width - C_PX(prm_edge)) / 2.0));
    }
    x2 = x1 + PX_C(C_PX(prm_edge));

    if (valign == VALIGN_TOP) {
        y1 = PX_C((model_height - (C_PX(prm_edge))) / 2.0);
    } else if (valign == VALIGN_MIDDLE) {
        y1 = PX_C(-C_PX(prm_edge)/ 2.0);
    } else { //VALIGN_BOTTOM
        y1 = PX_C(-model_height + ((model_height - C_PX(prm_edge)) / 2.0));
    }
    y2 = y1 + PX_C(C_PX(prm_edge));
    setColliAABox(prm_index, x1, y1, x2, y2);
}

void ViewCollisionChecker::drawHitArea(GgafDx::CollisionChecker* prm_pChecker) {
#ifdef MY_DEBUG
    ColliAABoardRectActor::get()->drawHitarea(prm_pChecker);
#endif
}

void ViewCollisionChecker::releaseHitArea() {
#ifdef MY_DEBUG
    ColliAABoardRectActor::release();
#endif
}


ViewCollisionChecker::~ViewCollisionChecker() {
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
