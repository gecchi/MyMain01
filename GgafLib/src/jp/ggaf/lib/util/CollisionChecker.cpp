#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

int CollisionChecker::_num_check = 0;
LinearOctreeForActor* CollisionChecker::_pLinearOctree = NULL;
CollisionChecker::CollisionChecker(GgafDxGeometricActor* prm_pActor) : GgafDxChecker(prm_pActor) {
    if (CollisionChecker::_pLinearOctree == NULL) {
        CollisionChecker::_pLinearOctree  = ((DefaultUniverse*)(GgafGod::_pGod->_pUniverse))->_pLinearOctree;
    }
    _pElem = NEW LinearOctreeActorElem(prm_pActor, 0);
    _need_update_aabb = true;
}

void CollisionChecker::makeCollision(int prm_nColliPart) {
    if (_pCollisionArea == NULL) {
        _pCollisionArea = NEW GgafDxCollisionArea(prm_nColliPart);
    } else {
        throwGgafCriticalException("CollisionChecker::makeCollision 既に makeCollision されています。");
    }
}

void CollisionChecker::setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rotX, bool rotY, bool rotZ) {
#ifdef MY_DEBUG
    if (_pCollisionArea == NULL) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_nColliPart) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == NULL) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliSphere();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwGgafCriticalException("CollisionChecker::setColliSphere()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はSPHEREでなかったため、更新はできません。");
    }
#endif
    ColliSphere* pSphere = (ColliSphere*)_pCollisionArea->_papColliPart[prm_index];
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rotX, rotY, rotZ);
    _need_update_aabb = true;
}


