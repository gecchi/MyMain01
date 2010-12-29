#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
                       GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppABB) {
    //＜AAB と AAB＞
    //軸が一致しない確率が高そうな順番(Z>Y>X)に判定
    if (pActor->_Z + pAAB->_z2 >= pOppActor->_Z + pOppABB->_z1) {
        if (pActor->_Z + pAAB->_z1 <= pOppActor->_Z + pOppABB->_z2) {
            if (pActor->_Y + pAAB->_y2 >= pOppActor->_Y + pOppABB->_y1) {
                if (pActor->_Y + pAAB->_y1 <= pOppActor->_Y + pOppABB->_y2) {
                    if (pActor->_X + pAAB->_x2 >= pOppActor->_X + pOppABB->_x1) {
                        if (pActor->_X + pAAB->_x1 <= pOppActor->_X + pOppABB->_x2) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
                       GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere) {
    //＜球 と 球＞
    //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
    //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
    if (
        (double)((pOppActor->_X+pOppSphere->_x) - (pActor->_X+pSphere->_x)) * ((pOppActor->_X+pOppSphere->_x) - (pActor->_X+pSphere->_x)) +
        (double)((pOppActor->_Y+pOppSphere->_y) - (pActor->_Y+pSphere->_y)) * ((pOppActor->_Y+pOppSphere->_y) - (pActor->_Y+pSphere->_y)) +
        (double)((pOppActor->_Z+pOppSphere->_z) - (pActor->_Z+pSphere->_z)) * ((pOppActor->_Z+pOppSphere->_z) - (pActor->_Z+pSphere->_z))
          <=
        (double)(pOppSphere->_r + pSphere->_r) * (pOppSphere->_r + pSphere->_r)
    ) {
        return true;
    } else {
        return false;
    }
}

boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
                       GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere) {
    //＜AAB と 球＞
    int o_scx =  pOppActor->_X+pOppSphere->_cx;
    int o_scy =  pOppActor->_Y+pOppSphere->_cy;
    int o_scz =  pOppActor->_Z+pOppSphere->_cz;
    int bx1 = pActor->_X+pAAB->_x1;
    int bx2 = pActor->_X+pAAB->_x2;
    int by1 = pActor->_Y+pAAB->_y1;
    int by2 = pActor->_Y+pAAB->_y2;
    int bz1 = pActor->_Z+pAAB->_z1;
    int bz2 = pActor->_Z+pAAB->_z2;
    double square_length = 0; //球の中心とAABの最短距離を二乗した値
    if(o_scx < bx1) {
        square_length += (double)(o_scx - bx1) * (o_scx - bx1);
    }
    if(o_scx > bx2) {
        square_length += (double)(o_scx - bx2) * (o_scx - bx2);
    }
    if(o_scy < by1) {
        square_length += (double)(o_scy - by1) * (o_scy - by1);
    }
    if(o_scy > by2) {
        square_length += (double)(o_scy - by2) * (o_scy - by2);
    }
    if(o_scz < bz1) {
        square_length += (double)(o_scz - bz1) * (o_scz - bz1);
    }
    if(o_scz > bz2) {
        square_length += (double)(o_scz - bz2) * (o_scz - bz2);
    }
    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length <= (double)pOppSphere->_r * pOppSphere->_r) {
        return true;
    } else {
        return false;
    }
}


boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                       GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppABB) {
    //＜プリズム と AAB＞
    int aX1 = pActor->_X + pAAPrism->_x1;
    int aY1 = pActor->_Y + pAAPrism->_y1;
    int aZ1 = pActor->_Z + pAAPrism->_z1;
    int aX2 = pActor->_X + pAAPrism->_x2;
    int aY2 = pActor->_Y + pAAPrism->_y2;
    int aZ2 = pActor->_Z + pAAPrism->_z2;

    int bX1 = pOppActor->_X + pOppABB->_x1;
    int bY1 = pOppActor->_Y + pOppABB->_y1;
    int bZ1 = pOppActor->_Z + pOppABB->_z1;
    int bX2 = pOppActor->_X + pOppABB->_x2;
    int bY2 = pOppActor->_Y + pOppABB->_y2;
    int bZ2 = pOppActor->_Z + pOppABB->_z2;



    if (aZ2 >= bZ1) {
        if (aZ1 <= bZ2) {
            if (aY2 >= bY1) {
                if (aY1 <= bY2) {
                    if (aX2 >= bX1) {
                        if (aX1 <= bX2) {
                            //この時点でAAB と AAB ならばヒット
                            int pos = pAAPrism->_pos_prism;
                            int a = pAAPrism->_a;
                            if (pos & PRISM_XY) { //XY平面スライスのプリズム
                                int b = pAAPrism->_b + pActor->_Y; //プリズム境界線の切片は縦方向成分を加えておけば良い
                                if (pos & PRISM_nn) {
                                    //            ↑ y+
                                    //              ┌─┐
                                    //        ┌──┼┐│Opp
                                    //        │＼　○┼┘
                                    // x- ←  │こ＼　│  → x+
                                    //        │ちら＼│
                                    //        └───┘
                                    //
                                    //            ↓ y-
                                    //
                                    //プリズム境界線 y = ax + b と
                                    //○の座標(bX1, bY1)、との位置関係を考える
                                    //y < ax + b であればヒット
                                    if (bY1 < a * bX1 +  b) {
                                        return true;
                                    }


                                } else if (pos & PRISM_np) {
                                    //            ↑ y+
                                    //
                                    //        ┌───┐
                                    //        │こち／│
                                    // x- ←  │ら／　│  → x+
                                    //        │／　○┼┐
                                    //        └──┼┘│Opp
                                    //              └─┘
                                    //            ↓ y-
                                    //
                                    //プリズム境界線 y = ax + b と
                                    //○の座標(bX1, bY2)、との位置関係を考える
                                    //y > ax + b であればヒット
                                    if (bY2 > a * bX1 +  b) {
                                        return true;
                                    }

                                } else if (pos & PRISM_pn) {
                                    //            ↑ y+
                                    //      ┌─┐
                                    //      │┌┼──┐
                                    //      └┼○　／│
                                    // x- ←  │　／こ│  → x+
                                    //        │／ちら│
                                    //        └───┘
                                    //
                                    //            ↓ y-
                                    //
                                    //プリズム境界線 y = ax + b と
                                    //○の座標(bX2, bY1)、との位置関係を考える
                                    //y < ax + b であればヒット
                                    if (bY1 > a * bX2 +  b) {
                                        return true;
                                    }

                                } else if (pos & PRISM_pp) {
                                    //            ↑ y+
                                    //
                                    //        ┌───┐
                                    //        │＼こち│
                                    // x- ←  │　＼ら│  → x+
                                    //      ┌┼○　＼│
                                    //      │└┼──┘
                                    //      └─┘
                                    //            ↓ y-
                                    //
                                    //プリズム境界線 y = ax + b と
                                    //○の座標(bX2, bY2)、との位置関係を考える
                                    //y > ax + b であればヒット
                                    if (bY2 > a * bX2 +  b) {
                                        return true;
                                    }

                                }
                            } else if (pos & PRISM_YZ) {//YZ平面スライスのプリズム

                                int b = pAAPrism->_b + pActor->_Z; //プリズム境界線の切片は縦方向成分を加えておけば良い
                                if (pos & PRISM_nn) {
                                    //            ↑ z+
                                    //              ┌─┐
                                    //        ┌──┼┐│Opp
                                    //        │＼　○┼┘
                                    // y- ←  │こ＼　│  → y+
                                    //        │ちら＼│
                                    //        └───┘
                                    //
                                    //            ↓ z-
                                    //
                                    //プリズム境界線 z = ay + b と
                                    //○の座標(bY1, bZ1)、との位置関係を考える
                                    //z < ay + b であればヒット
                                    if (bZ1 < a * bY1 +  b) {
                                        return true;
                                    }


                                } else if (pos & PRISM_np) {
                                    //            ↑ z+
                                    //
                                    //        ┌───┐
                                    //        │こち／│
                                    // y- ←  │ら／　│  → y+
                                    //        │／　○┼┐
                                    //        └──┼┘│Opp
                                    //              └─┘
                                    //            ↓ z-
                                    //
                                    //プリズム境界線 z = ay + b と
                                    //○の座標(bY1, bZ2)、との位置関係を考える
                                    //z > ay + b であればヒット
                                    if (bZ2 > a * bY1 +  b) {
                                        return true;
                                    }

                                } else if (pos & PRISM_pn) {
                                    //            ↑ z+
                                    //      ┌─┐
                                    //      │┌┼──┐
                                    //      └┼○　／│
                                    // y- ←  │　／こ│  → y+
                                    //        │／ちら│
                                    //        └───┘
                                    //
                                    //            ↓ z-
                                    //
                                    //プリズム境界線 z = ay + b と
                                    //○の座標(bY2, bZ1)、との位置関係を考える
                                    //z < ay + b であればヒット
                                    if (bZ1 > a * bY2 +  b) {
                                        return true;
                                    }

                                } else if (pos & PRISM_pp) {
                                    //            ↑ z+
                                    //
                                    //        ┌───┐
                                    //        │＼こち│
                                    // y- ←  │　＼ら│  → y+
                                    //      ┌┼○　＼│
                                    //      │└┼──┘
                                    //      └─┘
                                    //            ↓ z-
                                    //
                                    //プリズム境界線 z = ay + b と
                                    //○の座標(bY2, bZ2)、との位置関係を考える
                                    //z > ay + b であればヒット
                                    if (bZ2 > a * bY2 +  b) {
                                        return true;
                                    }

                                }

                            } else if (pos & PRISM_ZX) {
                                int b = pAAPrism->_b + pActor->_X; //プリズム境界線の切片は縦方向成分を加えておけば良い
                                if (pos & PRISM_nn) {
                                    //            ↑ x+
                                    //              ┌─┐
                                    //        ┌──┼┐│Opp
                                    //        │＼　○┼┘
                                    // z- ←  │こ＼　│  → z+
                                    //        │ちら＼│
                                    //        └───┘
                                    //
                                    //            ↓ x-
                                    //
                                    //プリズム境界線 x = az + b と
                                    //○の座標(bZ1, bX1)、との位置関係を考える
                                    //x < az + b であればヒット
                                    if (bX1 < a * bZ1 +  b) {
                                        return true;
                                    }


                                } else if (pos & PRISM_np) {
                                    //            ↑ x+
                                    //
                                    //        ┌───┐
                                    //        │こち／│
                                    // z- ←  │ら／　│  → z+
                                    //        │／　○┼┐
                                    //        └──┼┘│Opp
                                    //              └─┘
                                    //            ↓ x-
                                    //
                                    //プリズム境界線 x = az + b と
                                    //○の座標(bZ1, bX2)、との位置関係を考える
                                    //x > az + b であればヒット
                                    if (bX2 > a * bZ1 +  b) {
                                        return true;
                                    }

                                } else if (pos & PRISM_pn) {
                                    //            ↑ x+
                                    //      ┌─┐
                                    //      │┌┼──┐
                                    //      └┼○　／│
                                    // z- ←  │　／こ│  → z+
                                    //        │／ちら│
                                    //        └───┘
                                    //
                                    //            ↓ x-
                                    //
                                    //プリズム境界線 x = az + b と
                                    //○の座標(bZ2, bX1)、との位置関係を考える
                                    //x < az + b であればヒット
                                    if (bX1 > a * bZ2 +  b) {
                                        return true;
                                    }

                                } else if (pos & PRISM_pp) {
                                    //            ↑ x+
                                    //
                                    //        ┌───┐
                                    //        │＼こち│
                                    // z- ←  │　＼ら│  → z+
                                    //      ┌┼○　＼│
                                    //      │└┼──┘
                                    //      └─┘
                                    //            ↓ x-
                                    //
                                    //プリズム境界線 x = az + b と
                                    //○の座標(bZ2, bX2)、との位置関係を考える
                                    //x > az + b であればヒット
                                    if (bX2 > a * bZ2 +  b) {
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
    return false;
}

void StgUtil::shotWay001(GgafDx9GeometricActor* prm_pFrom,
                       GgafActorDispatcher* prm_pDispatcher_Shot,
                       GgafDx9GeometricActor* prm_pTarget,
                       int prm_way, angle prm_angClearance,
                       velo prm_velo, acce prm_acce) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getWayAngle2D(0,prm_way, prm_angClearance, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
        if (pActor_Shot) {
            pActor_Shot->setCoordinateBy(prm_pFrom);
            pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry);
            pActor_Shot->_pMover->setMvVelo(prm_velo);
            pActor_Shot->_pMover->setMvAcce(prm_acce);
            pActor_Shot->activate();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*     prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo_top, acce prm_acce_top,
                           int prm_num, float prm_attenuated) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getWayAngle2D(0,prm_way, prm_angClearance, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    velo now_velo = prm_velo_top;
    acce now_acce = prm_acce_top;
    for (int n = 0; n < prm_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
            if (pActor_Shot) {
                pActor_Shot->setCoordinateBy(prm_pFrom);
                pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry);
                pActor_Shot->_pMover->setMvVelo(now_velo);
                pActor_Shot->_pMover->setMvAcce(now_acce);
                pActor_Shot->activate();
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                        GgafCore::GgafActorDispatcher*     prm_pDispatcher_Shot,
                        GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                        int prm_way, angle prm_angBegin,
                        velo prm_velo, acce prm_acce) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getRadialAngle2D(prm_angBegin, prm_way, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
        if (pActor_Shot) {
            pActor_Shot->setCoordinateBy(prm_pFrom);
            pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry+ANGLE90);
            pActor_Shot->_pMover->setMvVelo(prm_velo);
            pActor_Shot->_pMover->setMvAcce(prm_acce);
            pActor_Shot->activate();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
void StgUtil::shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*     prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo_top, acce prm_acce_top,
                           int prm_num, float prm_attenuated) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getRadialAngle2D(prm_angBegin, prm_way, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    velo now_velo = prm_velo_top;
    acce now_acce = prm_acce_top;
    for (int n = 0; n < prm_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
            if (pActor_Shot) {
                pActor_Shot->setCoordinateBy(prm_pFrom);
                pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry+ANGLE90);
                pActor_Shot->_pMover->setMvVelo(now_velo);
                pActor_Shot->_pMover->setMvAcce(now_acce);
                pActor_Shot->activate();
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
