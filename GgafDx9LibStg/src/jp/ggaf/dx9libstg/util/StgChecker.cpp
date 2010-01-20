#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

int StgChecker::_num_check = 0;
LinearOctreeForActor* StgChecker::_pLinearOctree = NULL;
StgChecker::StgChecker(GgafDx9GeometricActor* prm_pActor) : GgafDx9Checker(prm_pActor) {
    _pHitAreaBoxs = NULL;
    _iStaminaPointOriginally = 1;//元来の耐久力
    _iScorePointOriginally = 0; //元来の得点
    _iStaminaPoint = 1; //耐久力
    _iScorePoint = 0; //得点
    _iAttackPoint = 0; //攻撃力
    _iDefensePoint = 0; //防御力
    if (StgChecker::_pLinearOctree == NULL) {
        StgChecker::_pLinearOctree  = ((DefaultUniverse*)(GgafGod::_pGod->_pUniverse))->_pLinearOctree;
    }
    _pElem = new LOFA_Elem(prm_pActor, 0);
}

void StgChecker::useHitAreaBoxNum(int n) {
    if (_pHitAreaBoxs == NULL) {
        _pHitAreaBoxs = NEW HitAreaBoxs(n);
    } else {
        throwGgafCriticalException("StgChecker::useHitAreaBoxNum HitAreaBoxsは既に new されています。");
    }
}

void StgChecker::setHitAreaBox(int prm_index,
                               int x1,
                               int y1,
                               int z1,
                               int x2,
                               int y2,
                               int z2,
                               bool rotX,
                               bool rotY,
                               bool rotZ) {
    if (_pHitAreaBoxs == NULL) {
        throwGgafCriticalException("StgChecker::setHitAreaBox まず useHitAreaBoxNum を実行して、要素数を宣言してください。");
    } else {
        _pHitAreaBoxs->setBox(prm_index, x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);
//
//        if (x1 < _X1) {
//            _X1 = x1;
//        }
//        if (y1 < _Y1) {
//            _Y1 = y1;
//        }
//        if (z1 < _Z1) {
//            _Z1 = z1;
//        }
//
//        if (x2 > _X2) {
//            _X2 = x2;
//        }
//        if (y2 > _Y2) {
//            _Y2 = y2;
//        }
//        if (z2 > _Z2) {
//            _Z2 = z2;
//        }

//        _pLinearOctree->registElem(_pElem, _pActor->_X + _X1,
//                                           _pActor->_Y + _Y1,
//                                           _pActor->_Z + _Z1,
//                                           _pActor->_X + _X2,
//                                           _pActor->_Y + _Y2,
//                                           _pActor->_Z + _Z2);
    }


}