void CollisionChecker::setColliAAB(int prm_index,
                                   coord x1,
                                   coord y1,
                                   coord z1,
                                   coord x2,
                                   coord y2,
                                   coord z2,
                                   bool rotX,
                                   bool rotY,
                                   bool rotZ) {
#ifdef MY_DEBUG
    if (_pCollisionArea == NULL) {
        throwGgafCriticalException("CollisionChecker::setColliAAB()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_nColliPart) {
        throwGgafCriticalException("CollisionChecker::setColliAAB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == NULL) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAB();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAB) {
        throwGgafCriticalException("CollisionChecker::setColliAAB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はAABBでなかったため、更新はできません。");
    }
#endif
    ColliAAB* pAAB = (ColliAAB*)_pCollisionArea->_papColliPart[prm_index];
    pAAB->_shape_kind = COLLI_AAB;
    pAAB->_is_valid_flg = true;
    pAAB->set(x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);
    _need_update_aabb = true;
}

void CollisionChecker::setColliAAPrism(int prm_index,
                                       coord x1, coord y1, coord z1,
                                       coord x2, coord y2, coord z2,
                                       int pos_prism,
                                       bool rotX, bool rotY, bool rotZ) {
#ifdef MY_DEBUG
    if (_pCollisionArea == NULL) {
        throwGgafCriticalException("CollisionChecker::setColliAAPrism()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_nColliPart) {
        throwGgafCriticalException("CollisionChecker::setColliAAPrism()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == NULL) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAPrism();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPRISM) {
        throwGgafCriticalException("CollisionChecker::setColliAAPrism()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はAAPRISMでなかったため、更新はできません。");
    }
#endif
    ColliAAPrism* pAAPrism = (ColliAAPrism*)_pCollisionArea->_papColliPart[prm_index];
    pAAPrism->_shape_kind = COLLI_AAPRISM;
    pAAPrism->_is_valid_flg = true;
    pAAPrism->set(x1, y1, z1, x2, y2, z2, pos_prism, rotX, rotY, rotZ);
    _need_update_aabb = true;
}


void CollisionChecker::updateHitArea() {
    GgafDxGeometricActor* pActor = _pActor;
    GgafDxCollisionArea* pCollisionArea = _pCollisionArea;
    if (pActor == NULL || pCollisionArea == NULL) {
        return;
    }
    //if (_pActor->_can_hit_flg && _pActor->isActiveInTheTree() && _pActor->isOutOfView() == 0 ) {  //視野外は登録しない
    //if (pActor->_can_hit_flg && pActor->isActiveInTheTree() ) {
    if (pActor->isActiveInTheTree() ) {
        GgafDxCollisionPart* pColliPart;
        for (int i = 0; i < pCollisionArea->_nColliPart; i++) {
#ifdef MY_DEBUG
            if (_pCollisionArea->_papColliPart[i] == NULL) {
                throwGgafCriticalException("CollisionChecker::updateHitArea()["<<getTargetActor()->getName()<<"]  _papColliPart["<<i<<"]がNULLです。");
            }
#endif
            pColliPart = pCollisionArea->_papColliPart[i];

            if (pColliPart->_rotX || pColliPart->_rotY || pColliPart->_rotZ) {
                pColliPart->rotateRxRzRy(pActor->_RX, pActor->_RY, pActor->_RZ);
                _need_update_aabb = true;
            }
        }
        if (_need_update_aabb) {
            //最外域のAABB更新
            pCollisionArea->updateAABB();
            _need_update_aabb = false;
        }

        //８分木に登録！
        _pElem->_kindbit = pActor->getMyGroupHead()->_kind;
        _pLinearOctree->registElem(_pElem, pActor->_X + pCollisionArea->_AABB_X1,
                                           pActor->_Y + pCollisionArea->_AABB_Y1,
                                           pActor->_Z + pCollisionArea->_AABB_Z1,
                                           pActor->_X + pCollisionArea->_AABB_X2,
                                           pActor->_Y + pCollisionArea->_AABB_Y2,
                                           pActor->_Z + pCollisionArea->_AABB_Z2);

#ifdef MY_DEBUG
//        if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//            _TRACE_("  CollisionChecker::updateHitArea()  registElem("<<(_pActor->getName())<<")=("<<
//                                             (_pActor->_X + _pCollisionArea->_AABB_X1)<<","<<
//                                             (_pActor->_Y + _pCollisionArea->_AABB_Y1)<<","<<
//                                             (_pActor->_Z + _pCollisionArea->_AABB_Z1)<<","<<
//                                             (_pActor->_X + _pCollisionArea->_AABB_X2)<<","<<
//                                             (_pActor->_Y + _pCollisionArea->_AABB_Y2)<<","<<
//                                             (_pActor->_Z + _pCollisionArea->_AABB_Z2)<<")");
//            //_pLinearOctree->putTree();
//
//        }
#endif
    }
}


bool CollisionChecker::isHit(GgafDxCore::GgafDxChecker* prm_pOppChecker) {
    CollisionChecker* pOppCChecker = (CollisionChecker*)prm_pOppChecker;
    //TODO: だんだん肥大化してきた
    //当たり判定を行う相手のアクター
    GgafDxGeometricActor* pOppActor = pOppCChecker->_pActor;
    //相手の当たり判定領域
    GgafDxCollisionArea* pOppCollisionArea = pOppCChecker->_pCollisionArea;

//    if (_pCollisionArea == NULL || pOppCollisionArea == NULL ||
//        _pActor->isOutOfView() > 0 || pOppActor->isOutOfView() > 0 ) {  //視野外は判定しない

    if (_pCollisionArea == NULL || pOppCollisionArea == NULL) {
        return false;
    }

    GgafDxCollisionPart* pColliPart;
    GgafDxCollisionPart* pOppColliPart;
    int shape_kind, opp_shape_kind;
    for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
        pColliPart = _pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        shape_kind = pColliPart->_shape_kind;
        for (int j = 0; j < pOppCollisionArea->_nColliPart; j++) {
            pOppColliPart = pOppCollisionArea->_papColliPart[j];
            if (!pOppColliPart->_is_valid_flg) { continue; }
            opp_shape_kind = pOppColliPart->_shape_kind;
            CollisionChecker::_num_check++;
            if (shape_kind == COLLI_AAB) {
                if (opp_shape_kind == COLLI_AAB) {
                    //＜AAB と AAB＞
                    if (StgUtil::isHit(this        , _pActor  , (ColliAAB*)pColliPart,
                                       pOppCChecker, pOppActor, (ColliAAB*)pOppColliPart)) {
                        //自身の吹っ飛び結果の逆ベクトルを相手に伝搬
                        pOppCChecker->_blown_sgn_vX += -(this->_blown_sgn_vX);
                        pOppCChecker->_blown_sgn_vY += -(this->_blown_sgn_vY);
                        pOppCChecker->_blown_sgn_vZ += -(this->_blown_sgn_vZ);
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //＜AAB と 球＞
                     if (StgUtil::isHit(this        , _pActor  , (ColliAAB*)pColliPart,
                                        pOppCChecker, pOppActor, (ColliSphere*)pOppColliPart)) {
                         pOppCChecker->_blown_sgn_vX += -(this->_blown_sgn_vX);
                         pOppCChecker->_blown_sgn_vY += -(this->_blown_sgn_vY);
                         pOppCChecker->_blown_sgn_vZ += -(this->_blown_sgn_vZ);
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //＜AAB と AAPrism＞
                     if (StgUtil::isHit(pOppCChecker, pOppActor, (ColliAAPrism*)pOppColliPart,
                                        this        , _pActor  , (ColliAAB*)pColliPart)) {
                         this->_blown_sgn_vX += -(pOppCChecker->_blown_sgn_vX);
                         this->_blown_sgn_vY += -(pOppCChecker->_blown_sgn_vY);
                         this->_blown_sgn_vZ += -(pOppCChecker->_blown_sgn_vZ);
                         return true;
                     }
                 }

            } else if (shape_kind == COLLI_SPHERE) {
                if (opp_shape_kind == COLLI_AAB) {
                    //＜球 と AAB＞
                    if (StgUtil::isHit(pOppCChecker, pOppActor, (ColliAAB*)pOppColliPart,
                                       this        , _pActor  , (ColliSphere*)pColliPart)) {
                        this->_blown_sgn_vX += -(pOppCChecker->_blown_sgn_vX);
                        this->_blown_sgn_vY += -(pOppCChecker->_blown_sgn_vY);
                        this->_blown_sgn_vZ += -(pOppCChecker->_blown_sgn_vZ);
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜球 と 球＞
                    if (StgUtil::isHit(this        , _pActor  , (ColliSphere*)pColliPart,
                                       pOppCChecker, pOppActor, (ColliSphere*)pOppColliPart)) {
                        pOppCChecker->_blown_sgn_vX += -(this->_blown_sgn_vX);
                        pOppCChecker->_blown_sgn_vY += -(this->_blown_sgn_vY);
                        pOppCChecker->_blown_sgn_vZ += -(this->_blown_sgn_vZ);
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜球 と AAPrism＞
                    if (StgUtil::isHit(pOppCChecker, pOppActor, (ColliAAPrism*)pOppColliPart,
                                       this        , _pActor  , (ColliSphere*)pColliPart)) {
                        this->_blown_sgn_vX += -(pOppCChecker->_blown_sgn_vX);
                        this->_blown_sgn_vY += -(pOppCChecker->_blown_sgn_vY);
                        this->_blown_sgn_vZ += -(pOppCChecker->_blown_sgn_vZ);
                        return true;
                    }
                }

            } else if (shape_kind == COLLI_AAPRISM) {
                if (opp_shape_kind == COLLI_AAB) {
                    //＜AAPrism と AAB＞
                    if (StgUtil::isHit(this        , _pActor  , (ColliAAPrism*)pColliPart,
                                       pOppCChecker, pOppActor, (ColliAAB*)pOppColliPart)) {
                        pOppCChecker->_blown_sgn_vX += -(this->_blown_sgn_vX);
                        pOppCChecker->_blown_sgn_vY += -(this->_blown_sgn_vY);
                        pOppCChecker->_blown_sgn_vZ += -(this->_blown_sgn_vZ);
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜AAPrism と 球＞
                    if (StgUtil::isHit(this        , _pActor  , (ColliAAPrism*)pColliPart,
                                       pOppCChecker, pOppActor, (ColliSphere*)pOppColliPart)) {
                        pOppCChecker->_blown_sgn_vX += -(this->_blown_sgn_vX);
                        pOppCChecker->_blown_sgn_vY += -(this->_blown_sgn_vY);
                        pOppCChecker->_blown_sgn_vZ += -(this->_blown_sgn_vZ);
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                   //＜AAPrism と AAPrism＞
                   //TODO: 考えるだけで重たくなりそう、というかめんどくさそうな感じがする；。
                   //時間があれば考えよう・・・。今は未対応。
                   throwGgafCriticalException("AAPrism と AAPrismの当たり判定処理が存在します。未だ作ってません。 "<<
                                              _pActor->getName()<<" vs "<<pOppActor->getName());
                   return false;
                }
            }

        }

    }
    return false;
}



CollisionChecker::~CollisionChecker() {
    TRACE("CollisionChecker::~CollisionChecker() _pActor="<<_pActor->getName());
    DELETE_IMPOSSIBLE_NULL(_pElem);
    DELETE_POSSIBLE_NULL(_pCollisionArea);
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
