#ifndef STGUTIL_H_
#define STGUTIL_H_
namespace GgafDx9LibStg {

class StgUtil: public GgafDx9Core::GgafDx9Util {
public:

//    /**
//     * AAB 対 AAB のヒットチェックを行う .
//     * @param pActor
//     * @param pAAB
//     * @param pOppActor
//     * @param pOppAAB
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);
//
//    /**
//     *  球 対 球 のヒットチェックを行う .
//     * @param pActor
//     * @param pSphere
//     * @param pOppActor
//     * @param pOppSphere
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);
//
//    /**
//     * AAB 対 球 のヒットチェックを行う .
//     * @param pActor
//     * @param pAAB
//     * @param pOppActor
//     * @param pOppSphere
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);
//
//    /**
//     * プリズム 対 AAB のヒットチェックを行う .
//     * @param pActor
//     * @param pAAPrism
//     * @param pOppActor
//     * @param pOppAAB
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);
//
//    /**
//     * プリズム 対 球 のヒットチェックを行う .
//     * @param pActor
//     * @param pAAPrism
//     * @param pOppActor
//     * @param pOppSphere
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere*  pOppSphere);



    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB) {
        //＜AAB と AAB＞
        //軸が一致しない確率が高そうな順番(Z>Y>X)に判定
        if (pActor->_Z + pAAB->_z2 >= pOppActor->_Z + pOppAAB->_z1) {
            if (pActor->_Z + pAAB->_z1 <= pOppActor->_Z + pOppAAB->_z2) {
                if (pActor->_Y + pAAB->_y2 >= pOppActor->_Y + pOppAAB->_y1) {
                    if (pActor->_Y + pAAB->_y1 <= pOppActor->_Y + pOppAAB->_y2) {
                        if (pActor->_X + pAAB->_x2 >= pOppActor->_X + pOppAAB->_x1) {
                            if (pActor->_X + pAAB->_x1 <= pOppActor->_X + pOppAAB->_x2) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
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

    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
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


    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB) {
        //＜プリズム と AAB＞
        int aX1 = pActor->_X + pAAPrism->_x1;
        int aY1 = pActor->_Y + pAAPrism->_y1;
        int aZ1 = pActor->_Z + pAAPrism->_z1;
        int aX2 = pActor->_X + pAAPrism->_x2;
        int aY2 = pActor->_Y + pAAPrism->_y2;
        int aZ2 = pActor->_Z + pAAPrism->_z2;

        int bX1 = pOppActor->_X + pOppAAB->_x1;
        int bY1 = pOppActor->_Y + pOppAAB->_y1;
        int bZ1 = pOppActor->_Z + pOppAAB->_z1;
        int bX2 = pOppActor->_X + pOppAAB->_x2;
        int bY2 = pOppActor->_Y + pOppAAB->_y2;
        int bZ2 = pOppActor->_Z + pOppAAB->_z2;

        if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
            //この時点でAAB と AAB ならばヒット
            int pos = pAAPrism->_pos_prism;
            double a = pAAPrism->_a;
            if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = y - ax
                double b = ((pActor->_Y+pAAPrism->_cy) - pAAPrism->_a * (pActor->_X+pAAPrism->_cx)) + pAAPrism->_b;

                if (pos & POS_PRISM_pp) {
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

                } else if (pos & POS_PRISM_np) {
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

                } else if (pos & POS_PRISM_pn) {
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
                    if (bY1 < a * bX2 +  b) {
                        return true;
                    }

                } else { // のこりは POS_PRISM_nn のみである
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


                }
            } else if (pos & POS_PRISM_YZ) {//YZ平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = z - ay
                int b = ((pActor->_Z+pAAPrism->_cz) - pAAPrism->_a * (pActor->_Y+pAAPrism->_cy)) + pAAPrism->_b;
                if (pos & POS_PRISM_pp) {
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

                } else if (pos & POS_PRISM_np) {
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

                } else if (pos & POS_PRISM_pn) {
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
                    if (bZ1 < a * bY2 +  b) {
                        return true;
                    }

                } else { //のこりは POS_PRISM_nn のみである
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
                }

            } else if (pos & POS_PRISM_ZX) {
                //ワールド座標でのプリズム境界線の切片を求める b = x - az
                int b = ((pActor->_X+pAAPrism->_cx) - pAAPrism->_a * (pActor->_Z+pAAPrism->_cz)) + pAAPrism->_b;
                if (pos & POS_PRISM_pp) {
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

                } else if (pos & POS_PRISM_np) {
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

                } else if (pos & POS_PRISM_pn) {
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
                    if (bX1 < a * bZ2 +  b) {
                        return true;
                    }

                } else { //残りは POS_PRISM_nn のみである
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
                }
            }
        }
        return false;
    }



    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere*  pOppSphere) {
        //＜プリズム と 球＞
        int aX1 = pActor->_X + pAAPrism->_x1;
        int aY1 = pActor->_Y + pAAPrism->_y1;
        int aZ1 = pActor->_Z + pAAPrism->_z1;
        int aX2 = pActor->_X + pAAPrism->_x2;
        int aY2 = pActor->_Y + pAAPrism->_y2;
        int aZ2 = pActor->_Z + pAAPrism->_z2;

        //AAB 対 球でまず判定する
        if (isHit(pActor, (ColliAAB*)pAAPrism, pOppActor, pOppSphere)) {
            //この時点でAAB 対 球でヒット。ここからプリズムでもヒットか検証する
            int pos = pAAPrism->_pos_prism;
            double a = pAAPrism->_a;
            if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = y - ax
                double b = ((pActor->_Y+pAAPrism->_cy) - pAAPrism->_a * (pActor->_X+pAAPrism->_cx)) + pAAPrism->_b;

                int oppX, oppY;
                int bZc = pOppActor->_Z + pOppSphere->_cz; //球の中心Z座標
                if (aZ1 < bZc && bZc < aZ2) {
                    //球の中心Z座標がプリズムのZ幅範囲内ならば、予め保持している_vIH_x,_vIH_yを使用して
                    //プリズム斜辺と最短距離の円周上のXY座標を求める
                    oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_x * pOppSphere->_r;
                    oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_y * pOppSphere->_r;
                } else {
                    if (bZc >= aZ2) {
                        //球の中心Z座標がプリズムのZ幅範囲外の場合
                        //離れる距離に応じて、球側の半径(pOppSphere->_r)を小さくして差分を計算
                        //小さくする割合は ROOT_1_MINUS_XX (1/4円の解の配列）を使用。
                        //                 |
                        //                 ＼
                        //        ┌───┐ `─
                        // z- ←  │      │  → z+
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pOppSphere->_r)*1000)];
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_x * r;
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_y * r;
                    } else if (aZ1 >= bZc) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pOppSphere->_r)*1000)];
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_x * r;
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_y * r;
                    }
                }

                if (pos & POS_PRISM_pp) {
                    //            ↑ y+
                    //
                    //        ┌───┐
                    //        │＼こち│
                    // x- ←  │　＼ら│  → x+
                    //       ,┼○　＼│
                    //      │└┼──┘
                    //       `─'
                    //            ↓ y-
                    //
                    //プリズム境界線 y = ax + b と
                    //○の座標(bX2, bY2)、との位置関係を考える
                    //y > ax + b であればヒット
                    if (oppY > a * oppX +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            ↑ y+
                    //
                    //        ┌───┐
                    //        │こち／│
                    // x- ←  │ら／　│  → x+
                    //        │／　○┼、
                    //        └──┼┘│Opp
                    //               `─'
                    //            ↓ y-
                    //
                    //プリズム境界線 y = ax + b と
                    //○の座標(bX1, bY2)、との位置関係を考える
                    //y > ax + b であればヒット
                    if (oppY > a * oppX +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            ↑ y+
                    //       ,─、
                    //      │┌┼──┐
                    //       `┼○　／│
                    // x- ←  │　／こ│  → x+
                    //        │／ちら│
                    //        └───┘
                    //
                    //            ↓ y-
                    //
                    //プリズム境界線 y = ax + b と
                    //○の座標(bX2, bY1)、との位置関係を考える
                    //y < ax + b であればヒット
                    if (oppY < a * oppX +  b) {
                        return true;
                    }

                } else { // のこりは POS_PRISM_nn のみである
                    //            ↑ y+
                    //               ,─、
                    //        ┌──┼┐│Opp
                    //        │＼　○┼'
                    // x- ←  │こ＼　│  → x+
                    //        │ちら＼│
                    //        └───┘
                    //
                    //            ↓ y-
                    //
                    //プリズム境界線 y = ax + b と
                    //○の座標(bX1, bY1)、との位置関係を考える
                    //y < ax + b であればヒット
                    if (oppY < a * oppX +  b) {
                        return true;
                    }


                }
            } else if (pos & POS_PRISM_YZ) {//YZ平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = z - ay
                int b = ((pActor->_Z+pAAPrism->_cz) - pAAPrism->_a * (pActor->_Y+pAAPrism->_cy)) + pAAPrism->_b;
                int oppY, oppZ;

                int bXc = pOppActor->_X + pOppSphere->_cx;
                if (aX1 < bXc && bXc < aX2) {
                    oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_x * pOppSphere->_r;
                    oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_y * pOppSphere->_r;
                } else {
                    if (bXc >= aX2) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pOppSphere->_r)*1000)];
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_x * r;
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_y * r;
                    } else if (aX1 >= bXc) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pOppSphere->_r)*1000)];
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_x * r;
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_y * r;
                    }
                }
                if (pos & POS_PRISM_pp) {
                    //            ↑ z+
                    //
                    //        ┌───┐
                    //        │＼こち│
                    // y- ←  │　＼ら│  → y+
                    //       ,┼○　＼│
                    //      │└┼──┘
                    //       `─'
                    //            ↓ z-
                    //
                    //プリズム境界線 z = ay + b と
                    //○の座標(bY2, bZ2)、との位置関係を考える
                    //z > ay + b であればヒット
                    if (oppZ > a * oppY +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            ↑ z+
                    //
                    //        ┌───┐
                    //        │こち／│
                    // y- ←  │ら／　│  → y+
                    //        │／　○┼、
                    //        └──┼┘│Opp
                    //               `─'
                    //            ↓ z-
                    //
                    //プリズム境界線 z = ay + b と
                    //○の座標(bY1, bZ2)、との位置関係を考える
                    //z > ay + b であればヒット
                    if (oppZ > a * oppY +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            ↑ z+
                    //       ,─、
                    //      │┌┼──┐
                    //       `┼○　／│
                    // y- ←  │　／こ│  → y+
                    //        │／ちら│
                    //        └───┘
                    //
                    //            ↓ z-
                    //
                    //プリズム境界線 z = ay + b と
                    //○の座標(bY2, bZ1)、との位置関係を考える
                    //z < ay + b であればヒット
                    if (oppZ < a * oppY +  b) {
                        return true;
                    }

                } else { //のこりは POS_PRISM_nn のみである
                    //            ↑ z+
                    //               ,─、
                    //        ┌──┼┐│Opp
                    //        │＼　○┼'
                    // y- ←  │こ＼　│  → y+
                    //        │ちら＼│
                    //        └───┘
                    //
                    //            ↓ z-
                    //
                    //プリズム境界線 z = ay + b と
                    //○の座標(bY1, bZ1)、との位置関係を考える
                    //z < ay + b であればヒット
                    if (oppZ < a * oppY +  b) {
                        return true;
                    }
                }

            } else if (pos & POS_PRISM_ZX) {
                //ワールド座標でのプリズム境界線の切片を求める b = x - az
                int b = ((pActor->_X+pAAPrism->_cx) - pAAPrism->_a * (pActor->_Z+pAAPrism->_cz)) + pAAPrism->_b;
                int oppZ,oppX;
                int bYc = pOppActor->_Y + pOppSphere->_cy;
                if (aY1 < bYc && bYc < aY2) {
                    oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_x * pOppSphere->_r;
                    oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_y * pOppSphere->_r;
                } else {
                    if (bYc >= aY2) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pOppSphere->_r)*1000)];
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_x * r;
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_y * r;
                    } else if (aY1 >= bYc) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pOppSphere->_r)*1000)];
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_x * r;
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_y * r;
                    }
                }
                if (pos & POS_PRISM_pp) {
                    //            ↑ x+
                    //
                    //        ┌───┐
                    //        │＼こち│
                    // z- ←  │　＼ら│  → z+
                    //       ,┼○　＼│
                    //      │└┼──┘
                    //       `─'
                    //            ↓ x-
                    //
                    //プリズム境界線 x = az + b と
                    //○の座標(bZ2, bX2)、との位置関係を考える
                    //x > az + b であればヒット
                    if (oppX > a * oppZ +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            ↑ x+
                    //
                    //        ┌───┐
                    //        │こち／│
                    // z- ←  │ら／　│  → z+
                    //        │／　○┼、
                    //        └──┼┘│Opp
                    //               `─'
                    //            ↓ x-
                    //
                    //プリズム境界線 x = az + b と
                    //○の座標(bZ1, bX2)、との位置関係を考える
                    //x > az + b であればヒット
                    if (oppX > a * oppZ +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            ↑ x+
                    //       ,─、
                    //      │┌┼──┐
                    //       `┼○　／│
                    // z- ←  │　／こ│  → z+
                    //        │／ちら│
                    //        └───┘
                    //
                    //            ↓ x-
                    //
                    //プリズム境界線 x = az + b と
                    //○の座標(bZ2, bX1)、との位置関係を考える
                    //x < az + b であればヒット
                    if (oppX < a * oppZ +  b) {
                        return true;
                    }

                } else { //残りは POS_PRISM_nn のみである
                    //            ↑ x+
                    //               ,─、
                    //        ┌──┼┐│Opp
                    //        │＼　○┼'
                    // z- ←  │こ＼　│  → z+
                    //        │ちら＼│
                    //        └───┘
                    //
                    //            ↓ x-
                    //
                    //プリズム境界線 x = az + b と
                    //○の座標(bZ1, bX1)、との位置関係を考える
                    //x < az + b であればヒット
                    if (oppX < a * oppZ +  b) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    /**
     * Rz変化による nWay弾を撃つ .
     * @param prm_pFrom 発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget 目標
     * @param prm_way Way数
     * @param prm_angClearance Wayの間隔
     * @param prm_velo 初期速度
     * @param prm_acce 加速度
     */
    static void shotWay001(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo, acce prm_acce);
    /**
     * Rz変化による nWay弾を複数セット同時に撃つ .
     * @param prm_pFrom        発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget      目標
     * @param prm_way          Way数
     * @param prm_angClearance Wayの間隔
     * @param prm_velo_top     初弾WAYの初期速度
     * @param prm_acce_top     初弾WAYの加速度
     * @param prm_num          撃つWAY弾のセット数
     * @param prm_attenuated   次のWAY弾の初期速度加速度の減衰率
     */
    static void shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angClearance,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);


    /**
     * Ry は目標への向き＋ANGLE90で、Rz変化による nWay放射弾を打つ .
     * @param prm_pFrom 発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget 目標
     * @param prm_way 放射Way数
     * @param prm_angBegin 放射開始アングル
     * @param prm_velo 初期速度
     * @param prm_acce 加速度
     */
    static void shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo, acce prm_acce);

    /**
     * shotWay002弾を複数セット同時に撃つ .
     * @param prm_pFrom 発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget 目標
     * @param prm_way 放射Way数
     * @param prm_angBegin 放射開始アングル
     * @param prm_velo_top 初弾放射WAYの初期速度
     * @param prm_acce_top 初弾放射WAYの加速度
     * @param prm_num      撃つ放射WAY弾のセット数
     * @param prm_attenuated 次のWAY弾の初期速度加速度の減衰率
     */
    static void shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angBegin,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);

};

}
#endif /*STGUTIL_H_*/
