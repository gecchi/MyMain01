#include "jp/ggaf/lib/util/CollisionChecker3D.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliAAB.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/LinearOctreeActorElem.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

int CollisionChecker3D::_num_check = 0;
CollisionChecker3D::CollisionChecker3D(GgafDxGeometricActor* prm_pActor) : GgafDxChecker(prm_pActor) ,
        _pLinearOctree(P_GOD->getSpacetime()->getLinearOctree()),
        _pElem(NEW LinearOctreeActorElem(_pLinearOctree, prm_pActor, 0))
{
    _need_update_aabb = true;
}

void CollisionChecker3D::setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("CollisionChecker3D::setColli_AABB()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("CollisionChecker3D::setColli_AABB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliSphere();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwGgafCriticalException("CollisionChecker3D::setColliSphere()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はSPHEREでなかったため、更新はできません。");
    }
#endif
#ifdef MY_DEBUG
    if (r < 0) {
        throwGgafCriticalException("CollisionChecker3D::setColliSphere()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"のSPHEREの半径が負の数です。r="<<r);
    }
#endif
    ColliSphere* pSphere = (ColliSphere*)_pCollisionArea->_papColliPart[prm_index];
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}


void CollisionChecker3D::setColliAAB(int prm_index,
                                     coord x1,
                                     coord y1,
                                     coord z1,
                                     coord x2,
                                     coord y2,
                                     coord z2,
                                     bool rot_x,
                                     bool rot_y,
                                     bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAB()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAB();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAB) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はAABBでなかったため、更新はできません。");
    }
#endif
    ColliAAB* pAAB = (ColliAAB*)_pCollisionArea->_papColliPart[prm_index];
    pAAB->_shape_kind = COLLI_AAB;
    pAAB->_is_valid_flg = true;
    pAAB->set(x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}

void CollisionChecker3D::setColliAAPrism(int prm_index,
                                         coord x1, coord y1, coord z1,
                                         coord x2, coord y2, coord z2,
                                         int pos_prism,
                                         bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAPrism()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAPrism()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAPrism();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPRISM) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAPrism()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はAAPRISMでなかったため、更新はできません。");
    }
#endif
    ColliAAPrism* pAAPrism = (ColliAAPrism*)_pCollisionArea->_papColliPart[prm_index];
    pAAPrism->_shape_kind = COLLI_AAPRISM;
    pAAPrism->_is_valid_flg = true;
    pAAPrism->set(x1, y1, z1, x2, y2, z2, pos_prism, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}

void CollisionChecker3D::updateHitArea() {
    GgafDxGeometricActor* const pActor = _pActor;
    GgafDxCollisionArea* const pCollisionArea = _pCollisionArea;
    if (pActor == nullptr || pCollisionArea == nullptr) {
        return;
    }
    if (pActor->isActiveInTheTree() && pActor->isActive()) {
        GgafDxCollisionPart* pColliPart;
        for (int i = 0; i < pCollisionArea->_colli_part_num; i++) {
#ifdef MY_DEBUG
            if (_pCollisionArea->_papColliPart[i] == nullptr) {
                throwGgafCriticalException("CollisionChecker3D::updateHitArea()["<<getTargetActor()->getName()<<"]  _papColliPart["<<i<<"]がnullptrです。");
            }
#endif
            pColliPart = pCollisionArea->_papColliPart[i];
            if (pColliPart->_rot) {
                pColliPart->rotateRxRzRy(pActor->_rx, pActor->_ry, pActor->_rz);
                _need_update_aabb = true;
            }
        }
        if (_need_update_aabb) {
            pCollisionArea->updateAABB(); //最外域の境界AABB更新
            _need_update_aabb = false;
        }

        //八分木に登録！
        _pElem->_kindbit = pActor->getMyGroupHead()->_kind;
#ifdef MY_DEBUG
        if (_pElem->_kindbit == 0) {
            _TRACE_("＜警告＞ CollisionChecker3D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        _pLinearOctree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                             pActor->_y + pCollisionArea->_aabb_y1,
                                             pActor->_z + pCollisionArea->_aabb_z1,
                                             pActor->_x + pCollisionArea->_aabb_x2,
                                             pActor->_y + pCollisionArea->_aabb_y2,
                                             pActor->_z + pCollisionArea->_aabb_z2);

    }
}


bool CollisionChecker3D::isHit(const GgafDxCore::GgafDxChecker* const prm_pOppChecker) {
    GgafDxCollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDxCollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDxGeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //相手のアクター
    const int colli_part_num = pCollisionArea->_colli_part_num;
    for (int i = 0; i < colli_part_num; i++) {
        const GgafDxCollisionPart* const pColliPart = pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        const int shape_kind = pColliPart->_shape_kind;
        const int opp_colli_part_num = pOppCollisionArea->_colli_part_num; //相手の当たり判定要素数
        for (int j = 0; j < opp_colli_part_num; j++) {
            const GgafDxCollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
            if (!pOppColliPart->_is_valid_flg) { continue; }
            const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
            CollisionChecker3D::_num_check++;
#endif
            if (shape_kind == COLLI_AAB) {
                if (opp_shape_kind == COLLI_AAB) {
                    //＜AAB と AAB＞
                    if (UTIL::isHit(_pActor  , (ColliAAB*)pColliPart,
                                    pOppActor, (ColliAAB*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //＜AAB と 球＞
                     if (UTIL::isHit(_pActor  , (ColliAAB*)pColliPart,
                                     pOppActor, (ColliSphere*)pOppColliPart)) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //＜AAB と AAPrism＞
                     if (UTIL::isHit(pOppActor, (ColliAAPrism*)pOppColliPart,
                                     _pActor  , (ColliAAB*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 }

            } else if (shape_kind == COLLI_SPHERE) {
                if (opp_shape_kind == COLLI_AAB) {
                    //＜球 と AAB＞
                    if (UTIL::isHit(pOppActor, (ColliAAB*)pOppColliPart,
                                    _pActor  , (ColliSphere*)pColliPart )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜球 と 球＞
                    if (UTIL::isHit(_pActor  , (ColliSphere*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜球 と AAPrism＞
                    if (UTIL::isHit(pOppActor, (ColliAAPrism*)pOppColliPart,
                                    _pActor  , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }

            } else if (shape_kind == COLLI_AAPRISM) {
                if (opp_shape_kind == COLLI_AAB) {
                    //＜AAPrism と AAB＞
                    if (UTIL::isHit(_pActor  , (ColliAAPrism*)pColliPart,
                                    pOppActor, (ColliAAB*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜AAPrism と 球＞
                    if (UTIL::isHit(_pActor  , (ColliAAPrism*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                   //＜AAPrism と AAPrism＞
                   //TODO: 考えるだけで重たくなりそう、というかめんどくさそうな感じがする；。
                   //時間があれば考えよう・・・。今は未対応。
                   throwGgafCriticalException("AAPrism と AAPrismの当たり判定処理が存在します。そんな処理は未だ作ってません。 "<<
                                              _pActor->getName()<<" vs "<<pOppActor->getName());
                   return false;
                }
            }

        }

    }
    return false;
}


CollisionChecker3D::~CollisionChecker3D() {
    delete _pElem;
    GGAF_DELETE_NULLABLE(_pCollisionArea);
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
