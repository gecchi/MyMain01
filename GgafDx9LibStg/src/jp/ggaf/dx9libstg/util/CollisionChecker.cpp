#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

int CollisionChecker::_num_check = 0;
LinearOctreeForActor* CollisionChecker::_pLinearOctree = NULL;
CollisionChecker::CollisionChecker(GgafDx9GeometricActor* prm_pActor) : GgafDx9Checker(prm_pActor) {
    _pCollisionArea = NULL;
    if (CollisionChecker::_pLinearOctree == NULL) {
        CollisionChecker::_pLinearOctree  = ((DefaultUniverse*)(GgafGod::_pGod->_pUniverse))->_pLinearOctree;
    }
    _pElem = new LOFA_Elem(prm_pActor, 0);
    _need_update_aabb = true;
}

void CollisionChecker::makeCollision(int prm_nColliPart) {
    if (_pCollisionArea == NULL) {
        _pCollisionArea = NEW GgafDx9CollisionArea(prm_nColliPart);
    } else {
        throwGgafCriticalException("CollisionChecker::useHitAreaBoxNum HitAreaBoxsは既に new されています。");
    }
}

void CollisionChecker::setColliBox(int prm_index,
                                       int x1,
                                       int y1,
                                       int z1,
                                       int x2,
                                       int y2,
                                       int z2,
                                       bool rotX,
                                       bool rotY,
                                       bool rotZ) {
#ifdef MY_DEBUG
    if (_pCollisionArea == NULL) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  まず makeCollision を実行して、要素数を宣言してください。");
    }
    if (prm_index > _pCollisionArea->_nColliPart) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"は範囲外。");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == NULL) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliBox();
    }
    ColliBox* pBox = (ColliBox*)_pCollisionArea->_papColliPart[prm_index];
    pBox->_shape_kind = COLLI_AABB;
    pBox->_is_valid_flg = true;
    pBox->set(x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);
    _need_update_aabb = true;
}

void CollisionChecker::updateHitArea() {
    if (_pActor == NULL || _pCollisionArea == NULL) {
        return;
    }
    if (_pActor->_can_bump_flg && _pActor->isActive() && _pActor->isOffscreen() == 0 ) {
        GgafDx9CollisionPart* pColliPart;
        for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
            pColliPart = _pCollisionArea->_papColliPart[i];
            if (pColliPart->rotate(_pActor->_RX, _pActor->_RY, _pActor->_RZ)) {
                _need_update_aabb = true;
            }
        }
        if (_need_update_aabb) {
            //境界領域更新
            _pCollisionArea->updateAABB();
        }
        _pElem->_kindbit = _pActor->getGroupActor()->_kind;
        _pLinearOctree->registElem(_pElem, _pActor->_X + _pCollisionArea->_AABB_X1,
                                           _pActor->_Y + _pCollisionArea->_AABB_Y1,
                                           _pActor->_Z + _pCollisionArea->_AABB_Z1,
                                           _pActor->_X + _pCollisionArea->_AABB_X2,
                                           _pActor->_Y + _pCollisionArea->_AABB_Y2,
                                           _pActor->_Z + _pCollisionArea->_AABB_Z2);

#ifdef MY_DEBUG
        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
            _TRACE_("  CollisionChecker::updateHitArea()  registElem("<<(_pActor->getName())<<")=("<<
                                             (_pActor->_X + _pCollisionArea->_AABB_X1)<<","<<
                                             (_pActor->_Y + _pCollisionArea->_AABB_Y1)<<","<<
                                             (_pActor->_Z + _pCollisionArea->_AABB_Z1)<<","<<
                                             (_pActor->_X + _pCollisionArea->_AABB_X2)<<","<<
                                             (_pActor->_Y + _pCollisionArea->_AABB_Y2)<<","<<
                                             (_pActor->_Z + _pCollisionArea->_AABB_Z2)<<")");
            _pLinearOctree->putTree();

        }
#endif
    }
}


bool CollisionChecker::isBump(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker) {
    static GgafDx9Core::GgafDx9GeometricActor* pOtherActor;
    static GgafDx9CollisionArea* pOtherCollisionArea;

    pOtherActor = prm_pOtherChecker->getTargetActor();
    pOtherCollisionArea = ((CollisionChecker*)prm_pOtherChecker)->_pCollisionArea;
    if (_pCollisionArea == NULL || pOtherCollisionArea == NULL ||
        _pActor->isOffscreen() > 0 || pOtherActor->isOffscreen() > 0 ) {
        return false;
    } else {
        //自分の箱と相手の箱
        ColliBox* pBox;
        ColliBox* pOtherBox;
        for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
            pBox = (ColliBox*)_pCollisionArea->_papColliPart[i];
            if (pBox->_is_valid_flg) {
                for (int j = 0; j < pOtherCollisionArea->_nColliPart; j++) {
                    pOtherBox = (ColliBox*)pOtherCollisionArea->_papColliPart[j];
                    if (pOtherBox->_is_valid_flg) {
                        CollisionChecker::_num_check++;
                        if (_pActor->_Z + pBox->_z2 >= pOtherActor->_Z + pOtherBox->_z1) {
                            if (_pActor->_Z + pBox->_z1 <= pOtherActor->_Z + pOtherBox->_z2) {
                                if (_pActor->_X + pBox->_x2 >= pOtherActor->_X + pOtherBox->_x1) {
                                    if (_pActor->_X + pBox->_x1 <= pOtherActor->_X + pOtherBox->_x2) {
                                        if (_pActor->_Y + pBox->_y2 >= pOtherActor->_Y + pOtherBox->_y1) {
                                            if (_pActor->_Y + pBox->_y1 <= pOtherActor->_Y + pOtherBox->_y2) {
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
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
