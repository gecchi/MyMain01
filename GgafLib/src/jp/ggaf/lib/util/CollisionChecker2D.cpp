#include "jp/ggaf/lib/util/CollisionChecker2D.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/LinearQuadtree.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

CollisionChecker2D::CollisionChecker2D(GgafDx::GeometricActor* prm_pActor) : CollisionChecker(prm_pActor) ,
        _pLinearQuadtree(pGOD->getSpacetime()->getLinearQuadtree()),
        _pElem(NEW GgafCore::TreeElem<2u>(_pLinearQuadtree->_paQuadrant, prm_pActor))
{
}

void CollisionChecker2D::updateHitArea() {
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
            _TRACE_("＜警告＞ CollisionChecker2D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        pCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //最外域の境界AABB更新
        _pLinearQuadtree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                               pActor->_y + pCollisionArea->_aabb_y1,
                                               pActor->_x + pCollisionArea->_aabb_x2,
                                               pActor->_y + pCollisionArea->_aabb_y2);

    }
}

bool CollisionChecker2D::isHit(const GgafDx::Checker* const prm_pOppChecker) {
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
        CollisionChecker::_num_check++;
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
        for (int j = 0; j < opp_colli_part_num; j++) {
            const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
            if (!pOppColliPart->_is_valid_flg) { continue; }
#ifdef MY_DEBUG
            CollisionChecker::_num_check++;
#endif
            bool is_hit = (*UTIL::hit_check2d_func_table[pColliPart->_shape_kind | pOppColliPart->_shape_kind])(
                    pActor, pColliPart, pOppActor, pOppColliPart);
            if (is_hit) {
                pCollisionArea->_hit_colli_part_index = i;
                pOppCollisionArea->_hit_colli_part_index = j;
                return true;
            }
        }
    }
    return false;
}


CollisionChecker2D::~CollisionChecker2D() {
    delete _pElem;
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
