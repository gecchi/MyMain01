#include "jp/ggaf/lib/util/WorldCollisionChecker2D.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

WorldCollisionChecker2D::WorldCollisionChecker2D(GgafDx::GeometricActor* prm_pActor) : WorldCollisionChecker(prm_pActor) ,
        _pLinearQuadtree(pCARETAKER->getSpacetime()->getLinearQuadtree()),
        _pElem(NEW GgafCore::LinearQuadtree<GgafCore::Actor>::NodeElem(prm_pActor))
{
}

void WorldCollisionChecker2D::updateHitArea() {
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
            _TRACE_("【警告】 WorldCollisionChecker2D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        pCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //最外域の境界AABB更新
        _pLinearQuadtree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                               pActor->_y + pCollisionArea->_aabb_y1,
                                               pActor->_x + pCollisionArea->_aabb_x2,
                                               pActor->_y + pCollisionArea->_aabb_y2);

    }
}

bool WorldCollisionChecker2D::isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDx::GeometricActor* const pActor = _pActor;                //相手のアクター
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //相手のアクター
    const int colli_part_num = pCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppCollisionArea->_colli_part_num; //相手の当たり判定要素数

    //複数の当たり判定要素をもつアクター同士の場合、
    //まず最外境界AABoxで当たり判定を行って、ヒットすれば厳密に当たり判定を行う。
    if (colli_part_num > 1 && opp_colli_part_num > 1) {
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check++;
#endif
        bool is_hit_bound_aabb = false;
        if (pActor->_x + pCollisionArea->_aabb_x2 >= pOppActor->_x + pOppCollisionArea->_aabb_x1) {
            if (pActor->_x + pCollisionArea->_aabb_x1 <= pOppActor->_x + pOppCollisionArea->_aabb_x2) {
                if (pActor->_y + pCollisionArea->_aabb_y2 >= pOppActor->_y + pOppCollisionArea->_aabb_y1) {
                    if (pActor->_y + pCollisionArea->_aabb_y1 <= pOppActor->_y + pOppCollisionArea->_aabb_y2) {
                        is_hit_bound_aabb = true;
                    }
                }
            }
        }
        if (!is_hit_bound_aabb) {
            //最外境界AABoxでヒットしていない
            return false;
        }
    }

    for (int i = 0; i < colli_part_num; i++) {
        const GgafDx::CollisionPart* const pColliPart = pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        const int shape_kind = pColliPart->_shape_kind;

        if (shape_kind == COLLI_AABOX) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜長方形 と 長方形＞
                    if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //＜長方形 と 円＞
                     if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                       pOppActor, (ColliSphere*)pOppColliPart)) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //＜長方形 と 直角三角形＞
                     if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
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
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜円 と 長方形＞
                    if (UTIL::isHit2D(pOppActor, (ColliAABox*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜円 と 円＞
                    if (UTIL::isHit2D(pActor  , (ColliSphere*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜円 と 直角三角形＞
                    if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
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
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜直角三角形 と 長方形＞
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜直角三角形 と 円＞
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜直角三角形 と 直角三角形＞
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAAPrism*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
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


WorldCollisionChecker2D::~WorldCollisionChecker2D() {
    delete _pElem;
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
