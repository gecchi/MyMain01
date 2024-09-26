#include "jp/ggaf/lib/util/ViewCollisionChecker.h"

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
#ifdef MY_DEBUG
unsigned int ViewCollisionChecker::_num_check = 0;
unsigned int ViewCollisionChecker::_num_check_actors = 0;
#endif
ViewCollisionChecker::ViewCollisionChecker(GgafDx::GeometricActor* prm_pActor) : GgafDx::CollisionChecker(prm_pActor)
{
}

void ViewCollisionChecker::updateHitArea() {
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    if (pActiveCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pColliActor;
    if (pActor->isActiveInTheTree()) {
        //四分木に登録！
#ifdef MY_DEBUG
        if (_kind == 0) {
            _TRACE_("【警告】 ViewCollisionChecker::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        pActiveCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //最外域の境界AABB更新
        DefaultSpacetime::_pViewQuadtree->registerElem(this, pActor->_x + pActiveCollisionArea->_aabb_x1,
                                                               pActor->_y + pActiveCollisionArea->_aabb_y1,
                                                               pActor->_x + pActiveCollisionArea->_aabb_x2,
                                                               pActor->_y + pActiveCollisionArea->_aabb_y2);
#ifdef MY_DEBUG
        ViewCollisionChecker::_num_check_actors++;
#endif
    }
}

bool ViewCollisionChecker::isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    //TODO:WorldCollisionChecker2D::isHit() のコピペ、２重管理を何とかする
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppActiveCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDx::GeometricActor* const pActor = _pColliActor;                //相手のアクター
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pColliActor;                //相手のアクター
    const int colli_part_num = pActiveCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppActiveCollisionArea->_colli_part_num; //相手の当たり判定要素数

//    //複数の当たり判定要素をもつアクター同士の場合、
//    //まず最外境界AABoxで当たり判定を行って、ヒットすれば厳密に当たり判定を行う。
//    if (colli_part_num > 1 && opp_colli_part_num > 1) {
//#ifdef MY_DEBUG
//        ViewCollisionChecker::_num_check++;
//#endif
//        bool is_hit_bound_aabb = false;
//        if (pActor->_x + pActiveCollisionArea->_aabb_x2 >= pOppActor->_x + pOppActiveCollisionArea->_aabb_x1) {
//            if (pActor->_x + pActiveCollisionArea->_aabb_x1 <= pOppActor->_x + pOppActiveCollisionArea->_aabb_x2) {
//                if (pActor->_y + pActiveCollisionArea->_aabb_y2 >= pOppActor->_y + pOppActiveCollisionArea->_aabb_y1) {
//                    if (pActor->_y + pActiveCollisionArea->_aabb_y1 <= pOppActor->_y + pOppActiveCollisionArea->_aabb_y2) {
//                        is_hit_bound_aabb = true;
//                    }
//                }
//            }
//        }
//        if (!is_hit_bound_aabb) {
//            //最外境界AABoxでヒットしていない
//            return false;
//        }
//    }

    for (int i = 0; i < colli_part_num; i++) {
        const GgafDx::CollisionPart* const pColliPart = pActiveCollisionArea->_papColliPart[i];
        const int shape_kind = pColliPart->_shape_kind;

        if (shape_kind == COLLI_AABOX) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                ViewCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜長方形 と 長方形＞
                    if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //＜長方形 と 円＞
                     if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                       pOppActor, (ColliSphere*)pOppColliPart)) {
                         pActiveCollisionArea->_hit_colli_part_index = i;
                         pOppActiveCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //＜長方形 と 直角三角形＞
                     if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pActiveCollisionArea->_hit_colli_part_index = i;
                         pOppActiveCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                     //＜長方形 と AAPyramid＞
                    _TRACE_("【警告】2Dで AAB と AAPyramid の当たり判定処理が存在します。AAPyramidの2D当たり判定はありません "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                 }
            }
        } else if (shape_kind == COLLI_SPHERE) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                ViewCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜円 と 長方形＞
                    if (UTIL::isHit2D(pOppActor, (ColliAABox*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart )) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜円 と 円＞
                    if (UTIL::isHit2D(pActor  , (ColliSphere*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜円 と 直角三角形＞
                    if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //＜円 と 直角三角形＞
                    _TRACE_("【警告】2Dで 球 と AAPyramid の当たり判定処理が存在します。AAPyramidの2D当たり判定はありません "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }
        } else if (shape_kind == COLLI_AAPRISM) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                ViewCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜直角三角形 と 長方形＞
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜直角三角形 と 円＞
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜直角三角形 と 直角三角形＞
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAAPrism*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //＜直角三角形 と AAPyramid＞
                    _TRACE_("【警告】2Dで AAPrism と AAPyramid の当たり判定処理が存在します。AAPyramidの2D当たり判定はありません "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                 }
            }
        } else if (shape_kind == COLLI_AAPYRAMID) {
            _TRACE_("【警告】2Dで AAPyramid の当たり判定処理が存在します。AAPyramidの2D当たり判定はありません "<<
                    pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
            return false;
        }
    }
    return false;
}


bool ViewCollisionChecker::isHit_old(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppActiveCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDx::GeometricActor* const pActor = _pColliActor;                //相手のアクター
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pColliActor;                //相手のアクター

#ifdef MY_DEBUG
    ViewCollisionChecker::_num_check++;
#endif
    if (pActor->_x + pActiveCollisionArea->_aabb_x2 >= pOppActor->_x + pOppActiveCollisionArea->_aabb_x1) {
        if (pActor->_x + pActiveCollisionArea->_aabb_x1 <= pOppActor->_x + pOppActiveCollisionArea->_aabb_x2) {
            if (pActor->_y + pActiveCollisionArea->_aabb_y2 >= pOppActor->_y + pOppActiveCollisionArea->_aabb_y1) {
                if (pActor->_y + pActiveCollisionArea->_aabb_y1 <= pOppActor->_y + pOppActiveCollisionArea->_aabb_y2) {
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
        throwCriticalException("["<<getTargetActor()->getName()<<"]  まず addCollisionArea を実行して、要素数を宣言してください。");
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
