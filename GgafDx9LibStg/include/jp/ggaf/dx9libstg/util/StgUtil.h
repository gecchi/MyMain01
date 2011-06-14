#ifndef STGUTIL_H_
#define STGUTIL_H_
namespace GgafDx9LibStg {

class StgUtil: public GgafDx9Core::GgafDx9Util {
public:

    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAB* pAAB01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliAAB* pAAB02) {
        //＜AAB と AAB＞
        //軸が一致しない確率が高そうな順番(Z>Y>X)に判定
        if (pActor01->_Z + pAAB01->_z2 >= pActor02->_Z + pAAB02->_z1) {
            if (pActor01->_Z + pAAB01->_z1 <= pActor02->_Z + pAAB02->_z2) {
                if (pActor01->_Y + pAAB01->_y2 >= pActor02->_Y + pAAB02->_y1) {
                    if (pActor01->_Y + pAAB01->_y1 <= pActor02->_Y + pAAB02->_y2) {
                        if (pActor01->_X + pAAB01->_x2 >= pActor02->_X + pAAB02->_x1) {
                            if (pActor01->_X + pAAB01->_x1 <= pActor02->_X + pAAB02->_x2) {
//                                if (pCChecker01->_is_blown || pCChecker02->_is_blown) {
                                    //ヒットしている場合、
                                    //吹っ飛び方向を設定
                                    if (pActor01->_Z + pAAB01->_z1 < pActor02->_Z + pAAB02->_z1) {
                                        pCChecker01->_blown_sgn_vZ -= 1;
                                    }
                                    if (pActor01->_Z + pAAB01->_z2 > pActor02->_Z + pAAB02->_z2) {
                                        pCChecker01->_blown_sgn_vZ += 1;
                                    }
                                    if (pActor01->_Y + pAAB01->_y1 < pActor02->_Y + pAAB02->_y1) {
                                        pCChecker01->_blown_sgn_vY -= 1;
                                    }
                                    if (pActor01->_Y + pAAB01->_y2 > pActor02->_Y + pAAB02->_y2) {
                                        pCChecker01->_blown_sgn_vY += 1;
                                    }
                                    if (pActor01->_X + pAAB01->_x1 < pActor02->_X + pAAB02->_x1) {
                                        pCChecker01->_blown_sgn_vX -= 1;
                                    }
                                    if (pActor01->_X + pAAB01->_x2 > pActor02->_X + pAAB02->_x2) {
                                        pCChecker01->_blown_sgn_vX += 1;
                                    }
//                                }
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliSphere* pSphere01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliSphere* pSphere02) {
        //＜球 と 球＞
        //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
        //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
        //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
        double d2 = (double)((pActor02->_X+pSphere02->_x) - (pActor01->_X+pSphere01->_x)) * ((pActor02->_X+pSphere02->_x) - (pActor01->_X+pSphere01->_x)) +
                    (double)((pActor02->_Y+pSphere02->_y) - (pActor01->_Y+pSphere01->_y)) * ((pActor02->_Y+pSphere02->_y) - (pActor01->_Y+pSphere01->_y)) +
                    (double)((pActor02->_Z+pSphere02->_z) - (pActor01->_Z+pSphere01->_z)) * ((pActor02->_Z+pSphere02->_z) - (pActor01->_Z+pSphere01->_z));
        if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
        ) {
            //ヒット
            //todo:「球対球吹っ飛び簡易計算アイディア」
            //内接正８角形を考え互いの直径の平均をとり、その平均直径に真横面の割合を計算し掛ける範囲が垂直吹っ飛び
            if (pActor01->_Z + pSphere01->_aab_z1 < pActor02->_Z + pSphere02->_aab_z1) {
                pCChecker01->_blown_sgn_vZ -= 1;
            }
            if (pActor01->_Z + pSphere01->_aab_z2 > pActor02->_Z + pSphere02->_aab_z2) {
                pCChecker01->_blown_sgn_vZ += 1;
            }
            if (pActor01->_Y + pSphere01->_aab_y1 < pActor02->_Y + pSphere02->_aab_y1) {
                pCChecker01->_blown_sgn_vY -= 1;
            }
            if (pActor01->_Y + pSphere01->_aab_y2 > pActor02->_Y + pSphere02->_aab_y2) {
                pCChecker01->_blown_sgn_vY += 1;
            }
            if (pActor01->_X + pSphere01->_aab_x1 < pActor02->_X + pSphere02->_aab_x1) {
                pCChecker01->_blown_sgn_vX -= 1;
            }
            if (pActor01->_X + pSphere01->_aab_x2 > pActor02->_X + pSphere02->_aab_x2) {
                pCChecker01->_blown_sgn_vX += 1;
            }
            return true;
        } else {
            return false;
        }
    }

    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAB*    pAAB01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliSphere* pSphere02) {
        //＜AAB と 球＞
        int o_scx = pActor02->_X+pSphere02->_cx;
        int o_scy = pActor02->_Y+pSphere02->_cy;
        int o_scz = pActor02->_Z+pSphere02->_cz;
        int bx1 = pActor01->_X+pAAB01->_x1;
        int bx2 = pActor01->_X+pAAB01->_x2;
        int by1 = pActor01->_Y+pAAB01->_y1;
        int by2 = pActor01->_Y+pAAB01->_y2;
        int bz1 = pActor01->_Z+pAAB01->_z1;
        int bz2 = pActor01->_Z+pAAB01->_z2;
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
        if (square_length <= pSphere02->_rr) {
            //ヒット
            //吹っ飛方向を考慮
            if (pActor01->_Z + pAAB01->_aab_z1 < pActor02->_Z + pSphere02->_aab_z1) {
                pCChecker01->_blown_sgn_vZ -= 1;
            }
            if (pActor01->_Z + pAAB01->_aab_z2 > pActor02->_Z + pSphere02->_aab_z2) {
                pCChecker01->_blown_sgn_vZ += 1;
            }
            if (pActor01->_Y + pAAB01->_aab_y1 < pActor02->_Y + pSphere02->_aab_y1) {
                pCChecker01->_blown_sgn_vY -= 1;
            }
            if (pActor01->_Y + pAAB01->_aab_y2 > pActor02->_Y + pSphere02->_aab_y2) {
                pCChecker01->_blown_sgn_vY += 1;
            }
            if (pActor01->_X + pAAB01->_aab_x1 < pActor02->_X + pSphere02->_aab_x1) {
                pCChecker01->_blown_sgn_vX -= 1;
            }
            if (pActor01->_X + pAAB01->_aab_x2 > pActor02->_X + pSphere02->_aab_x2) {
                pCChecker01->_blown_sgn_vX += 1;
            }
            return true;
        } else {
            return false;
        }
    }


    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliAAB*     pAAB02) {
        //＜プリズム と AAB＞
        int aX1 = pActor01->_X + pAAPrism01->_x1;
        int aY1 = pActor01->_Y + pAAPrism01->_y1;
        int aZ1 = pActor01->_Z + pAAPrism01->_z1;
        int aX2 = pActor01->_X + pAAPrism01->_x2;
        int aY2 = pActor01->_Y + pAAPrism01->_y2;
        int aZ2 = pActor01->_Z + pAAPrism01->_z2;

        int bX1 = pActor02->_X + pAAB02->_x1;
        int bY1 = pActor02->_Y + pAAB02->_y1;
        int bZ1 = pActor02->_Z + pAAB02->_z1;
        int bX2 = pActor02->_X + pAAB02->_x2;
        int bY2 = pActor02->_Y + pAAB02->_y2;
        int bZ2 = pActor02->_Z + pAAB02->_z2;

        if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
            //この時点でAAB と AAB ならばヒット
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = y - ax
                double b = ((pActor01->_Y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_X+pAAPrism01->_cx)) + pAAPrism01->_b;

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
                        pCChecker01->_blown_sgn_vY += 1;
                        pCChecker01->_blown_sgn_vX += 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vY += 1;
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
                        pCChecker01->_blown_sgn_vX += 1;
                        pCChecker01->_blown_sgn_vY -= 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vY -= 1;
                        return true;
                    }


                }
            } else if (pos & POS_PRISM_YZ) {//YZ平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = z - ay
                int b = ((pActor01->_Z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_Y+pAAPrism01->_cy)) + pAAPrism01->_b;
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
                        pCChecker01->_blown_sgn_vY += 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vY -= 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vY += 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
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
                        pCChecker01->_blown_sgn_vY -= 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
                        return true;
                    }
                }

            } else if (pos & POS_PRISM_ZX) {
                //ワールド座標でのプリズム境界線の切片を求める b = x - az
                int b = ((pActor01->_X+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_Z+pAAPrism01->_cz)) + pAAPrism01->_b;
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
                        pCChecker01->_blown_sgn_vX += 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vX += 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
                        return true;
                    }
                }
            }
        }
        return false;
    }



    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliSphere*  pSphere02) {
        //＜プリズム と 球＞
        int aX1 = pActor01->_X + pAAPrism01->_x1;
        int aY1 = pActor01->_Y + pAAPrism01->_y1;
        int aZ1 = pActor01->_Z + pAAPrism01->_z1;
        int aX2 = pActor01->_X + pAAPrism01->_x2;
        int aY2 = pActor01->_Y + pAAPrism01->_y2;
        int aZ2 = pActor01->_Z + pAAPrism01->_z2;

        //AAB 対 球でまず判定する
        if (isHit(pCChecker01   , pActor01   , (ColliAAB*)pAAPrism01,
                  pCChecker02, pActor02, pSphere02)          ) {
            //この時点でAAB 対 球でヒット。ここからプリズムでもヒットか検証する
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = y - ax
                double b = ((pActor01->_Y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_X+pAAPrism01->_cx)) + pAAPrism01->_b;

                int oppX, oppY;
                int bZc = pActor02->_Z + pSphere02->_cz; //球の中心Z座標
                if (aZ1 < bZc && bZc < aZ2) {
                    //球の中心Z座標がプリズムのZ幅範囲内ならば、予め保持している_vIH_x,_vIH_yを使用して
                    //プリズム斜辺と最短距離の円周上のXY座標を求める
                    oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bZc >= aZ2) {
                        //球の中心Z座標がプリズムのZ幅範囲外の場合
                        //離れる距離に応じて、球側の半径(pSphere02->_r)を小さくして差分を計算
                        //小さくする割合は ROOT_1_MINUS_XX (1/4円の解のテーブル配列）を使用。
                        //                 |
                        //                 ＼
                        //        ┌───┐ `─
                        // z- ←  │      │  → z+
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
                    } else if (aZ1 >= bZc) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
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
                int b = ((pActor01->_Z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_Y+pAAPrism01->_cy)) + pAAPrism01->_b;
                int oppY, oppZ;

                int bXc = pActor02->_X + pSphere02->_cx;
                if (aX1 < bXc && bXc < aX2) {
                    oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bXc >= aX2) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
                    } else if (aX1 >= bXc) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
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
                int b = ((pActor01->_X+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_Z+pAAPrism01->_cz)) + pAAPrism01->_b;
                int oppZ,oppX;
                int bYc = pActor02->_Y + pSphere02->_cy;
                if (aY1 < bYc && bYc < aY2) {
                    oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bYc >= aY2) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_y * r;
                    } else if (aY1 >= bYc) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_y * r;
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
