#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker2D.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"



using namespace GgafLib;

bool StgUtil::_was_StgUtil_inited_flg = false;
float StgUtil::ROOT_1_MINUS_XX[1000];
uint32_t StgUtil::BITNUM[33];
std::map<pos_t,pos_t> StgUtil::POS_R_TRIANGLE_inv_X;
std::map<pos_t,pos_t> StgUtil::POS_R_TRIANGLE_inv_Y;


#define C_INT64(X)  ( (int_fast64_t)((X) * (1.0 / LEN_UNIT)) )


void StgUtil::init() {
    GgafDx::Util::init();
    if (StgUtil::_was_StgUtil_inited_flg) {
        return;
    }

    //ROOT_1_MINUS_XXの設定
    for (int i = 0; i < 1000; i++) {
        StgUtil::ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }

    BITNUM[0] = (uint32_t)0;
    for (int i = 1; i < 33; i++) {
        BITNUM[i] = ((uint32_t)1 << (i-1));
    }

    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_NN] = POS_R_TRIANGLE_PN;
    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_NP] = POS_R_TRIANGLE_PP;
    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_PN] = POS_R_TRIANGLE_NN;
    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_PP] = POS_R_TRIANGLE_NP;

    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_NN] = POS_R_TRIANGLE_NP;
    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_NP] = POS_R_TRIANGLE_NN;
    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_PN] = POS_R_TRIANGLE_PP;
    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_PP] = POS_R_TRIANGLE_PN;

    StgUtil::_was_StgUtil_inited_flg = true;
}

GgafDx::CollisionChecker* StgUtil::createCollisionChecker(GgafDx::GeometricActor* prm_pActor) {
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        return NEW WorldCollisionChecker2D(prm_pActor);
    } else {
        return NEW WorldCollisionChecker3D(prm_pActor);
    }
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
    //＜球 と 球＞
    //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
    //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
    double dx = (double)( (pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx) );
    double dy = (double)( (pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy) );
    double dz = (double)( (pActor02->_z+pSphere02->_cz) - (pActor01->_z+pSphere01->_cz) );
    double dd = dx*dx + dy*dy + dz*dz;
    if (dd <= (double)(pSphere02->_r + pSphere01->_r) * (double)(pSphere02->_r + pSphere01->_r)
    ) {
        return true;
    } else {
        return false;
    }
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02) {
    //＜AAB と 球＞
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord o_scz = pActor02->_z + pSphere02->_cz;
    const coord bx1 = pActor01->_x + pAABox01->_x1;
    const coord bx2 = pActor01->_x + pAABox01->_x2;
    const coord by1 = pActor01->_y + pAABox01->_y1;
    const coord by2 = pActor01->_y + pAABox01->_y2;
    const coord bz1 = pActor01->_z + pAABox01->_z1;
    const coord bz2 = pActor01->_z + pAABox01->_z2;

    double square_length = 0; //球の中心とAABの最短距離(を二乗)した値
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
    //↑の判定が全てハズレて、square_length == 0 ならば、
    //球の中心が、BOX内にあるという意味になる。

    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length <= pSphere02->_rr) { //あたり判定なので、ルートをとらず二乗のままの比較でよい
        return true;
    } else {
        return false;
    }
}


bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02     ) {
    //＜プリズム と AAB＞
    const coord aX = pActor01->_x;
    const coord aY = pActor01->_y;
    const coord aZ = pActor01->_z;
    const coord aX1 = aX + pAAPrism01->_x1;
    const coord aY1 = aY + pAAPrism01->_y1;
    const coord aZ1 = aZ + pAAPrism01->_z1;
    const coord aX2 = aX + pAAPrism01->_x2;
    const coord aY2 = aY + pAAPrism01->_y2;
    const coord aZ2 = aZ + pAAPrism01->_z2;
    const coord bX1 = pActor02->_x + pAABox02->_x1;
    const coord bY1 = pActor02->_y + pAABox02->_y1;
    const coord bZ1 = pActor02->_z + pAABox02->_z1;
    const coord bX2 = pActor02->_x + pAABox02->_x2;
    const coord bY2 = pActor02->_y + pAABox02->_y2;
    const coord bZ2 = pActor02->_z + pAABox02->_z2;

    if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //この時点でAAB と AAB ならばヒット
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        if (pos & POS_PRISM_XY_xx) { //XY平面スライスのプリズム
            //ワールド座標でのプリズム境界線の切片を求める b = y - ax
            const double b = ((aY+pAAPrism01->_cy) - pAAPrism01->_a * (aX+pAAPrism01->_cx)) + pAAPrism01->_b;

            if (pos & POS_PRISM_xx_PP) {
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

            } else if (pos & POS_PRISM_xx_NP) {
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

            } else if (pos & POS_PRISM_xx_PN) {
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

            } else { // のこりは POS_PRISM_xx_NN のみである
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
        } else if (pos & POS_PRISM_YZ_xx) {//YZ平面スライスのプリズム
            //ワールド座標でのプリズム境界線の切片を求める b = z - ay
            int b = ((aZ+pAAPrism01->_cz) - pAAPrism01->_a * (aY+pAAPrism01->_cy)) + pAAPrism01->_b;
            if (pos & POS_PRISM_xx_PP) {
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

            } else if (pos & POS_PRISM_xx_NP) {
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

            } else if (pos & POS_PRISM_xx_PN) {
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

            } else { //のこりは POS_PRISM_xx_NN のみである
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

        } else if (pos & POS_PRISM_ZX_xx) {
            //ワールド座標でのプリズム境界線の切片を求める b = x - az
            int b = ((aX+pAAPrism01->_cx) - pAAPrism01->_a * (aZ+pAAPrism01->_cz)) + pAAPrism01->_b;
            if (pos & POS_PRISM_xx_PP) {
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

            } else if (pos & POS_PRISM_xx_NP) {
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

            } else if (pos & POS_PRISM_xx_PN) {
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

            } else { //残りは POS_PRISM_xx_NN のみである
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


bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  ) {
    //＜プリズム と 球＞
    //MEMO:厳密な当たり判定計算は行っていません。
    //まず、球 対 AAB の判定を行う
    const coord aX = pActor01->_x;
    const coord aY = pActor01->_y;
    const coord aZ = pActor01->_z;
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord o_scz = pActor02->_z + pSphere02->_cz;
    const coord aX1 = aX + pAAPrism01->_x1;
    const coord aY1 = aY + pAAPrism01->_y1;
    const coord aZ1 = aZ + pAAPrism01->_z1;
    const coord aX2 = aX + pAAPrism01->_x2;
    const coord aY2 = aY + pAAPrism01->_y2;
    const coord aZ2 = aZ + pAAPrism01->_z2;
    double square_length = 0; //球の中心とAABの最短距離を二乗した値
    if(o_scx < aX1) {
        square_length += (double)(o_scx - aX1) * (o_scx - aX1);
    }
    if(o_scx > aX2) {
        square_length += (double)(o_scx - aX2) * (o_scx - aX2);
    }
    if(o_scy < aY1) {
        square_length += (double)(o_scy - aY1) * (o_scy - aY1);
    }
    if(o_scy > aY2) {
        square_length += (double)(o_scy - aY2) * (o_scy - aY2);
    }
    if(o_scz < aZ1) {
        square_length += (double)(o_scz - aZ1) * (o_scz - aZ1);
    }
    if(o_scz > aZ2) {
        square_length += (double)(o_scz - aZ2) * (o_scz - aZ2);
    }
    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length > pSphere02->_rr) {
        return false;
    }
    //この時点でAAB 対 球でヒット。ここからプリズムでもヒットか検証する

    const int pos = pAAPrism01->_pos_info;
    const double a = pAAPrism01->_a;
    if (pos & POS_PRISM_XY_xx) { //XY平面スライスのプリズム
        //ワールド座標でのプリズム境界線の切片を求める b = y - ax
        const double b = ((aY+pAAPrism01->_cy) - pAAPrism01->_a * (aX+pAAPrism01->_cx)) + pAAPrism01->_b;

        int oppX, oppY;
        const int bZc = o_scz; //球の中心Z座標
        if (aZ1 < bZc && bZc < aZ2) {
            //球の中心Z座標がプリズムのZ幅範囲内ならば、予め保持している_vIH_x,_vIH_yを使用して
            //プリズム斜辺と最短距離の円周上のXY座標を求める
            oppX = o_scx + pAAPrism01->_vIH_x * pSphere02->_r;
            oppY = o_scy + pAAPrism01->_vIH_y * pSphere02->_r;
        } else if (bZc >= aZ2) {
            //球の中心Z座標がプリズムのZ幅範囲外の場合
            //離れる距離に応じて、球側の半径(pSphere02->_r)を小さくして差分を計算
            //小さくする割合は ROOT_1_MINUS_XX (1/4円の解のテーブル配列）を使用。
            //                 |
            //                 ＼
            //        ┌───┐ `─
            // z- ←  │      │  → z+
            int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
            oppX = o_scx + pAAPrism01->_vIH_x * r;
            oppY = o_scy + pAAPrism01->_vIH_y * r;
        } else { //if (aZ1 >= bZc) {
            int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
            oppX = o_scx + pAAPrism01->_vIH_x * r;
            oppY = o_scy + pAAPrism01->_vIH_y * r;
        }

        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { // のこりは POS_PRISM_xx_NN のみである
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
    } else if (pos & POS_PRISM_YZ_xx) {//YZ平面スライスのプリズム
        //ワールド座標でのプリズム境界線の切片を求める b = z - ay
        const int b = ((aZ+pAAPrism01->_cz) - pAAPrism01->_a * (aY+pAAPrism01->_cy)) + pAAPrism01->_b;
        int oppY, oppZ;

        const int bXc = o_scx;
        if (aX1 < bXc && bXc < aX2) {
            oppY = o_scy + pAAPrism01->_vIH_x * pSphere02->_r;
            oppZ = o_scz + pAAPrism01->_vIH_y * pSphere02->_r;
        } else {
            if (bXc >= aX2) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                oppY = o_scy + pAAPrism01->_vIH_x * r;
                oppZ = o_scz + pAAPrism01->_vIH_y * r;
            } else if (aX1 >= bXc) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                oppY = o_scy + pAAPrism01->_vIH_x * r;
                oppZ = o_scz + pAAPrism01->_vIH_y * r;
            }
        }
        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { //のこりは POS_PRISM_xx_NN のみである
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

    } else if (pos & POS_PRISM_ZX_xx) {
        //ワールド座標でのプリズム境界線の切片を求める b = x - az
        const int b = ((aX+pAAPrism01->_cx) - pAAPrism01->_a * (aZ+pAAPrism01->_cz)) + pAAPrism01->_b;
        int oppZ,oppX;
        const int bYc = o_scy;
        if (aY1 < bYc && bYc < aY2) {
            oppZ = o_scz + pAAPrism01->_vIH_x * pSphere02->_r;
            oppX = o_scx + pAAPrism01->_vIH_y * pSphere02->_r;
        } else {
            if (bYc >= aY2) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                oppZ = o_scz + pAAPrism01->_vIH_x * r;
                oppX = o_scx + pAAPrism01->_vIH_y * r;
            } else if (aY1 >= bYc) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                oppZ = o_scz + pAAPrism01->_vIH_x * r;
                oppX = o_scx + pAAPrism01->_vIH_y * r;
            }
        }
        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { //残りは POS_PRISM_xx_NN のみである
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
    return false;
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAABox*     const pAABox02     ) {
    //ピラミッドとBOX
    const coord aX1 = pActor01->_x + pAAPyramid01->_x1;
    const coord aY1 = pActor01->_y + pAAPyramid01->_y1;
    const coord aZ1 = pActor01->_z + pAAPyramid01->_z1;
    const coord aX2 = pActor01->_x + pAAPyramid01->_x2;
    const coord aY2 = pActor01->_y + pAAPyramid01->_y2;
    const coord aZ2 = pActor01->_z + pAAPyramid01->_z2;
    //斜面の法線
    float a = pAAPyramid01->_s_nvx;
    float b = pAAPyramid01->_s_nvy;
    float c = pAAPyramid01->_s_nvz;
    //斜面と対角線の交点
    const coord px = pActor01->_x + pAAPyramid01->_l_px;
    const coord py = pActor01->_y + pAAPyramid01->_l_py;
    const coord pz = pActor01->_z + pAAPyramid01->_l_pz;

    const coord bX1 = pActor02->_x + pAABox02->_x1;
    const coord bY1 = pActor02->_y + pAABox02->_y1;
    const coord bZ1 = pActor02->_z + pAABox02->_z1;
    const coord bX2 = pActor02->_x + pAABox02->_x2;
    const coord bY2 = pActor02->_y + pAABox02->_y2;
    const coord bZ2 = pActor02->_z + pAABox02->_z2;


    if (aX2 >= bX1 && aX1 <= bX2 && aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2) {
        //この時点でAAB と AAB ならばヒット

        //ピラミッド斜面に対してピラミッド側のBOX領域内で、相手BOXの最近傍点を求める
        const pos_t pos_info = pAAPyramid01->_pos_info;
        coord nnx, nny, nnz; //BOX内最近傍点
        if (pos_info & POS_PYRAMID_Pxx) {
            //bX2に興味がある
            if (/* aX1 <= bX2 && */ bX2 <= aX2) {
                //bX2 が中にある
                nnx = bX2;
            } else { //if (aX2 < bX2) {
                //bX2 が外にある
                nnx = aX2;
            }
        } else {
            //bX1に興味がある
            if (aX1 <= bX1 /* && bX1 <= aX2*/ ) {
                //bX1 が中にある
                nnx = bX1;
            } else { // if (aX1 > bX1) {
                //bX1 が外にある
                nnx = aX1;
            }
        }
        if (pos_info & POS_PYRAMID_xPx) {
            //bY2に興味がある
            if (/* aY1 <= bY2 &&*/ bY2 <= aY2) {
                //bY2 が中にある
                nny = bY2;
            } else { //if (aY2 < bY2) {
                //bY2 が外にある
                nny = aY2;
            }
        } else {
            //bY1に興味がある
            if (aY1 <= bY1 /*&& bY1 <= aY2*/) {
                //by1 が中にある
                nny = bY1;
            } else { //if (aY1 > bY1) {
                //bx1 が外にある
                nny = aY1;
            }
        }

        if (pos_info & POS_PYRAMID_xxP) {
            //bZ2に興味がある
            if (/*aZ1 <= bZ2 &&*/ bZ2 <= aZ2) {
                //bZ2 が中にある
                nnz = bZ2;
            } else { //if (aZ2 < bZ2) {
                //bZ2 が外にある
                nnz = aZ2;
            }
        } else {
            //bZ1に興味がある
            if (aZ1 <= bZ1 /* && bZ1 <= aZ2*/) {
                //bz1 が中にある
                nnz = bZ1;
            } else { //if (aZ1 > bZ1) {
                //bx1 が外にある
                nnz = aZ1;
            }
        }
        //(nnx,nny,nnz) がBOX内近傍点
        //斜面の法線ベクトル (a, b, c)
        //斜面上の点(px, py, pz) から 近傍点(nnx,nny,nnz) のベクトル
        // (nnx-px, nny-py, nnz-pz) の内積が 負 ならば近傍点 (nnx,nny,nnz) がピラミッドの中にある
        double d = a*(nnx-px) + b*(nny-py) + c*(nnz-pz);
        if (d < 0) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere*    const pSphere02  ) {
    //三直角三角錐の三直角頂点の座標を原点(0,0,0)におき、
    //A(ex,0,0), B(0,ey,0), C(0,0,ez) の三直角三角錐で当たり判定を考えたいので、
    //球の位置(o_cx, o_cy, o_cz)を座標変換する。

    const int_fast64_t ex = C_INT64(pAAPyramid01->_dx); //幅がそのまま頂点AのX軸座標となる
    const int_fast64_t ey = C_INT64(pAAPyramid01->_dy); //高さがそのまま頂点BのY軸座標となる
    const int_fast64_t ez = C_INT64(pAAPyramid01->_dz); //奥行きさがそのまま頂点CのZ軸座標となる
    const int_fast64_t o_r  = C_INT64(pSphere02->_r);   //球の半径は座標変換に無影響なのでそのまま
    const int_fast64_t o_rr = o_r*o_r;

    //本来の球の位置
    int_fast64_t o_cx = C_INT64(pActor02->_x + pSphere02->_cx);
    int_fast64_t o_cy = C_INT64(pActor02->_y + pSphere02->_cy);
    int_fast64_t o_cz = C_INT64(pActor02->_z + pSphere02->_cz);
    const pos_t pos_info = pAAPyramid01->_pos_info; //三直角三角錐の姿勢情報
    if (pos_info & POS_PYRAMID_Pxx) {
        //元の三直角三角錐の頂点のX軸は正の方向
        o_cx -= C_INT64(pActor01->_x + pAAPyramid01->_x2);
        o_cx = -o_cx; //x軸反転
    } else {
        //元の三直角三角錐の頂点のX軸は負の方向
        o_cx -= C_INT64(pActor01->_x + pAAPyramid01->_x1);
    }
    if (pos_info & POS_PYRAMID_xPx) {
        //元の三直角三角錐の頂点のY軸は正の方向
        o_cy -= C_INT64(pActor01->_y + pAAPyramid01->_y2);
        o_cy = -o_cy; //y軸反転
    } else {
        //元の三直角三角錐の頂点のY軸は負の方向
        o_cy -= C_INT64(pActor01->_y + pAAPyramid01->_y1);
    }

    if (pos_info & POS_PYRAMID_xxP) {
        //元の三直角三角錐の頂点のZ軸は正の方向
        o_cz -= C_INT64(pActor01->_z + pAAPyramid01->_z2);
        o_cz = -o_cz; //z軸反転
    } else {
        //元の三直角三角錐の頂点のZ軸は負の方向
        o_cz -= C_INT64(pActor01->_z + pAAPyramid01->_z1);
    }
    //球の位置変換完了、ここから当たり判定ロジック

    //xy平面より内(第一卦限側)か
    const bool xy = (o_cz > 0);
    //yz平面より内(第一卦限側)か
    const bool yz = (o_cx > 0);
    //zx平面より内(第一卦限側)か
    const bool zx = (o_cy > 0);
    //xy平面に平行な点Cを通る平面(true:原点側)
    const bool xy_C = (o_cz < ez);
    //yz平面に平行な点Aを通る平面(true:原点側)
    const bool yz_A = (o_cx < ex);
    //zx平面に平行な点Bを通る平面(true:原点側)
    const bool zx_B = (o_cy < ey);

    //球対BOXの当たり判定をまず行う
    const int_fast64_t o_cx2 = o_cx*o_cx;
    const int_fast64_t o_cy2 = o_cy*o_cy;
    const int_fast64_t o_cz2 = o_cz*o_cz;
    const int_fast64_t o_cx_MINUS_ex2 = (o_cx - ex)*(o_cx - ex);
    const int_fast64_t o_cy_MINUS_ey2 = (o_cy - ey)*(o_cy - ey);
    const int_fast64_t o_cz_MINUS_ez2 = (o_cz - ez)*(o_cz - ez);
    int_fast64_t slength = 0; //球の中心とAABの最短距離を二乗した値
    if (!yz) {
        slength += o_cx2;
    }
    if (!yz_A) {
        slength += o_cx_MINUS_ex2;
    }
    if (!zx) {
        slength += o_cy2;
    }
    if (!zx_B) {
        slength += o_cy_MINUS_ey2;
    }
    if (!xy) {
        slength += o_cz2;
    }
    if (!xy_C) {
        slength += o_cz_MINUS_ez2;
    }
    if (slength > o_rr) {
        //square_length が球の半径（の二乗）よりも長ければBOXとすら衝突していない。
        return false;
    }
    //ここから以降は、球 対 BOX で衝突していることになる。
    //三直角三角錐のどの部分（頂点、辺、面）との距離で判定すればよいか
    //場合わけで考える

    if (!xy && !yz && !zx) {
        //原点との距離で判定
        //球 対 BOX で衝突しているのでヒット
        return true;
    }

    if (xy) {
        if (!yz) {
            if (!zx) {
                if (xy_C) {
                    //辺OCとの距離で判定
                    //球 対 BOX で衝突しているのでヒット
                    return true;
                }
            }
        }
    } else {
        if (yz) {
            if (!zx) {
                if (yz_A) {
                    //辺OAとの距離で判定
                    //球 対 BOX で衝突しているのでヒット
                    return true;
                }
            }
        } else {
            if (zx) {
                if (zx_B) {
                    //辺OBとの距離で判定
                    //球 対 BOX で衝突しているのでヒット
                    return true;
                }
            }
        }
    }

    const int_fast64_t exey = ex*ey;
    const int_fast64_t eyez = ey*ez;
    const int_fast64_t ezex = ez*ex;
    // A(ex,0,0), B(0,ey,0) を含むxy平面に垂直な面より内（原点がある側）
    const bool vxy_AB = (-ey*o_cx - ex*o_cy           + exey > 0);
    // B(0,ey,0), C(0,0,ez) を含むyz平面に垂直な面より内（原点がある側）
    const bool vyz_BC = (          -ez*o_cy - ey*o_cz + eyez > 0);
    // C(0,0,ez), A(ex,0,0) を含むzx平面に垂直な面より内（原点がある側）
    const bool vzx_CA = (-ez*o_cx           - ex*o_cz + ezex > 0);
    if (xy) {
        if (yz) {
            if (!zx) {
                if (vzx_CA) {
                    //面OCAとの距離で判定
                    //球 対 BOX で衝突しているのでヒット
                    return true;
                }

            }
        } else {
            if (zx) {
                if (vyz_BC) {
                    //面OBCとの距離で判定
                    //球 対 BOX で衝突しているのでヒット
                    return true;
                }
            }
        }
    } else {
        if (yz) {
            if (zx) {
                if (vxy_AB) {
                    //面OABとの距離で判定
                    //球 対 BOX で衝突しているのでヒット
                    return true;
                }
            }
        }
    }

    const int_fast64_t ex2 = ex*ex;
    const int_fast64_t ey2 = ey*ey;
    const int_fast64_t ez2 = ez*ez;
    //点Aと辺ABの境界面(true:原点側)
    const bool bo_A_AB = ( ezex * o_cx - eyez * o_cy               - ex2*ez > 0);
    //点Aと辺ACの境界面(true:原点側)
    const bool bo_A_AC = ( exey * o_cx               - eyez * o_cz - ey*ex2 > 0);
    //なぜこうなるのかは、「球とピラミッド（頂点と辺の境界面）」参照
    if (!yz_A && bo_A_AB && bo_A_AC) {
        //頂点Aとの距離で判定
        int_fast64_t length = o_cx_MINUS_ex2 + o_cy2 + o_cz2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //点Bと辺BAの境界面(true:原点側)
    const bool bo_B_BA = (-ezex * o_cx + eyez * o_cy               - ey2*ez > 0);
    //点Bと辺BCの境界面(true:原点側)
    const bool bo_B_BC = (               exey * o_cy - ezex * o_cz - ey2*ex > 0);
    if (!zx_B && bo_B_BA && bo_B_BC) {
        //頂点Bとの距離で判定
        int_fast64_t length = o_cx2 + o_cy_MINUS_ey2 + o_cz2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }
    //点Cと辺CAの境界面(true:原点側)
    const bool bo_C_CA = (-exey * o_cx               + eyez * o_cz - ey*ez2 > 0);
    //点Cと辺CBの境界面
    const bool bo_C_CB = (              -exey * o_cy + ezex * o_cz - ex*ez2 > 0);
    if (!xy_C && bo_C_CA && bo_C_CB) {
        //頂点Cとの距離で判定
        int_fast64_t length = o_cx2 + o_cy2 + o_cz_MINUS_ez2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //A(ex,0,0), B(0,ey,0) を含む斜面に垂直な面より内（原点がある側）
    bool vramp_AB = ((-ex*ey2)*o_cx      + (-ex2*ey)*o_cy      + (ez*(ex2+ey2))*o_cz + (ex2*ey2) > 0);
    //なぜこうなるのかは、「球とピラミッド（斜面との距離で判定する範囲）」参照
    if (!vxy_AB && !bo_A_AB && !bo_B_BA && !vramp_AB) {
        //辺ABとの距離で判定
        // A(ex,0,0), B(0,ey,0)  より
        // 辺ABの直線の式は
        //
        // 点P(o_cx, o_cy, o_cz) と
        // ABを通る直線l (x,y,z) = (ex,0,0) + t(-ex, ey, 0)の距離を考える。
        // 点Pから直線lに垂直に降ろした線の交点を H とすると、点Hは直線l上なので
        // 点H(ex-t*ex, t*ey, 0) であらわされる
        //
        // |PH|^2 = ((ex-t*ex)-o_cx)^2 + (t*ey - o_cy)^2 + (0-o_cz)^2
        //
        // ところで、ABとPHは垂直なので
        // (-ex, ey, 0)・((ex-t*ex)-o_cx, t*ey-o_cy, -o_cz) = 0
        //
        // (-ex*((ex-t*ex)-o_cx)) + (ey*(t*ey-o_cy)) + (0) = 0
        // t=(ey*o_cy-ex*o_cx+ex^2)/(ey^2+ex^2)
        double t = (ey*o_cy - ex*o_cx + ex2) / double(ey2+ex2);
        int_fast64_t length = ((ex-t*ex)-o_cx)*((ex-t*ex)-o_cx) + (t*ey - o_cy)*(t*ey - o_cy) + o_cz2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //B(0,ey,0) C(0,0,ez)  を含む斜面に垂直な面より内（原点がある側）
    bool vramp_BC = ((ex*(ey2+ez2))*o_cx + (-ey*ez2)*o_cy      + (-ey2*ez)*o_cz      + (ey2*ez2) > 0);
    if (!vyz_BC && !bo_B_BC && !bo_C_CB && !vramp_BC) {
        //辺BCとの距離で判定
        double t = (ez*o_cz - ey*o_cy + ey2) / double(ez2+ey2);
        int_fast64_t length = o_cx2 + ((ey-t*ey) - o_cy)*((ey-t*ey) - o_cy) + (t*ez - o_cz)*(t*ez - o_cz);
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //C(0,0,ez) A(ex,0,0)  を含む斜面に垂直な面より内（原点がある側）
    bool vramp_CA = ((-ez2*ex)*o_cx      + (ey*(ez2+ex2))*o_cy + (-ez*ex2)*o_cz      + (ez2*ex2) > 0);
    if (!vzx_CA && !bo_A_AC && !bo_C_CA && !vramp_CA) {
        //辺CAとの距離で判定
        double t = (ex*o_cx - ez*o_cz + ez2) / double(ez2+ex2);
        int_fast64_t length = (t*ex-o_cx)*(t*ex-o_cx) + o_cy2 + ((ez-t*ez) - o_cz)*((ez-t*ez) - o_cz);
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //斜面より外か（原点の無い側）
    int_fast64_t ramp_value = eyez*o_cx + ezex*o_cy + exey*o_cz - ex*ey*ez;
    bool ramp = (ramp_value > 0);
    if (vramp_AB && vramp_BC && vramp_CA && ramp) {
        //面ABCとの距離で判定
        //円の中心から斜面に降ろした垂線の交点(lx,ly,lz)を求める
        //斜面は
        //a*x + b*y + c*z - ex*ey*ez = 0
        //垂線の方程式は
        //(x,y,z) = (o_cx,o_cy,o_cz) + t(a,b,c)
        // x = o_cx + t*a
        // y = o_cy + t*b
        // z = o_cz + t*c
        // tを求める
        // a*(o_cx + t*a) + b*(o_cy + t*b) + c*(o_cz + t*c) - ex*ey*ez = 0
        // t=-(c*o_cz+b*o_cy+a*o_cx-ex*ey*ez)/(c^2+b^2+a^2)
        //斜面の方程式の要素

        //斜面の法線(a,b,c)
        //int_fast64_t a = eyez;
        //int_fast64_t b = ezex;
        //int_fast64_t c = exey;
        //double d = -(ex*ex*ez);
        //double t =-(a*o_cx + b*o_cy +c*o_cz - ex*ey*ez) / double(a*a + b*b + c*c);
        double t = -ramp_value / double(eyez*eyez + ezex*ezex + exey*exey);
        //交点は
        int_fast64_t lx = o_cx + t*eyez;
        int_fast64_t ly = o_cy + t*ezex;
        int_fast64_t lz = o_cz + t*exey;
        //円の中心から、斜面に垂線を下ろしたときの交点との距離(の２乗)
        int_fast64_t length = (o_cx-lx)*(o_cx-lx) + (o_cy-ly)*(o_cy-ly) + (o_cz-lz)*(o_cz-lz);
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    if (xy && yz && zx && !ramp) {
        //三角錐内部
        return true;
    } else {
        _TRACE_("【警告】StgUtil::isHit3D() 数値範囲がオーバーフローして、正しく判定されていません。");
    }

    return false;
}

bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
    //＜球 と 球＞
    //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
    //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
    //(x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
    double d2 = (double)((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) * ((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) +
                (double)((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy)) * ((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy));
    if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
    ) {
        return true;
    } else {
        return false;
    }
}


bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02) {
    //＜AAB と 球＞
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord bx1 = pActor01->_x + pAABox01->_x1;
    const coord bx2 = pActor01->_x + pAABox01->_x2;
    const coord by1 = pActor01->_y + pAABox01->_y1;
    const coord by2 = pActor01->_y + pAABox01->_y2;

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
    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length <= pSphere02->_rr) {
        return true;
    } else {
        return false;
    }
}
bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02   ) {
    const coord aX1 = pActor01->_x + pAAPrism01->_x1;
    const coord aY1 = pActor01->_y + pAAPrism01->_y1;
    const coord aX2 = pActor01->_x + pAAPrism01->_x2;
    const coord aY2 = pActor01->_y + pAAPrism01->_y2;
    const coord bX1 = pActor02->_x + pAABox02->_x1;
    const coord bY1 = pActor02->_y + pAABox02->_y1;
    const coord bX2 = pActor02->_x + pAABox02->_x2;
    const coord bY2 = pActor02->_y + pAABox02->_y2;

    if (aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //この時点でAAB と AAB ならばヒット
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;
        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { // のこりは POS_PRISM_xx_NN のみである
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
    }
    return false;
}
bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  ) {
    //＜プリズム と 球＞
    //MEMO:厳密な当たり判定計算は行っていません。

    //まず、球 対 AAB の判定を行う
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord aX1 = pActor01->_x + pAAPrism01->_x1;
    const coord aY1 = pActor01->_y + pAAPrism01->_y1;
    const coord aX2 = pActor01->_x + pAAPrism01->_x2;
    const coord aY2 = pActor01->_y + pAAPrism01->_y2;
    double square_length = 0; //球の中心とAABの最短距離を二乗した値
    if(o_scx < aX1) {
        square_length += (double)(o_scx - aX1) * (o_scx - aX1);
    }
    if(o_scx > aX2) {
        square_length += (double)(o_scx - aX2) * (o_scx - aX2);
    }
    if(o_scy < aY1) {
        square_length += (double)(o_scy - aY1) * (o_scy - aY1);
    }
    if(o_scy > aY2) {
        square_length += (double)(o_scy - aY2) * (o_scy - aY2);
    }
    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length > pSphere02->_rr) {
        return false;
    }
    //この時点でAAB 対 球でヒット。ここからプリズムでもヒットか検証する

    const int pos = pAAPrism01->_pos_info;
    const double a = pAAPrism01->_a;
    //ワールド座標でのプリズム境界線の切片を求める b = y - ax
    const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

    //予め保持している_vIH_x,_vIH_yを使用して
    //プリズム斜辺と最短距離の円周上のXY座標を求める
    int oppX = o_scx + pAAPrism01->_vIH_x * pSphere02->_r;
    int oppY = o_scy + pAAPrism01->_vIH_y * pSphere02->_r;
    if (pos & POS_PRISM_xx_PP) {
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

    } else if (pos & POS_PRISM_xx_NP) {
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

    } else if (pos & POS_PRISM_xx_PN) {
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

    } else { // のこりは POS_PRISM_xx_NN のみである
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
    return false;
}

bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAAPrism* const pAAPrism02  ) {
    const coord aX = pActor01->_x;
    const coord aY = pActor01->_y;
    const coord bX = pActor02->_x;
    const coord bY = pActor02->_y;

    coord bX1 = bX + pAAPrism02->_x1;
    coord bY1 = bY + pAAPrism02->_y1;
    coord bX2 = bX + pAAPrism02->_x2;
    coord bY2 = bY + pAAPrism02->_y2;
    if (aY + pAAPrism01->_y2 >= bY1 && aY + pAAPrism01->_y1 <= bY2 &&
        aX + pAAPrism01->_x2 >= bX1 && aX + pAAPrism01->_x1 <= bX2)
    {
        //この時点でAAB と AAB ならばヒット
    } else {
        //この時点でAAB と AAB だとしてもヒットしてない
        return false;
    }
    int pos1 = pAAPrism01->_pos_info; //自分の三角形の直角頂点の位置
    double aA = pAAPrism01->_a;       //自分の三角形の斜辺の傾き
    coord aB = aY + pAAPrism01->_b;   //自分の三角形の斜辺の切片
    float aNx = -pAAPrism01->_vIH_x;  //自分の三角形の斜辺の法線ベクトルX要素
    float aNy = -pAAPrism01->_vIH_y;  //自分の三角形の斜辺の法線ベクトルY要素

    int pos2 = pAAPrism02->_pos_info; //自分の三角形の直角頂点の位置
    double bA = pAAPrism02->_a;       //自分の三角形の斜辺の傾き
    coord bB = bY + pAAPrism02->_b;   //自分の三角形の斜辺の切片
    float bNx = -pAAPrism02->_vIH_x;  //自分の三角形の斜辺の法線ベクトルX要素
    float bNy = -pAAPrism02->_vIH_y;  //自分の三角形の斜辺の法線ベクトルY要素

    //自分の直角三角形について、直角頂点を(0, 0) におき、残りの頂点を A(aEx,0), B(0,aEy) とする
    //直角三角形での当たり判定を考えたい（POS_R_TRIANGLE_NN に固定したい）
    const coord aEx = pAAPrism01->_dx;
    const coord aEy = pAAPrism01->_dy;
    const coord aCX = aEx / 2; //自分の三角形の斜辺上の点のX要素
    const coord aCY = aEy / 2; //自分の三角形の斜辺上の点のY要素
    //そこで、自分と相手の直角三角形の位置関係をダイナミックに変換！
    if (pos1 & POS_R_TRIANGLE_Px) {
        //相手直角三角形座標の、X軸平行移動・X座標反転(Y軸反転)
        const coord aX2 = aX + pAAPrism01->_x2;
        const coord tmp_bX2 = bX2;
        bX2 = aX2 - bX1;
        bX1 = aX2 - tmp_bX2;
        //aB bB 切片はそのまま
        //相手直角三角形要素の、X座標反転(Y軸反転)
        aA = -aA;
        bA = -bA;
        aNx = -aNx;
        bNx = -bNx;
        pos2 = StgUtil::POS_R_TRIANGLE_inv_X[pos2];
    } else {
        //X軸平行移動
        const coord aX1 = aX + pAAPrism01->_x1;
        bX1 -= aX1;
        bX2 -= aX1;
    }

    if (pos1 & POS_R_TRIANGLE_xP) {
        //相手直角三角形座標の、Y軸平行移動・Y座標反転(X軸反転)
        const coord aY2 = aY + pAAPrism01->_y2;
        const coord tmp_bY2 = bY2;
        bY2 = aY2 - bY1;
        bY1 = aY2 - tmp_bY2;
        aB  = aY2 - aB;
        bB  = aY2 - bB;
        //相手直角三角形要素の、Y座標反転(X軸反転)
        aA = -aA;
        bA = -bA;
        aNy = -aNy;
        bNy = -bNy;
        pos2 = StgUtil::POS_R_TRIANGLE_inv_Y[pos2];
    } else {
        //Y軸平行移動
        const coord aY1 = aY + pAAPrism01->_y1;
        bY1 -= aY1;
        bY2 -= aY1;
        aB  -= aY1;
        bB  -= aY1;
    }
    coord bCX = bX1 + (pAAPrism02->_dx / 2); //相手の三角形の斜辺上の点のX要素
    coord bCY = bY1 + (pAAPrism02->_dy / 2); //相手の三角形の斜辺上の点のY要素

    //自分の頂点は(0,0)で POS_R_TRIANGLE_NN 固定
    //相手の直角三角形は、それに伴い位置関係が変換された状態
    if (pos2 == POS_R_TRIANGLE_NN) {
        //相手の直角頂点は (bX1, bY1)
        if (bX1 <= 0) {
            if (bY1 <= 0) {
                //位置1
                //自身の直角頂点が、近傍点(0, 0)
                //相手の直角三角形の斜辺の法線ベクトル (bNx, bNy) と
                //相手の直角三角形の斜辺の点 (bCX, bCY) から  近傍点(0, 0) のベクトル(-bCX, -bCY)の
                //内積が負 ならば近傍点(0, 0) が相手の直角三角形の中にある
                //(bNx, bNy)・(-bCX, -bCY) = bNx*(-bCX) + bNy*(bCY)
                if ((bNx*(-bCX) + bNy*(-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //位置4
                if (bX2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //位置7
                return false;
            }
        } else if (bX1 <= aEx) {
            if (bY1 <= 0) {
                //位置2
                if (bY2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //位置5
                //相手の直角頂点が、近傍点(bX1, bY1)
                //自身の直角三角形の斜辺の法線ベクトル (aNx, aNy) と
                //自身の直角三角形の斜辺の点 (aCX, aCY) から  近傍点(bX1, bY1) のベクトル(bX1-aCX, bY1-aCY)の
                //内積が負 ならば近傍点(bX1, bY1) が直角三角形の中にある
                //(aNx, aNy)・(bX1-aCX, bY1-aCY) = aNx*(bX1-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //位置8
                return false;
            }
        } else {
            //位置3 or 6 or 9
            return false;
        }
    } //pos2 == POS_R_TRIANGLE_NN

    if (pos2 == POS_R_TRIANGLE_NP) {
        //相手の直角頂点は (bX1, bY2)
        if (bX1 <= 0) {
            if (bY2 <= 0) {
                //位置1
                return false;
            } else if (bY2 <= aEy) {
                //位置4
                if (bX2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //位置7
                //自身の頂点近傍点(0, aEy)
                //相手の直角三角形の斜辺の法線ベクトル (bNx, bNy) と
                //相手の直角三角形の斜辺の点 (bCX, bCY) から  近傍点(0, aEy) のベクトル(-bCX, aEy-bCY)の
                //内積が負 ならば近傍点(0, aEy) が相手の直角三角形の中にある
                //(bNx, bNy)・(-bCX, aEy-bCY) = bNx*(-bCX) + bNy*(aEy-bCY)
                if ((bNx*(-bCX) + bNy*(aEy-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            }
        } else if (bX1 <= aEx) {
            if (bY2 <= 0) {
                //位置2
                return false;
            } else if (bY2 <= aEy) {
                //位置5
                //相手の頂点近傍点(bX1, bY1)
                //自身の直角三角形の斜辺の法線ベクトル (aNx, aNy) と
                //自身の直角三角形の斜辺の点 (aCX, aCY) から  近傍点(bX1, bY1) のベクトル(bX1-aCX, bY1-aCY)の
                //内積が負 ならば近傍点(bX1, bY1) が直角三角形の中にある
                //(aNx, aNy)・(bX1-aCX, bY1-aCY) = aNx*(bX1-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //位置8
                //位置5と同じ
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            //位置3 or 6or 9
            return false;
        }
    } //pos2 == POS_R_TRIANGLE_NP

    if (pos2 == POS_R_TRIANGLE_PN) {
        //相手の直角頂点は (bX2, bY1)
        if (bX2 <= 0) {
            return false;
        } else if (bX2 <= aEx) {
            if (bY1 <= 0) {
                //位置2
                if (bY2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //位置5
                //相手の頂点近傍点(bX1, bY1)
                //自身の直角三角形の斜辺の法線ベクトル (aNx, aNy) と
                //自身の直角三角形の斜辺の点 (aCX, aCY) から  近傍点(bX1, bY1) のベクトル(bX1-aCX, bY1-aCY)の
                //内積が負 ならば近傍点(bX1, bY1) が直角三角形の中にある
                //(aNx, aNy)・(bX1-aCX, bY1-aCY) = aNx*(bX1-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //位置8
                return false;
            }
        } else {
            if (bY1 <= 0) {
                //位置3
                //自身の頂点近傍点(aEx, 0)
                //相手の直角三角形の斜辺の法線ベクトル (bNx, bNy) と
                //相手の直角三角形の斜辺の点 (bCX, bCY) から  近傍点(aEx, 0) のベクトル(aEx-bCX, -bCY)の
                //内積が負 ならば近傍点(aEx, 0) が相手の直角三角形の中にある
                //(bNx, bNy)・(aEx-bCX, -bCY) = bNx*(aEx-bCX) + bNy*(-bCY)
                if ((bNx*(aEx-bCX) + bNy*(-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //位置6
                //位置5と同じ
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //位置9
                return false;
            }
        }
    } //pos2 == POS_R_TRIANGLE_PN

    if (pos2 == POS_R_TRIANGLE_PP) {
        //相手の直角頂点は (bX2, bY2)
        if (bX2 <= 0) {
            //位置1 or 4 or 7
            return false;
        } else if (bX2 <= aEx) {
            if (bY2 <= 0) {
                //位置2
                return false;
            } else {
                //位置5 or 8
            }
        } else {
            if (bY2 <= 0) {
                //位置3
                return false;
            } else if (bY2 <= aEy) {
                //位置6 or 9
            }
        }

        //位置5 or 6 or 8 or 9
        //まず傾きをきを比較
        // aA < bA の場合、相手三角形の頂点(bX1,bY2) の位置に注目
        // aA > bA の場合、相手三角形の頂点(bX2,bY1) の位置に注目
        // aA = bA の場合、斜辺が平行なのでどっちでもいい
        // 注目の頂点について、
        // A(aEx,0) を含む斜辺の法線に平行な線と
        // B(0,aEy) を含む斜辺の法線に平行な線との間の範囲(範囲Rとする)
        // の内側に相手の頂点があるか無いかで場合わけ
        //
        //A(aEx,0) を含む斜辺の法線に平行な線は、
        //直線の法線 →AB=(-aEx, aEy) に向けたいので
        //-aEx * x + aEy * y + c = 0
        //これが、A(aEx,0)を通るので
        //-aEx * aEx + c = 0
        //c = aEx^2
        //よって
        //-aEx * x + aEy * y + aEx^2 > 0
        //
        //B(0,aEy) を含む斜辺の法線に平行な線は、
        //直線の法線 →BA=(aEx, -aEy) に向けたいので
        //aEx * x - aEy * y + c = 0
        //これが、B(0,aEy) を通るので
        //- aEy * aEy + c = 0
        //c = aEy^2
        //よって
        //aEx * x - aEy * y + aEy^2 > 0

        //領域Rは
        //-aEx * x + aEy * y + aEx^2 > 0
        //aEx * x - aEy * y + aEy^2 > 0
        //の範囲

        const double ex = aEx;
        const double ey = aEy;
        if (aA < bA) {
            //斜辺の傾き（負）が、相手三角形の方がより水平に近い

            //相手三角形の頂点(bX1,bY2) の位置に注目
            if ((-ex*bX1 + ey*bY2 + ex*ex) < 0) {
                //注目の頂点(bX1,bY2)がA(ex,0) を含む斜辺の法線に平行な線の外側
                return false;
            } else if ((ex*bX1 - ey*bY2 + ey*ey) < 0) {
                //注目の頂点(bX1,bY2)がB(0,ey) を含む斜辺の法線に平行な線の外側

                //自身の頂点近傍点(0, aEy)
                //相手の直角三角形の斜辺の法線ベクトル (bNx, bNy) と
                //相手の直角三角形の斜辺の点 (bCX, bCY) から  近傍点(0, aEy) のベクトル(-bCX, aEy-bCY)の
                //内積が負 ならば近傍点(0, aEy) が相手の直角三角形の中にある
                //(bNx, bNy)・(-bCX, aEy-bCY) = bNx*(-bCX) + bNy*(aEy-bCY)
                if ((bNx*(-bCX) + bNy*(aEy-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //注目の頂点(bX1,bY2)が範囲Rの範囲内の場合

                //相手の頂点近傍点(bX1,bY2)
                //自身の直角三角形の斜辺の法線ベクトル (aNx, aNy) と
                //自身の直角三角形の斜辺の点 (aCX, aCY) から  近傍点(bX1,bY2) のベクトル(bX1-aCX, bY2-aCY)の
                //内積が負 ならば近傍点(bX1, bY2) が直角三角形の中にある
                //(aNx, aNy)・(bX1-aCX, bY2-aCY) = aNx*(bX1-aCX) + aNy*(bY2-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY2-aCY)) < 0)  {
                    return true;
                } else {
                    return false;
                }
            }

        } else {
            //斜辺の傾き（負）が、相手三角形の方がより垂直に近い
            //相手三角形の頂点(bX2,bY1) の位置に注目
            if ((-ex*bX2 + ey*bY1 + ex*ex) < 0) {
                //注目の頂点(bX2,bY1)がA(ex,0) を含む斜辺の法線に平行な線の外側

                //自身の頂点近傍点(aEx, 0)
                //相手の直角三角形の斜辺の法線ベクトル (bNx, bNy) と
                //相手の直角三角形の斜辺の点 (bCX, bCY) から  近傍点(aEx, 0) のベクトル(aEx-bCX, -bCY)の
                //内積が負 ならば近傍点(aX2, 0) が相手の直角三角形の中にある
                //(bNx, bNy)・(aEx-bCX, -bCY) = bNx*(aEx-bCX) + bNy*(-bCY)
                if ((bNx*(aEx-bCX) + bNy*(-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else if ((ex*bX2 - ey*bY1 + ey*ey) < 0) {
                //注目の頂点(bX2,bY1)がB(0,ey) を含む斜辺の法線に平行な線の外側

                return false;
            } else {
                //注目の頂点(bX2,bY1)が範囲Rの範囲内の場合

                //相手の頂点近傍点(bX2,bY1)
                //自身の直角三角形の斜辺の法線ベクトル (aNx, aNy) と
                //自身の直角三角形の斜辺の点 (aCX, aCY) から  近傍点(bX2,bY1) のベクトル(bX2-aCX, bY1-aCY)の
                //内積が負 ならば近傍点(bX2, bY1) が直角三角形の中にある
                //(aNx, aNy)・(bX2-aCX, bY1-aCY) = aNx*(bX2-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX2-aCX) + aNy*(bY1-aCY)) < 0)  {
                    return true;
                } else {
                    return false;
                }
            }

        }
    } //pos2 == POS_R_TRIANGLE_PP

    return false;
}

GgafDx::FigureActor* StgUtil::shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int)) {
    if (prm_set_num <= 0) {  return nullptr;  }
    double vx, vy, vz;
    GgafDx::Util::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    coord x = vx * prm_r;
    coord y = vy * prm_r;
    coord z = vz * prm_r;
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
        if (pActor_shot) {
            dispatch_num++;
            pActor_shot->setPosition(prm_x + x,
                                     prm_y + y,
                                     prm_z + z);
            pActor_shot->getLocoVehicle()->setRzRyMvAng(prm_rz, prm_ry);
            pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
            pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
            if (pFunc_call_back_dispatched) {
                pFunc_call_back_dispatched(pActor_shot, dispatch_num, n);
            }
        }
        now_velo *= prm_attenuated;
    }
    return pActor_shot;
}

GgafDx::FigureActor* StgUtil::shotWay001(const GgafDx::GeometricActor* prm_pFrom,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int)) {
    return shotWay001(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDx::FigureActor* StgUtil::shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                       coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int)) {
    angle rz,ry;
    GgafDx::Util::convVectorToRzRy(prm_to_x - prm_from_x,
                                 prm_to_y - prm_from_y,
                                 prm_to_z - prm_from_z,
                                 rz, ry);
    return shotWay001(prm_from_x, prm_from_y, prm_from_z,
                      rz, ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDx::FigureActor* StgUtil::shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way_N,
                                       angle prm_ang_clearance_N,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    if (prm_way_N <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    GgafDx::Util::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDx::GeoElem* paGeo = NEW GgafDx::GeoElem[prm_way_N];
    double vx, vy, vz;
    double tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    for (int i = 0; i < prm_way_N; i++) {
        rz = GgafDx::Util::simplifyAng(paAng_way_N[i]);
        ry = D0ANG;
        GgafDx::Util::convRzRyToVector(rz, ry, vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                       paGeo[i].rz, paGeo[i].ry);
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getLocoVehicle()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
                pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDx::FigureActor* StgUtil::shotWay002(const GgafDx::GeometricActor* prm_pFrom,
                                                   GgafCore::ActorDepository* prm_pDepo_shot,
                                                   coord prm_r,
                                                   int prm_way_N,
                                                   angle prm_ang_clearance_N,
                                                   velo prm_velo_first, acce prm_acce,
                                                   int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                   void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    return shotWay002(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_way_N,
                      prm_ang_clearance_N,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDx::FigureActor* StgUtil::shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int)) {
    if (prm_way_N <= 0 || prm_way_M <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    uint32_t* paUint32_dotmat = NEW uint32_t[prm_way_N];
    GgafDx::Util::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDx::Util::getWayAngle2D(0, prm_way_M, prm_ang_clearance_M, paAng_way_M);
    GgafDx::GeoElem** papaGeo = NEW GgafDx::GeoElem*[prm_way_N];
    double vx, vy, vz;
    double tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    uint32_t dot1,dot2,dot3;
    for (int i = 0; i < prm_way_N; i++) {
        dot1 = prm_paUint32_dotmat1 ? prm_paUint32_dotmat1[i] : 0;
        dot2 = prm_paUint32_dotmat2 ? prm_paUint32_dotmat2[i] : 0;
        dot3 = prm_paUint32_dotmat3 ? prm_paUint32_dotmat3[i] : 0;
        paUint32_dotmat[i] = dot1 | dot2 | dot3;
        if (paUint32_dotmat[i] == 0) {
            papaGeo[i] = nullptr;
            continue;
        }
        rz = GgafDx::Util::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDx::GeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                ry = GgafDx::Util::simplifyAng(paAng_way_M[j]);
                GgafDx::Util::convRzRyToVector(rz, ry, vx, vy, vz);
                tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
                ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
                tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
                papaGeo[i][j].x = (coord)(tx * prm_r);
                papaGeo[i][j].y = (coord)(ty * prm_r);
                papaGeo[i][j].z = (coord)(tz * prm_r);
                GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                               papaGeo[i][j].rz, papaGeo[i][j].ry);
            }
        }
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    int depo_no = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            if (paUint32_dotmat[i] == 0) {
                continue;
            }
            for (int j = 0; j < prm_way_M; j++) {
                if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                    if (prm_paUint32_dotmat1 && (prm_paUint32_dotmat1[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot1->dispatch(n*prm_interval_frames+1);
                        depo_no = 1;
                    } else if (prm_paUint32_dotmat2 && (prm_paUint32_dotmat2[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot2->dispatch(n*prm_interval_frames+1);
                        depo_no = 2;
                    } else if (prm_paUint32_dotmat3 && (prm_paUint32_dotmat3[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot3->dispatch(n*prm_interval_frames+1);
                        depo_no = 3;
                    } else {
                        pActor_shot = nullptr;
                        depo_no = 0;
                    }
                } else {
                    pActor_shot = nullptr;
                    depo_no = 0;
                }
                if (pActor_shot) {
                    dispatch_num++;
                    pActor_shot->setPosition(prm_x + papaGeo[i][j].x,
                                             prm_y + papaGeo[i][j].y,
                                             prm_z + papaGeo[i][j].z);
                    pActor_shot->getLocoVehicle()->setRzRyMvAng(papaGeo[i][j].rz, papaGeo[i][j].ry);
                    pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
                    pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
                    if (pFunc_call_back_dispatched) {
                        pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, depo_no, i, j);
                    }
                }
            }
        }
        now_velo *= prm_attenuated;
    }

    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paAng_way_M);
    GGAF_DELETEARR(paUint32_dotmat);
    for (int i = 0; i < prm_way_N; i++) {
        if (papaGeo[i]) {
            GGAF_DELETEARR(papaGeo[i]);
        }
    }
    GGAF_DELETEARR(papaGeo);

    return pActor_shot;
}


GgafDx::FigureActor* StgUtil::shotWay003(const GgafDx::GeometricActor* prm_pFrom,
                                       GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int)) {
    return shotWay003(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot1, prm_paUint32_dotmat1,
                      prm_pDepo_shot2, prm_paUint32_dotmat2,
                      prm_pDepo_shot3, prm_paUint32_dotmat3,
                      prm_r,
                      prm_way_N, prm_way_M,
                      prm_ang_clearance_N, prm_ang_clearance_M,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}


GgafDx::FigureActor* StgUtil::shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_radial_way_num, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    if (prm_radial_way_num <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way = NEW angle[prm_radial_way_num];
    GgafDx::Util::getRadialAngle2D(0, prm_radial_way_num, paAng_way);
    GgafDx::GeoElem* paGeo = NEW GgafDx::GeoElem[prm_radial_way_num];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RzRy(GgafDx::Util::simplifyAng(prm_rz-D90ANG), prm_ry, matWorldRot);

    double vx, vy, vz;
    double tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    for (int i = 0; i < prm_radial_way_num; i++) {
        GgafDx::Util::convRzRyToVector(expanse_rz, paAng_way[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                       paGeo[i].rz, paGeo[i].ry);
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_radial_way_num; i++) {
            pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getLocoVehicle()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
                pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
//                pActor_shot->_rz = Rz;
//                pActor_shot->_ry = Ry;
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way);
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDx::FigureActor* StgUtil::shotWay004(const GgafDx::GeometricActor* prm_pFrom,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    return shotWay004(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_way, prm_expanse_angle,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}





//ピラミッドと球
//  平面 a*x + b*y + c*z + d = 0
//  点D(x0,y0,z0)
//  点から平面に下ろした足の根元を点H(x,y,z) とすると
//
//  ベクトル HD=(x0-x ,y0-y, z0-z) = t(a,b,c)  (tは実数)  ・・・①
//
//  ①より
//  x0 - x = t*a
//  y0 - y = t*b
//  z0 - z = t*c
//  なので
//  x = x0 - t*a
//  y = y0 - t*b
//  z = z0 - t*c
//
//  を平面の式へ代入
//  a*(x0-t*a) + b*(y0-t*b) + c*(z0-t*c) + d = 0
//
//  これをtについて解くと
//  t = (a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2)  ・・・②
//
//  よって
//  x =  x0 - t*a
//    =  x0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*a
//
//  y = y0 - t*b
//    = y0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*b
//
//  z = z0 - t*c
//    = z0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*c
//
//  また、HDの距離は
//  |HD|= |t(a,b,c)| = |t|*|(a,b,c)| = abs(t)*sqrt(a^2+b^2+c^2)  ・・・③
//
//  ②のtを③へ代入
//
//  |HD| = abs((c*z0+b*y0+a*x0+d)/(c^2+b^2+a^2))*sqrt(a^2+b^2+c^2)
//
//  |HD| = abs(a*x0+b*y0+c*z0+d) / sqrt(a^2+b^2+c^2)



//// 特定の点(a,b,c)を通り、方向ベクトルが(p,q,r)の直線は。
//(x,y,z) = (a,b,c) + t(p,q,r)  (tは媒介変数)
//
//x = a + t*p ・・・ ①
//y = b + t*q ・・・ ②
//z = c + t*r ・・・ ③
//
//t = (x-a) /p = (y-b)/q = (z-c)/r
//
//
//点D(x0,y0,z0)
//点から直線に下ろした足の根元を点H(x,y,z) とすると
//ベクトル HD = (x0-x,y0-y, z0-z)
//    = (x0-(a+t*p), y0-(b+t*q), z0-(c+t*r))  ・・・④
//
//これが、(p,q,r) と直交するので、内積=0
//(x0-(a+t*p), y0-(b+t*q), z0-(c+t*r))・(p,q,r) = 0
//p*(x0-(a+t*p)) + q*(y0-(b+t*q)) + r*(z0-(c+t*r)) = 0
//
//tについて解くと
//
//t=(r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2)
//
//④のt に代入し、したがって HD は
//HD = ( x0-(a+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*p),
//y0-(b+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*q),
//z0-(c+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*r)    )
//
//|HD| = sqrt( (x0-(a+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*p))^2 +
//     (y0-(b+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*q))^2 +
//     (z0-(c+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*r))^2   )
//
//|HD| = sqrt((q^2+p^2)*z0^2+(-2*q*r*y0-2*p*r*x0+(2*b*q+2*a*p)*r-2*c*q^2-2*c*p^2)*z0+(r^2+p^2)*y0^2+
//(-2*p*q*x0-2*b*r^2+2*c*q*r+2*a*p*q-2*b*p^2)*y0+(r^2+q^2)*x0^2+(-2*a*r^2+2*c*p*r-2*a*q^2+2*b*p*q)*x0+(b^2+a^2)*r^2+
//(-2*b*c*q-2*a*c*p)*r+(c^2+a^2)*q^2-2*a*b*p*q+(c^2+b^2)*p^2)/(sqrt(r^2+q^2+p^2))


//点ABを通る直線と点Dの距離
//点 A(a,b,c) B(d,e,f) を通る直線は
//AB = (d-a, e-b, f-c)
//(x,y,z) = (a,b,c) + t(d-a, e-b, f-c)  (tは媒介変数)
//
//x = a + t*(d-a) ・・・ ①
//y = b + t*(e-b) ・・・ ②
//z = c + t*(f-c) ・・・ ③
//
//点D(x0,y0,z0)
//点から直線に下ろした足の根元を点H(x,y,z) とすると
//ベクトル HD = (x0-x,y0-y, z0-z)
//            = (x0-(a+t*(d-a)), y0-(b+t*(e-b)), z0-(c+t*(f-c)))  ・・・④
//
//
//これが、AB=(d-a, e-b, f-c) と直交するので、内積=0
//(x0-(a+t*(d-a)), y0-(b+t*(e-b)), z0-(c+t*(f-c)))・(d-a, e-b, f-c) = 0
//なので
//(x0-(a+t*(d-a)))*(d-a) + (y0-(b+t*(e-b)))*(e-b) + (z0-(c+t*(f-c)))*(f-c) = 0
//
//tについて解くと
//
//t = ((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2)
//
//④の t に代入し、したがって HD は
//HD = ( x0-(a+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(d-a)) ,
//       y0-(b+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(e-b)) ,
//       z0-(c+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(f-c))   )
//
//|HD| = sqrt( (x0-(a+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(d-a)))^2 +
//             (y0-(b+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(e-b)))^2 +
//             (z0-(c+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(f-c)))^2    )
//
//=sqrt(((e^2-2*b*e+d^2-2*a*d+b^2+a^2)*z0^2+(((2*b-2*e)*f+2*c*e-2*b*c)*y0+((2*a-2*d)*f+2*c*d-2*a*c)*x0+
//(2*b*e+2*a*d-2*b^2-2*a^2)*f-2*c*e^2+2*b*c*e-2*c*d^2+2*a*c*d)*z0+(f^2-2*c*f+d^2-2*a*d+c^2+a^2)*y0^2+
//(((2*a-2*d)*e+2*b*d-2*a*b)*x0-2*b*f^2+(2*c*e+2*b*c)*f+(2*a*d-2*c^2-2*a^2)*e-2*b*d^2+2*a*b*d)*y0+
//(f^2-2*c*f+e^2-2*b*e+c^2+b^2)*x0^2+(-2*a*f^2+(2*c*d+2*a*c)*f-2*a*e^2+(2*b*d+2*a*b)*e+(-2*c^2-2*b^2)*d)*x0+(b^2+a^2)*
//f^2+(-2*b*c*e-2*a*c*d)*f+(c^2+a^2)*e^2-2*a*b*d*e+(c^2+b^2)*d^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))
//なんじゃこれ・・・


// 球とピラミッド（斜面との距離で判定する範囲）
//    (1) (a, b, c) が平面の法線ベクトルです。
//
//    (2) |d|/|(a, b, c)| が "平面と原点の距離" になります。つまり、原点から平面に垂線を降ろした時の、垂線の長さです。
//    　但し、|(a, b, c)| = √(a^2+b^2+c^2) (法線ベクトルの長さ) です。
//    　法線ベクトル (a,b,c) が既に規格化されている場合 (|(a,b,c)|=1 の場合) は、単に |d| が "平面と原点の距離" です。
//
//    (3) d の符号は、原点が平面の表側にあるか裏側にあるかに対応しています。
//    　d が正の時は、原点は平面の表側(平面から見て法線ベクトルの方向)にあります。
//    　d が負の時は、原点は平面の裏側(法線ベクトルと逆の方向)にあります。
//    a→=(ax,ay,az),
//    b→=(bx,by,bz)
//
//    内積
//    内積-1）：スカラー値 |a→||b→|cosθ のこと
//    （内積-2）：スカラー値 ax bx + ay by + az bz のこと。
//
//    外積
//    長さが |a→||b→|sinθ で a→ と b→ に垂直なベクトルのこと
//    （外積-2）：(ay bz - az by, az bx - ax bz, ax by - ay bx)という成分で表されるベクトルのこと。
//
//
//    原点に三直角頂点をおき、A(ex,0,0), B(0,ey,0), C(0,0,ez) の三直角三角錐を考え (ex>0, ey>0, ez>0)
//    斜面を底面とした三角柱（高さ無限）の範囲を考える
//
//    斜面の方程式
//    AB→ = (-ex, ey, 0 )
//    AC→ = (-ex, 0 , ez)
//    AB→ｘAC→ = (a,b,c)
//
//    a = ey*ez
//    b = ex*ez
//    c = ey*ex
//
//    ey ez x + ex ez y + ey ex z + d = 0
//    これが、A(ex,0,0)をとおるので、
//
//    d = -ex*ey*ez
//
//    斜面の方程式
//    (ey*ez)*x + (ex*ez)*y + (ey*ex)*z - ex*ey*ez = 0
//    法線 (ey*ez, ex*ez, ey*ex)
//
//    ----------------------------------------------------------
//    A(ex,0,0), B(0,ey,0) を含む斜面に垂直な面を求める
//
//    求める面を
//    va*x + vb*y + vc*z + vd = 0 とする
//    ---------------------------------
//    ＜外積で求める＞
//
//    求める面の法線は(va, vb, vc)
//    求める面の法線は (ey*ez, ex*ez, ey*ex)に垂直でかつ、AB→(-ex, ey, 0 )とも垂直なので
//    (ey*ez, ex*ez, ey*ex) ｘ (-ex, ey, 0 ) = (va, vb, vc)
//
//    (va, vb, vc) =
//    ( - (ey*ex)* ey, (ey*ex)*(-ex) , (ey*ez)*ey - (ex*ez)*(-ex))
//    ( -ex*ey^2, -ex^2*ey , (ey^2+ex^2)*ez)
//
//    -------------
//
//    ＜内積が0で求める＞
//
//    求める面の法線は (ey*ez, ex*ez, ey*ex)に垂直なので
//    (ey*ez, ex*ez, ey*ex)・(va, vb, vc) = 0
//    ey*ez*va + ex*ez*vb + ey*ex*vc = 0        ・・・①
//
//    求める面の法線はAB→(-ex, ey, 0 )とも垂直なので
//    (-ex, ey, 0 )・(va, vb, vc) = 0
//    -ex*va + ey*vb = 0 ・・・②
//
//    ここで 法線ベクトル(va, vb, vc) z成分 vc=1 （z成分法線はせいというのが図よりわかったので）とすると
//
//    ey*ez*va + ex*ez*vb + ey*ex = 0  ・・・①’
//    -ex*va + ey*vb = 0               ・・・②
//
//    va=(ey*vb)/ex を①’へ
//
//    ey*ez*((ey*vb)/ex) + ex*ez*vb + ey*ex = 0
//
//    vb=-(ex^2*ey)/((ey^2+ex^2)*ez)
//    ②へ代入
//
//    -ex*va + ey*(-(ex^2*ey)/((ey^2+ex^2)*ez)) = 0
//    va=-(ex*ey^2)/((ey^2+ex^2)*ez)
//
//    よって法線(va, vb, vc) =
//     (-(ex*ey^2)/((ey^2+ex^2)*ez), -(ex^2*ey)/((ey^2+ex^2)*ez), 1)
//
//    ((ey^2+ex^2)*ez)を掛けて整理
//    (-ex*ey^2, -ex^2*ey, (ey^2+ex^2)*ez)
//
//
//    -----------------------------------------------------
//
//    (-ex*ey^2)*x + (-ex^2*ey)*y + ((ey^2+ex^2)*ez)*z + vd = 0
//    が A(ex,0,0) を通るので
//    (-ex*ey^2)*ex + vd = 0
//    vd=ex^2*ey^2
//
//    よって求めたい平面は
//    (-ex*ey^2)*x + (-ex^2*ey)*y + ((ey^2+ex^2)*ez)*z + (ex^2*ey^2) = 0
//

//    同様にして、
//
//    B(0,ey,0) C(0,0,ez) を含む斜面に垂直な面を求める
//
//    求める面を
//    va*x + vb*y + vc*z + vd = 0 とする
//
//    求める面の法線は (ey*ez, ex*ez, ey*ex)に垂直なので
//    (ey*ez, ex*ez, ey*ex)・(va, vb, vc) = 0
//    ey*ez*va + ex*ez*vb + ey*ex*vc = 0        ・・・①
//
//
//    求める面の法線はBC→(0, -ey, ez)とも垂直なので
//    (0, -ey, ez)・(va, vb, vc) = 0
//    -ey*vb + ez*vc = 0 ・・・②
//
//    ここで 法線ベクトル(va, vb, vc) x成分 va=1 （x成分法線は正というのが図よりわかったので）とすると
//
//    ey*ez + ex*ez*vb + ey*ex*vc = 0     ・・・①’
//    -ey*vb + ez*vc = 0                  ・・・②’
//
//    vb=(ez*vc)/ey を ①’へ代入
//
//    ey*ez + ex*ez*((ez*vc)/ey) + ey*ex*vc = 0
//
//    vc=-(ey^2*ez)/(ex*ez^2+ex*ey^2)
//    ②’へ代入
//    -ey*vb + ez*(-(ey^2*ez)/(ex*ez^2+ex*ey^2)) = 0
//
//    vb=-(ey*ez^2)/(ex*ez^2+ex*ey^2)
//
//    よって法線(va, vb, vc) =
//    (1, -(ey*ez^2)/(ex*ez^2+ex*ey^2), -(ey^2*ez)/(ex*ez^2+ex*ey^2))
//
//    (ex*ez^2+ex*ey^2) を掛けて整理
//
//    (ex*(ez^2+ey^2), -ey*ez^2, -ey^2*ez)
//    -----------------------------------------------------
//
//    (ex*(ez^2+ey^2))*x + (-ey*ez^2)*y + (-ey^2*ez)*z + vd = 0
//    がB(0,ey,0) を通るので、
//    (-ey*ez^2)*ey + vd = 0
//    vd=ey^2*ez^2
//
//    よって求めたい平面は
//
//    (ex*(ez^2+ey^2))*x + (-ey*ez^2)*y + (-ey^2*ez)*z + (ey^2*ez^2) = 0


//    同様にして
//    C(0,0,ez) A(ex,0,0) を含む斜面に垂直な面を求める
//
//    求める面を
//    va*x + vb*y + vc*z + vd = 0 とする
//
//    求める面の法線は (ey*ez, ex*ez, ey*ex)に垂直なので
//    (ey*ez, ex*ez, ey*ex)・(va, vb, vc) = 0
//    ey*ez*va + ex*ez*vb + ey*ex*vc = 0        ・・・①
//
//    求める面の法線はCA→(ex, 0, -ez)とも垂直なので
//    (ex, 0, -ez)・(va, vb, vc) = 0
//    ex*va - ez*vc = 0 ・・・②
//
//    ここで 法線ベクトル(va, vb, vc) y成分 vb=1 （y成分法線は正というのが図よりわかったので）とすると
//
//    ey*ez*va + ex*ez + ey*ex*vc = 0        ・・・①’
//    ex*va - ez*vc = 0                      ・・・②
//
//    va=(ez*vc)/ex  を①’へ代入
//
//    ey*ez*((ez*vc)/ex) + ex*ez + ey*ex*vc = 0
//    vc=-(ex^2*ez)/(ey*ez^2+ex^2*ey)
//    ②へ代入
//    ex*va - ez*(-(ex^2*ez)/(ey*ez^2+ex^2*ey)) = 0
//    va=-(ex*ez^2)/(ey*ez^2+ex^2*ey)
//
//
//    よって法線(va, vb, vc) =
//    (-(ex*ez^2)/(ey*ez^2+ex^2*ey), 1, -(ex^2*ez)/(ey*ez^2+ex^2*ey))
//
//    (ey*ez^2+ex^2*ey) を掛けて整理
//
//    (-ex*ez^2, ey*(ez^2+ex^2), -ex^2*ez)
//
//    -----------------------------------------------------
//    (-ex*ez^2)*x + (ey*(ez^2+ex^2))*y + (-ex^2*ez)*z + vd = 0
//    が C(0,0,ez) を通るので、
//    (-ex^2*ez)*ez + vd = 0
//    vd=ex^2*ez^2
//
//    よって求めたい平面は
//
//    (-ex*ez^2)*x + (ey*(ez^2+ex^2))*y + (-ex^2*ez)*z + ex^2*ez^2 = 0
//   よって斜面を底面とした三角柱（高さ無限）の範囲は
//    (ey*ez)*x + (ex*ez)*y + (ey*ex)*z - ex*ey*ez > 0      斜面
//    (-ex*ey^2)*x       + (-ex^2*ey)*y       + (ez*(ex^2+ey^2))*z + (ex^2*ey^2) > 0
//    (ex*(ey^2+ez^2))*x + (-ey*ez^2)*y       + (ey^2*ez)*z        + (ey^2*ez^2) > 0
//    (-ez^2*ex)*x       + (ey*(ez^2+ex^2))*y + (-ez*ex^2)*z       + (ez^2*ex^2) > 0

//球とピラミッド「頂点と辺の境界面」
//    ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//        原点に三直角頂点をおき、A(ex,0,0), B(0,ey,0), C(0,0,ez) の三直角三角錐を考え (ex>0, ey>0, ez>0)
//        A(ex,0,0), B(0,ey,0) を含むxy平面に垂直な面を求める
//        求める面を
//        va*x + vb*y + vc*z + vd = 0 とする
//
//        法線(va, vb, vc) = (-ey, -ex, 0)  なので
//        -ey*x -ex*y + vd = 0   となり、これがA(ex,0,0)を通るので
//        -ey*ex + vd = 0
//        vd = ex*ey
//
//        よって求める面は
//        -ey*x - ex*y + ex*ey = 0
//
//    -----------
//        B(0,ey,0), C(0,0,ez) を含むyz平面に垂直な面を求める
//        va*x + vb*y + vc*z + vd = 0 とする
//
//        法線(va, vb, vc) = (0, -ez, -ey)  なので
//        -ez*y - ey*z + vd = 0   となり、これがB(0,ey,0)を通るので
//        -ez*ey + vd = 0
//        vd = ey*ez
//
//        よって求める面は
//        -ez*y - ey*z + ey*ez = 0
//
//    ------------------------
//        C(0,0,ez), A(ex,0,0) を含むzx平面に垂直な面を求める
//        va*x + vb*y + vc*z + vd = 0 とする
//
//        法線(va, vb, vc) = (-ez, 0, -ex)  なので
//        -ez*x - ex*z + vd = 0 となり、これがC(0,0,ez)を通るので
//        -ex*ez + vd = 0
//        vd=ez*ex
//
//        よって求める面は
//       -ez*x - ex*z + ez*ex = 0
//    ------------------------

//外積メモ
//     a→=(ax,ay,az),
//     b→=(bx,by,bz)
//    (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)

//    A(ex,0,0), B(0,ey,0), C(0,0,ez)
//
//    ＜点Bと辺BAの境界面＞
//    斜面の方程式
//    (ey*ez)*x + (ex*ez)*y + (ey*ex)*z - ex*ey*ez = 0
//    より、
//
//    B(0,ey,0)を通り斜面法線 (ey*ez, ex*ez, ey*ex) に平行な線であるので、
//    (x,y,z) = (0,ey,0) + t(ey*ez, ex*ez, ey*ex)  ・・・①
//
//    A(ex,0,0)を通り面zx に平行な（境界の）線その１は
//    (x,y,z) = (0,ey,0) + t(0, 0, -1)  ・・・②
//
//    ①②を含む面を求める
//    この面の法線を(a,b,c) とすると
//    外積は垂直より
//    (ey*ez, ex*ez, ey*ex)ｘ(0, 0, -1) = (-ex*ez, ey*ez, 0)
//
//    -ex*ez * x + ey*ez * y + d = 0
//    これが点B(0,ey,0)を通るので
//    d = -ey^2*ez
//
//    求める面は
//    -ex*ez * x + ey*ez * y - ey^2*ez = 0    ・・・点Bと辺BAの境界面
//    ------------------------------------------------
//    ＜点Bと辺BCの境界面＞
//    (x,y,z) = (ex,0,0) + t(ey*ez, ex*ez, ey*ex)  ・・・①
//    B(0,ey,0)を通り面zx に平行な（境界の）線その２は
//    (x,y,z) = (ex,0,0) + t(-1, 0, 0)  ・・・②
//    ①②を含む面を求める
//    この面の法線を(a,b,c) とすると
//    外積は垂直より
//    (-1, 0, 0)ｘ(ey*ez, ex*ez, ey*ex) = (0, ey*ex, -ex*ez)
//
//    ey*ex * y - ex*ez * z + d = 0
//
//    これが点B(0,ey,0)を通るので
//    d = -ey^2*ex
//
//    求める面は
//    ey*ex * y - ex*ez * z - ey^2*ex = 0   ・・・点Bと辺BCの境界面
//
//
//    ------------------------------------------------
//    ＜点Aと辺ABの境界面＞
//    外積は垂直よりこの面の法線ベクトルは
//    (0, 0, -1)ｘ(ey*ez, ex*ez, ey*ex) =  (ex*ez, -ey*ez, 0)
//
//    ex*ez * x - ey*ez * y + d = 0
//    これが点A(ex,0,0)を通るので
//    d = -ex^2*ez
//
//    求める面は
//    ex*ez * x - ey*ez * y - ex^2*ez = 0   ・・・点Aと辺ABの境界面
//    ------------------------------------------------
//    ＜点Aと辺ACの境界面＞
//    外積は垂直よりこの面の法線ベクトルは
//    (ey*ez, ex*ez, ey*ex)ｘ(0, -1, 0) = (ey*ex, 0, -ey*ez)
//
//    ey*ex * x - ey*ez * z + d = 0
//    これが点A(ex,0,0)を通るので
//    d = -ey*ex^2
//
//    求める面は
//    ey*ex * x - ey*ez * z - ey*ex^2 = 0   ・・・点Aと辺ACの境界面
//
//
//    ------------------------------------------------
//    ＜点Cと辺CAの境界面＞
//    外積は垂直よりこの面の法線ベクトルは
//    (0, -1, 0)ｘ(ey*ez, ex*ez, ey*ex) = (-ey*ex, 0, ey*ez)
//    -ey*ex * x + ey*ez * z + d = 0
//    これが点 C(0,0,ez) を通るので
//    d = -ey*ez^2
//    求める面は
//    -ey*ex * x + ey*ez * z -ey*ez^2 = 0  ・・・点Cと辺CAの境界面
//    ------------------------------------------------
//    ＜点Cと辺CBの境界面＞
//    外積は垂直よりこの面の法線ベクトルは
//    (ey*ez, ex*ez, ey*ex)ｘ(-1, 0, 0) = (0, -ey*ex, ex*ez)
//    -ey*ex * y + ex*ez * z + d = 0
//    これが点 C(0,0,ez) を通るので
//    d = -ex*ez^2
//    求める面は
//    -ey*ex * y + ex*ez * z - ex*ez^2 = 0    ・・・点Cと辺CBの境界面
//
//    ex*ez * x - ey*ez * y             - ex^2*ez = 0   ・・・点Aと辺ABの境界面
//    ey*ex * x             - ey*ez * z - ey*ex^2 = 0   ・・・点Aと辺ACの境界面
//
//   -ex*ez * x + ey*ez * y             - ey^2*ez = 0    ・・・点Bと辺BAの境界面
//                ey*ex * y - ex*ez * z - ey^2*ex = 0    ・・・点Bと辺BCの境界面
//
//   -ey*ex * x             + ey*ez * z - ey*ez^2 = 0    ・・・点Cと辺CAの境界面
//               -ey*ex * y + ex*ez * z - ex*ez^2 = 0    ・・・点Cと辺CBの境界面
