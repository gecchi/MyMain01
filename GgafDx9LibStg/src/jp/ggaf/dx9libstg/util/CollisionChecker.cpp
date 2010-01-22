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

void CollisionChecker::setColliSphere(int prm_index, int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ) {
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
    } else if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwGgafCriticalException("CollisionChecker::setColliSphere()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はSPHEREでなかったため、更新はできません。");
    }

    ColliSphere* pSphere = (ColliSphere*)_pCollisionArea->_papColliPart[prm_index];
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rotX, rotY, rotZ);
    _need_update_aabb = true;
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
    } else if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AABB) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  要素インデックス"<<prm_index<<"はAABBでなかったため、更新はできません。");
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
    if (_pActor->_can_collide_flg && _pActor->isActive() && _pActor->isOffscreen() == 0 ) {
        GgafDx9CollisionPart* pColliPart;
        for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
#ifdef MY_DEBUG
            if (_pCollisionArea->_papColliPart[i] == NULL) {
                throwGgafCriticalException("CollisionChecker::updateHitArea()["<<getTargetActor()->getName()<<"]  _papColliPart["<<i<<"]がNULLです。");
            }
#endif
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
        GgafDx9CollisionPart* pColliPart;
        GgafDx9CollisionPart* pOtherColliPart;
        for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
            pColliPart = _pCollisionArea->_papColliPart[i];
            if (pColliPart->_is_valid_flg) {
                for (int j = 0; j < pOtherCollisionArea->_nColliPart; j++) {
                    pOtherColliPart = pOtherCollisionArea->_papColliPart[j];
                    if (pOtherColliPart->_is_valid_flg) {
                        CollisionChecker::_num_check++;


                        if (pColliPart->_shape_kind == COLLI_AABB && pOtherColliPart->_shape_kind == COLLI_AABB) {
                            //AABB AABB
                            ColliBox* pBox = (ColliBox*)pColliPart;
                            ColliBox* pOtherBox = (ColliBox*)pOtherColliPart;
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

                        } else if (pColliPart->_shape_kind == COLLI_SPHERE && pOtherColliPart->_shape_kind == COLLI_SPHERE) {
                            //球と球
                            ColliSphere* pSphere = (ColliSphere*)pColliPart;
                            ColliSphere* pOtherSphere = (ColliSphere*)pOtherColliPart;
                            //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
                            //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
                            //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
                            if (
                                (double)((pOtherActor->_X+pOtherSphere->_x) - (_pActor->_X+pSphere->_x)) * ((pOtherActor->_X+pOtherSphere->_x) - (_pActor->_X+pSphere->_x)) +
                                (double)((pOtherActor->_Y+pOtherSphere->_y) - (_pActor->_Y+pSphere->_y)) * ((pOtherActor->_Y+pOtherSphere->_y) - (_pActor->_Y+pSphere->_y)) +
                                (double)((pOtherActor->_Z+pOtherSphere->_z) - (_pActor->_Z+pSphere->_z)) * ((pOtherActor->_Z+pOtherSphere->_z) - (_pActor->_Z+pSphere->_z))
                                  <=
                                (double)(pOtherSphere->_r + pSphere->_r) * (pOtherSphere->_r + pSphere->_r)
                            ) {
                                return true;
                            }

                        } else if (pColliPart->_shape_kind == COLLI_AABB && pOtherColliPart->_shape_kind == COLLI_SPHERE) {
                            ColliBox* pBox = (ColliBox*)pColliPart;
                            ColliSphere* pOtherSphere = (ColliSphere*)pOtherColliPart;
                            int o_scx =  pOtherActor->_X+pOtherSphere->_cx;
                            int o_scy =  pOtherActor->_Y+pOtherSphere->_cy;
                            int o_scz =  pOtherActor->_Z+pOtherSphere->_cz;
                            int bx1 = _pActor->_X+pBox->_x1;
                            int bx2 = _pActor->_X+pBox->_x2;
                            int by1 = _pActor->_Y+pBox->_y1;
                            int by2 = _pActor->_Y+pBox->_y2;
                            int bz1 = _pActor->_Z+pBox->_z1;
                            int bz2 = _pActor->_Z+pBox->_z2;
//							_TRACE_("pOtherSphere->_r="<<pOtherSphere->_r);
//							_TRACE_("o_scx,o_scy,o_scz="<<o_scx<<","<<o_scy<<","<<o_scz);
//							_TRACE_("bx1,by1,bz1 - bx2,by2,bz2 ="<<bx1<<","<<by1<<","<<bz1<<" - "<<bx2<<","<<by2<<","<<bz2);
                            double square_length = 0; //球の中心とAABBの最短距離を二乗した値

                            if(o_scx < bx1) {
                                square_length += (double)(o_scx - bx1) * (o_scx - bx1);
                                //_TRACE_("1(o_scx < bx1) square_length="<<square_length);
                            }
                            if(o_scx > bx2) {
                                square_length += (double)(o_scx - bx2) * (o_scx - bx2);
                                //_TRACE_("2(o_scx > bx2) square_length="<<square_length);
                            }
                            if(o_scy < by1) {
                                square_length += (double)(o_scy - by1) * (o_scy - by1);
                                //_TRACE_("3(o_scy < by1) square_length="<<square_length);
                            }
                            if(o_scy > by2) {
                                square_length += (double)(o_scy - by2) * (o_scy - by2);
                                //_TRACE_("4(o_scy > by2) square_length="<<square_length);
                            }
                            if(o_scz < bz1) {
                                square_length += (double)(o_scz - bz1) * (o_scz - bz1);
                                //_TRACE_("5(o_scz < bz1) square_length="<<square_length);
                            }
                            if(o_scz > bz2) {
                                square_length += (double)(o_scz - bz2) * (o_scz - bz2);
                                //_TRACE_("6(o_scz > bz2) square_length="<<square_length);
                            }
                            //_TRACE_("square_length="<<square_length<<" pOtherSphere->_r * pOtherSphere->_r="<<((double)pOtherSphere->_r * pOtherSphere->_r));
                            //square_lengthが球の半径（の二乗）よりも短ければ衝突している
                            if (square_length <= (double)pOtherSphere->_r * pOtherSphere->_r) {
                                return true;
                            }
                        } else if (pColliPart->_shape_kind == COLLI_SPHERE && pOtherColliPart->_shape_kind == COLLI_AABB) {
                            ColliSphere* pSphere = (ColliSphere*)pColliPart;
                            ColliBox* pOtherBox = (ColliBox*)pOtherColliPart;
                            int scx =  _pActor->_X+pSphere->_cx;
                            int scy =  _pActor->_Y+pSphere->_cy;
                            int scz =  _pActor->_Z+pSphere->_cz;
                            int o_bx1 = pOtherActor->_X+pOtherBox->_x1;
                            int o_bx2 = pOtherActor->_X+pOtherBox->_x2;
                            int o_by1 = pOtherActor->_Y+pOtherBox->_y1;
                            int o_by2 = pOtherActor->_Y+pOtherBox->_y2;
                            int o_bz1 = pOtherActor->_Z+pOtherBox->_z1;
                            int o_bz2 = pOtherActor->_Z+pOtherBox->_z2;
                            double square_length = 0; //球の中心とAABBの最短距離を二乗した値

                            if(scx < o_bx1) {
                                square_length += (double)(scx - o_bx1) * (scx - o_bx1);
                            }
                            if(scx > o_bx2) {
                                square_length += (double)(scx - o_bx2) * (scx - o_bx2);
                            }
                            if(scy < o_by1) {
                                square_length += (double)(scy - o_by1) * (scy - o_by1);
                            }
                            if(scy > o_by2) {
                                square_length += (double)(scy - o_by2) * (scy - o_by2);
                            }
                            if(scz < o_bz1) {
                                square_length += (double)(scz - o_bz1) * (scz - o_bz1);
                            }
                            if(scz > o_bz2) {
                                square_length += (double)(scz - o_bz2) * (scz - o_bz2);
                            }
                            //square_lengthが球の半径（の二乗）よりも短ければ衝突している
                            if (square_length <= (double)pSphere->_r * pSphere->_r) {
                                return true;
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