void StgChecker::updateHitArea() {
    if (_pActor == NULL || _pHitAreaBoxs == NULL) {
        return;
    }

    if (_pActor->_can_bump_flg && _pActor->isActive() && _pActor->isOffscreen() == 0 ) {
        //_TRACE_("updateHitArea() _can_bump_flg && isActive() "<<_pActor->getName());
        int cx, cy, cz;
        s_ang s_RX, s_RY, s_RZ;
        HitAreaBoxs::Box* pHitArea;
        HitAreaBoxs::Box* pBase;
        _X1=_Y1=_Z1=_X2=_Y2=_Z2=0;
        for (int i = 0; i < _pHitAreaBoxs->_iAreaNum; i++) {
            pHitArea = &(_pHitAreaBoxs->_paHitArea[i]);
            pBase= &(_pHitAreaBoxs->_paBase[i]);

            if (pBase->rotX || pBase->rotY || pBase->rotZ) {
                //当たり判定領域軸回転
                if (i == 0) {
                    s_RX = _pActor->_RX / ANGLE_RATE;
                    s_RY = _pActor->_RY / ANGLE_RATE;
                    s_RZ = _pActor->_RZ / ANGLE_RATE;
                }

                cx = pBase->cx;
                cy = pBase->cy;
                cz = pBase->cz;

                if (pBase->rotX) {
                    pHitArea->cy = (cy * GgafDx9Util::COS[s_RX]) - (cz * GgafDx9Util::SIN[s_RX]);
                    pHitArea->cz = (cy * GgafDx9Util::SIN[s_RX]) + (cz * GgafDx9Util::COS[s_RX]);
                    cy = pHitArea->cy;
                    cz = pHitArea->cz;
                }

                if (pBase->rotY) {
                    pHitArea->cz = (cz * GgafDx9Util::COS[s_RY]) - (cx * GgafDx9Util::SIN[s_RY]);
                    pHitArea->cx = (cz * GgafDx9Util::SIN[s_RY]) + (cx * GgafDx9Util::COS[s_RY]);
                    cz = pHitArea->cz;
                    cx = pHitArea->cx;
                }

                if (pBase->rotZ) {
                    pHitArea->cx = (cx * GgafDx9Util::COS[s_RZ]) - (cy * GgafDx9Util::SIN[s_RZ]);
                    pHitArea->cy = (cx * GgafDx9Util::SIN[s_RZ]) + (cy * GgafDx9Util::COS[s_RZ]);
                    cx = pHitArea->cx;
                    cy = pHitArea->cy;
                }

                pHitArea->x1 = cx - pBase->hdx;
                pHitArea->y1 = cy - pBase->hdy;
                pHitArea->z1 = cz - pBase->hdz;
                pHitArea->x2 = cx + pBase->hdx;
                pHitArea->y2 = cy + pBase->hdy;
                pHitArea->z2 = cz + pBase->hdz;
            }

            if (pHitArea->x1 < _X1) {
                _X1 = pHitArea->x1;
            }
            if (pHitArea->y1 < _Y1) {
                _Y1 = pHitArea->y1;
            }
            if (pHitArea->z1 < _Z1) {
                _Z1 = pHitArea->z1;
            }

            if (pHitArea->x2 > _X2) {
                _X2 = pHitArea->x2;
            }
            if (pHitArea->y2 > _Y2) {
                _Y2 = pHitArea->y2;
            }
            if (pHitArea->z2 > _Z2) {
                _Z2 = pHitArea->z2;
            }

        }

        _pElem->_kindbit = _pActor->getGroupActor()->_kind;
        _pLinearOctree->registElem(_pElem, _pActor->_X + _X1,
                                           _pActor->_Y + _Y1,
                                           _pActor->_Z + _Z1,
                                           _pActor->_X + _X2,
                                           _pActor->_Y + _Y2,
                                           _pActor->_Z + _Z2);

#ifdef MY_DEBUG
        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
            _TRACE_("  StgChecker::updateHitArea()  registElem("<<(_pActor->getName())<<")=("<<
                                             (_pActor->_X + _X1)<<","<<
                                             (_pActor->_Y + _Y1)<<","<<
                                             (_pActor->_Z + _Z1)<<","<<
                                             (_pActor->_X + _X2)<<","<<
                                             (_pActor->_Y + _Y2)<<","<<
                                             (_pActor->_Z + _Z2)<<")");
            _pLinearOctree->putTree();

        }
#endif

    } else {
        //毎回クリアするのでいらないはずだ
        //_pElem->extract();
    }

}
//
//bool StgChecker::isBump(GgafDx9Checker* prm_pOtherChecker) {
//
//    static GgafDx9GeometricActor* pOtherActor;
//    static HitAreaBoxs* pOtherHitAreaBoxs;
//
//    pOtherActor = prm_pOtherChecker->getTargetActor();
//    pOtherHitAreaBoxs = ((StgChecker*)prm_pOtherChecker)->getHitAreaBoxs();
//    if (_pActor == NULL || pOtherActor == NULL || _pHitAreaBoxs == NULL || pOtherHitAreaBoxs == NULL ||
//        _pActor->isOffscreen() > 0 || pOtherActor->isOffscreen() > 0 ||
//        _pHitAreaBoxs->_paHitArea->active == false || pOtherHitAreaBoxs->_paHitArea->active == false) {
//        return false;
//    } else {
//
//        //自分の箱と相手の箱
//
//        for (int i = 0; i < _pHitAreaBoxs->_iAreaNum; i++) {
//            for (int j = 0; j < pOtherHitAreaBoxs->_iAreaNum; j++) {
//                StgChecker::_num_check++;
//                if (_pActor->_Z + pHitArea->z2 >= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[j].z1) {
//                    if (_pActor->_Z + pHitArea->z1 <= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[j].z2) {
//                        if (_pActor->_X + pHitArea->x2 >= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[j].x1) {
//                            if (_pActor->_X + pHitArea->x1 <= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[j].x2) {
//                                if (_pActor->_Y + pHitArea->y2 >= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[j].y1) {
//                                    if (_pActor->_Y + pHitArea->y1 <= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[j].y2) {
//                                        return true;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//
//            }
//        }
//    }
//    return false;
//}

StgChecker::~StgChecker() {
    TRACE("StgChecker::~StgChecker() _pActor="<<_pActor->getName());
    DELETE_IMPOSSIBLE_NULL(_pElem);
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
    DELETE_POSSIBLE_NULL(_pHitAreaBoxs);
}
