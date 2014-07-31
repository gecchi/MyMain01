#ifndef GGAFLIB_STGUTIL_H_
#define GGAFLIB_STGUTIL_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

#include "jp/ggaf/lib/util/ColliAAB.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafLib::StgUtil

namespace GgafLib {

/**
 * ユーティリティ .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class StgUtil: public GgafDxCore::GgafDxUtil {
public:
    struct Pos {
        coord X;
        coord Y;
        coord Z;
    };

    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAB* pAAB01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliAAB* pAAB02 ) {
        //＜AAB と AAB＞
        //軸が一致しない確率が高そうな順番(X>Z>Y)に判定
        if (pActor01->_x + pAAB01->_x2 >= pActor02->_x + pAAB02->_x1) {
            if (pActor01->_x + pAAB01->_x1 <= pActor02->_x + pAAB02->_x2) {
                if (pActor01->_z + pAAB01->_z2 >= pActor02->_z + pAAB02->_z1) {
                    if (pActor01->_z + pAAB01->_z1 <= pActor02->_z + pAAB02->_z2) {
                        if (pActor01->_y + pAAB01->_y2 >= pActor02->_y + pAAB02->_y1) {
                            if (pActor01->_y + pAAB01->_y1 <= pActor02->_y + pAAB02->_y2) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliSphere* pSphere01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliSphere* pSphere02 ) {
        //＜球 と 球＞
        //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
        //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
        //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
        double d2 = (double)((pActor02->_x+pSphere02->_x) - (pActor01->_x+pSphere01->_x)) * ((pActor02->_x+pSphere02->_x) - (pActor01->_x+pSphere01->_x)) +
                    (double)((pActor02->_y+pSphere02->_y) - (pActor01->_y+pSphere01->_y)) * ((pActor02->_y+pSphere02->_y) - (pActor01->_y+pSphere01->_y)) +
                    (double)((pActor02->_z+pSphere02->_z) - (pActor01->_z+pSphere01->_z)) * ((pActor02->_z+pSphere02->_z) - (pActor01->_z+pSphere01->_z));
        if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
        ) {
            return true;
        } else {
            return false;
        }
    }

    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAB*    pAAB01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliSphere* pSphere02) {
        //＜AAB と 球＞
        coord o_scx = pActor02->_x + pSphere02->_cx;
        coord o_scy = pActor02->_y + pSphere02->_cy;
        coord o_scz = pActor02->_z + pSphere02->_cz;
        coord bx1 = pActor01->_x + pAAB01->_x1;
        coord bx2 = pActor01->_x + pAAB01->_x2;
        coord by1 = pActor01->_y + pAAB01->_y1;
        coord by2 = pActor01->_y + pAAB01->_y2;
        coord bz1 = pActor01->_z + pAAB01->_z1;
        coord bz2 = pActor01->_z + pAAB01->_z2;
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
            return true;
        } else {
            return false;
        }
    }


    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliAAB*     pAAB02     ) {
        //＜プリズム と AAB＞
        int aX1 = pActor01->_x + pAAPrism01->_x1;
        int aY1 = pActor01->_y + pAAPrism01->_y1;
        int aZ1 = pActor01->_z + pAAPrism01->_z1;
        int aX2 = pActor01->_x + pAAPrism01->_x2;
        int aY2 = pActor01->_y + pAAPrism01->_y2;
        int aZ2 = pActor01->_z + pAAPrism01->_z2;

        int bX1 = pActor02->_x + pAAB02->_x1;
        int bY1 = pActor02->_y + pAAB02->_y1;
        int bZ1 = pActor02->_z + pAAB02->_z1;
        int bX2 = pActor02->_x + pAAB02->_x2;
        int bY2 = pActor02->_y + pAAB02->_y2;
        int bZ2 = pActor02->_z + pAAB02->_z2;

        if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
            //この時点でAAB と AAB ならばヒット
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = y - ax
                double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

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
                int b = ((pActor01->_z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_y+pAAPrism01->_cy)) + pAAPrism01->_b;
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
                int b = ((pActor01->_x+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_z+pAAPrism01->_cz)) + pAAPrism01->_b;
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



    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliSphere*  pSphere02  ) {
        //＜プリズム と 球＞
        //MEMO:厳密な当たり判定計算は行っていません。
        int aX1 = pActor01->_x + pAAPrism01->_x1;
        int aY1 = pActor01->_y + pAAPrism01->_y1;
        int aZ1 = pActor01->_z + pAAPrism01->_z1;
        int aX2 = pActor01->_x + pAAPrism01->_x2;
        int aY2 = pActor01->_y + pAAPrism01->_y2;
        int aZ2 = pActor01->_z + pAAPrism01->_z2;

        //AAB 対 球でまず判定する
        if (isHit(pActor01, (ColliAAB*)pAAPrism01,
                  pActor02, pSphere02             ) ) {
            //この時点でAAB 対 球でヒット。ここからプリズムでもヒットか検証する
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
                //ワールド座標でのプリズム境界線の切片を求める b = y - ax
                double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

                int oppX, oppY;
                int bZc = pActor02->_z + pSphere02->_cz; //球の中心Z座標
                if (aZ1 < bZc && bZc < aZ2) {
                    //球の中心Z座標がプリズムのZ幅範囲内ならば、予め保持している_vIH_x,_vIH_yを使用して
                    //プリズム斜辺と最短距離の円周上のXY座標を求める
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else if (bZc >= aZ2) {
                    //球の中心Z座標がプリズムのZ幅範囲外の場合
                    //離れる距離に応じて、球側の半径(pSphere02->_r)を小さくして差分を計算
                    //小さくする割合は ROOT_1_MINUS_XX (1/4円の解のテーブル配列）を使用。
                    //                 |
                    //                 ＼
                    //        ┌───┐ `─
                    // z- ←  │      │  → z+
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
                } else { //if (aZ1 >= bZc) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
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
                int b = ((pActor01->_z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_y+pAAPrism01->_cy)) + pAAPrism01->_b;
                int oppY, oppZ;

                int bXc = pActor02->_x + pSphere02->_cx;
                if (aX1 < bXc && bXc < aX2) {
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bXc >= aX2) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
                    } else if (aX1 >= bXc) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
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
                int b = ((pActor01->_x+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_z+pAAPrism01->_cz)) + pAAPrism01->_b;
                int oppZ,oppX;
                int bYc = pActor02->_y + pSphere02->_cy;
                if (aY1 < bYc && bYc < aY2) {
                    oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bYc >= aY2) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_y * r;
                    } else if (aY1 >= bYc) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_y * r;
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
     * 弾を複数個撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_x               発射元X座標
     * @param prm_y               発射元Y座標
     * @param prm_z               発射元Z座標
     * @param prm_rz              発射方向Rz
     * @param prm_ry              発射方向Ry
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_velo_first      初弾のショット初期速度
     * @param prm_acce            初弾のショット初期加速度
     * @param prm_set_num         撃つ弾の合計数
     * @param prm_interval_frames 弾と弾の出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全弾一斉発射。）
     * @param prm_attenuated      初弾以降のショット初期速度・加速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched 弾がデポジトリから dispach() された時に呼び出すコールバック。
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって 弾を複数個撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_from_x          発射元X座標
     * @param prm_from_y          発射元Y座標
     * @param prm_from_z          発射元Z座標
     * @param prm_to_x            目標X座標
     * @param prm_to_y            目標Y座標
     * @param prm_to_z            目標Z座標
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_velo_first      初弾のショット初期速度。初弾以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            ショット初期加速度
     * @param prm_set_num         撃つ弾の合計数
     * @param prm_interval_frames 弾と弾の出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全弾一斉発射。）
     * @param prm_attenuated      初弾以降のショット初期速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                                       coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって 弾を複数個撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_velo_first      初弾のショット初期速度。初弾以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            ショット初期加速度
     * @param prm_set_num         撃つ弾の合計数
     * @param prm_interval_frames 弾と弾の出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全弾一斉発射。）
     * @param prm_attenuated      初弾以降のショット初期速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay001(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int) = nullptr);


    /**
     * N-Way弾（Rz変化）を複数セット撃つ .
     * prm_rx, prm_rz, prm_ry = (0,0,0) で、XY平面上にRz変化の N-Way弾 を放ちます。
     * @param prm_x                発射元X座標
     * @param prm_y                発射元Y座標
     * @param prm_z                発射元Z座標
     * @param prm_rx               N Wayの回転角
     * @param prm_rz               発射方向Rz
     * @param prm_ry               発射方向Ry
     * @param prm_pDepo_shot       発射するショットのデポジトリ
     * @param prm_r                発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N            N-Way数（Rz変化）
     * @param prm_ang_clearance_N   N-Wayの間隔角度
     * @param prm_velo_first       N-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce             N-Way弾各セットのショット初期加速度
     * @param prm_set_num          発射する N-Way弾セットの合計セット数
     * @param prm_interval_frames  弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated       初弾セット以降の各セット毎のショット初期速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_way_N,
                                                       angle prm_ang_clearance_N,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rx, _rz > _ry）N-Way弾（Rz変化）を複数セット撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom                  発射元
     * @param prm_pDepo_shot             発射するショットのデポジトリ
     * @param prm_r                      発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N                  N-Way数（Rz変化）
     * @param prm_ang_clearance_N         N-Wayの間隔角度
     * @param prm_velo_first             N-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce                   N-Way弾各セットのショット初期加速度
     * @param prm_set_num                発射する N-Way弾セットの合計セット数
     * @param prm_interval_frames        弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated             初弾セット以降の各セット毎のショット初期速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay002(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_way_N,
                                                       angle prm_ang_clearance_N,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * N*M-Way弾を複数セット撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_x                発射元X座標
     * @param prm_y                発射元Y座標
     * @param prm_z                発射元Z座標
     * @param prm_rx               N*M 長方形の回転角
     * @param prm_rz               発射方向Rz
     * @param prm_ry               発射方向Ry
     * @param prm_pDepo_shot1      発射するショットのデポジトリその１
     * @param prm_paUint32_dotmat1 ショットその１を使用するドットマトリックス
     * @param prm_pDepo_shot2      発射するショットのデポジトリその２
     * @param prm_paUint32_dotmat2 ショットその２を使用するドットマトリックス
     * @param prm_pDepo_shot3      発射するショットのデポジトリその３
     * @param prm_paUint32_dotmat3 ショットその３を使用するドットマトリックス
     * @param prm_r                発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N            N-Way数（Rz変化）
     * @param prm_way_M            M-Way数（Ry変化）
     * @param prm_ang_clearance_N   N-Wayの間隔角度
     * @param prm_ang_clearance_M   M-Wayの間隔角度
     * @param prm_velo_first       N*M-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce             N*M-Way弾各セットのショット初期加速度
     * @param prm_set_num          発射する N*M-Way弾セットの合計セット数
     * @param prm_interval_frames  弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated       初弾セット以降の各セット毎のショット初期速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                                       coord prm_r,
                                                       int prm_way_N, int prm_way_M,
                                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int, int, int) = nullptr);


    /**
     * 発射元が向いている方向（_rx > _rz > _ry）に向かって N*M-Way弾を複数セット撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom            発射元
     * @param prm_pDepo_shot1      発射するショットのデポジトリその１
     * @param prm_paUint32_dotmat1 ショットその１を使用するドットマトリックス
     * @param prm_pDepo_shot2      発射するショットのデポジトリその２
     * @param prm_paUint32_dotmat2 ショットその２を使用するドットマトリックス
     * @param prm_pDepo_shot3      発射するショットのデポジトリその３
     * @param prm_paUint32_dotmat3 ショットその３を使用するドットマトリックス
     * @param prm_r                発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N            N-Way数（Rz変化）
     * @param prm_way_M            M-Way数（Ry変化）
     * @param prm_ang_clearance_N   N-Wayの間隔角度
     * @param prm_ang_clearance_M   M-Wayの間隔角度
     * @param prm_velo_first       N*M-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce             N*M-Way弾各セットのショット初期加速度
     * @param prm_set_num          発射する N*M-Way弾セットの合計セット数
     * @param prm_interval_frames  弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated       初弾セット以降の各セット毎のショット初期速度の減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay003(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                                       coord prm_r,
                                                       int prm_way_N, int prm_way_M,
                                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int, int, int) = nullptr);



    /**
     * 拡散放射弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_x               発射元X座標
     * @param prm_y               発射元Y座標
     * @param prm_z               発射元Z座標
     * @param prm_rz              発射方向Rz
     * @param prm_ry              発射方向Ry
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_radial_way_num  １セット放射Way数
     * @param prm_expanse_angle   放射弾の照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_set_num         撃つ放射WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched デポジトリ(prm_pDepo_shot)から dispatch() されて、
     *                                 移動方向、初期速度、加速度が設定された後にコールバックされる関数を設定。
     *                                 引数には次の値が引き渡される。
     *                                 void f(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()された弾のアクター
     *                                 prm_dispatch_num   何回目の dispatch() の弾か  (1～)
     *                                 prm_set_index      放射WAY弾何セット目であるか (0～)
     *                                 prm_way_index      何WAY目の弾であるか         (0～)
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_radial_way_num, angle prm_expanse_angle,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって拡散放射弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_radial_way_num  １セット放射Way数
     * @param prm_expanse_angle   放射弾の照射中心角(0 ～ D180ANG。懐中電灯の光の広がりの成す角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_velo_first      初弾セットのショット初期速度
     * @param prm_acce            初弾セットのショット初期加速度
     * @param prm_set_num         撃つ放射WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度・加速度の減衰率(> 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched デポジトリ(prm_pDepo_shot)から dispatch() されて、
     *                                 移動方向、初期速度、加速度が設定された後にコールバックされる関数を設定。
     *                                 引数には次の値が引き渡される。
     *                                 void f(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()された弾のアクター
     *                                 prm_dispatch_num   何回目の dispatch() の弾か  (1～)
     *                                 prm_set_index      放射WAY弾何セット目であるか (0～)
     *                                 prm_way_index      何WAY目の弾であるか         (0～)
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay004(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_radial_way_num, angle prm_expanse_angle,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * 黄金角拡散放射弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_x               発射元X座標
     * @param prm_y               発射元Y座標
     * @param prm_z               発射元Z座標
     * @param prm_rz              発射方向Rz
     * @param prm_ry              発射方向Ry
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_num         １セット発射数(1～999)
     * @param prm_first_expanse_angle   発射弾の初期照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_inc_expanse_angle     1弾毎に加算する照射角差分(0 ～ D180ANG)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_set_num         撃つ放射WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                             angle prm_rz, angle prm_ry,
                                                             GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                             coord prm_r,
                                                             int prm_way_num,
                                                             angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                             velo prm_velo_first, acce prm_acce,
                                                             int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                             void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって黄金角拡散放射弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_num         １セット発射数(1～999)
     * @param prm_first_expanse_angle   発射弾の初期照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_inc_expanse_angle     1弾毎に加算する照射角差分(0 ～ D180ANG)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_set_num         撃つ放射WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度減衰率(< 1.0)、或いは増幅率(>1.0)
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWayGoldenAng(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                             GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                             coord prm_r,
                                                             int prm_way_num,
                                                             angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                             velo prm_velo_first, acce prm_acce,
                                                             int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                             void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);


};

}
#endif /*GGAFLIB_STGUTIL_H_*/
