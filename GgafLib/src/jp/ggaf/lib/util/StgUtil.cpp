#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/GgafLibConfig.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker2D.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

bool StgUtil::_was_StgUtil_inited_flg = false;
float StgUtil::ROOT_1_MINUS_XX[1000];
uint32_t StgUtil::BITNUM[33];

void StgUtil::init() {
    GgafDxUtil::init();
    if (StgUtil::_was_StgUtil_inited_flg) {
        return;
    }

    //ROOT_1_MINUS_XXの設定
    for (int i = 0; i < 1000; i++) {
        StgUtil::ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }


    StgUtil::BITNUM[ 0] = 0;
    StgUtil::BITNUM[ 1] = (0x1);            //0b 00000000 00000000 00000000 00000001
    StgUtil::BITNUM[ 2] = (0x2);            //0b 00000000 00000000 00000000 00000010
    StgUtil::BITNUM[ 3] = (0x4);            //0b 00000000 00000000 00000000 00000100
    StgUtil::BITNUM[ 4] = (0x8);            //0b 00000000 00000000 00000000 00001000
    StgUtil::BITNUM[ 5] = (0x10);           //0b 00000000 00000000 00000000 00010000
    StgUtil::BITNUM[ 6] = (0x20);           //0b 00000000 00000000 00000000 00100000
    StgUtil::BITNUM[ 7] = (0x40);           //0b 00000000 00000000 00000000 01000000
    StgUtil::BITNUM[ 8] = (0x80);           //0b 00000000 00000000 00000000 10000000
    StgUtil::BITNUM[ 9] = (0x100);          //0b 00000000 00000000 00000001 00000000
    StgUtil::BITNUM[10] = (0x200);          //0b 00000000 00000000 00000010 00000000
    StgUtil::BITNUM[11] = (0x400);          //0b 00000000 00000000 00000100 00000000
    StgUtil::BITNUM[12] = (0x800);          //0b 00000000 00000000 00001000 00000000
    StgUtil::BITNUM[13] = (0x1000);         //0b 00000000 00000000 00010000 00000000
    StgUtil::BITNUM[14] = (0x2000);         //0b 00000000 00000000 00100000 00000000
    StgUtil::BITNUM[15] = (0x4000);         //0b 00000000 00000000 01000000 00000000
    StgUtil::BITNUM[16] = (0x8000);         //0b 00000000 00000000 10000000 00000000
    StgUtil::BITNUM[17] = (0x10000);        //0b 00000000 00000001 00000000 00000000
    StgUtil::BITNUM[18] = (0x20000);        //0b 00000000 00000010 00000000 00000000
    StgUtil::BITNUM[19] = (0x40000);        //0b 00000000 00000100 00000000 00000000
    StgUtil::BITNUM[20] = (0x80000);        //0b 00000000 00001000 00000000 00000000
    StgUtil::BITNUM[21] = (0x100000);       //0b 00000000 00010000 00000000 00000000
    StgUtil::BITNUM[22] = (0x200000);       //0b 00000000 00100000 00000000 00000000
    StgUtil::BITNUM[23] = (0x400000);       //0b 00000000 01000000 00000000 00000000
    StgUtil::BITNUM[24] = (0x800000);       //0b 00000000 10000000 00000000 00000000
    StgUtil::BITNUM[25] = (0x1000000);      //0b 00000001 00000000 00000000 00000000
    StgUtil::BITNUM[26] = (0x2000000);      //0b 00000010 00000000 00000000 00000000
    StgUtil::BITNUM[27] = (0x4000000);      //0b 00000100 00000000 00000000 00000000
    StgUtil::BITNUM[28] = (0x8000000);      //0b 00001000 00000000 00000000 00000000
    StgUtil::BITNUM[29] = (0x10000000);     //0b 00010000 00000000 00000000 00000000
    StgUtil::BITNUM[30] = (0x20000000);     //0b 00100000 00000000 00000000 00000000
    StgUtil::BITNUM[31] = (0x40000000);     //0b 01000000 00000000 00000000 00000000
    StgUtil::BITNUM[32] = (0x80000000);     //0b 10000000 00000000 00000000 00000000

    StgUtil::_was_StgUtil_inited_flg = true;
}

GgafDxChecker* StgUtil::createChecker(GgafDxGeometricActor* prm_pActor) {
    if (CONFIG::IS_HIT_CHECK_3D) {
        return NEW CollisionChecker3D(prm_pActor);
    } else {
        return NEW CollisionChecker2D(prm_pActor);
    }
}

bool StgUtil::isHit3D(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                    const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
    //＜球 と 球＞
    //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
    //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
    double d2 = (double)((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) * ((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) +
                (double)((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy)) * ((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy)) +
                (double)((pActor02->_z+pSphere02->_cz) - (pActor01->_z+pSphere01->_cz)) * ((pActor02->_z+pSphere02->_cz) - (pActor01->_z+pSphere01->_cz));
    if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
    ) {
        return true;
    } else {
        return false;
    }
}



bool StgUtil::isHit3D(const GgafDxCore::GgafDxGeometricActor* pActor01, const ColliAABox*  pAABox01,
                    const GgafDxCore::GgafDxGeometricActor* pActor02, const ColliSphere* pSphere02) {
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
    //↑の判定が全てハズレて、square_length == 0 ならば、
    //球の中心が、BOX内にあるという意味になる。

    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length <= pSphere02->_rr) {
        return true;
    } else {
        return false;
    }
}


 bool StgUtil::isHit3D(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                     const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliAABox*   const pAABox02     ) {
    //＜プリズム と AAB＞
    const int aX1 = pActor01->_x + pAAPrism01->_x1;
    const int aY1 = pActor01->_y + pAAPrism01->_y1;
    const int aZ1 = pActor01->_z + pAAPrism01->_z1;
    const int aX2 = pActor01->_x + pAAPrism01->_x2;
    const int aY2 = pActor01->_y + pAAPrism01->_y2;
    const int aZ2 = pActor01->_z + pAAPrism01->_z2;

    const int bX1 = pActor02->_x + pAABox02->_x1;
    const int bY1 = pActor02->_y + pAABox02->_y1;
    const int bZ1 = pActor02->_z + pAABox02->_z1;
    const int bX2 = pActor02->_x + pAABox02->_x2;
    const int bY2 = pActor02->_y + pAABox02->_y2;
    const int bZ2 = pActor02->_z + pAABox02->_z2;

    if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //この時点でAAB と AAB ならばヒット
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
            //ワールド座標でのプリズム境界線の切片を求める b = y - ax
            const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

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



bool StgUtil::isHit3D(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                    const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere*  const pSphere02  ) {
    //＜プリズム と 球＞
    //MEMO:厳密な当たり判定計算は行っていません。


    //AAB 対 球でまず判定する
    if (isHit3D(pActor01, (ColliAABox*)pAAPrism01,
              pActor02, pSphere02             ) ) {
        //この時点でAAB 対 球でヒット。ここからプリズムでもヒットか検証する
        const int aX1 = pActor01->_x + pAAPrism01->_x1;
        const int aY1 = pActor01->_y + pAAPrism01->_y1;
        const int aZ1 = pActor01->_z + pAAPrism01->_z1;
        const int aX2 = pActor01->_x + pAAPrism01->_x2;
        const int aY2 = pActor01->_y + pAAPrism01->_y2;
        const int aZ2 = pActor01->_z + pAAPrism01->_z2;
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        if (pos & POS_PRISM_XY) { //XY平面スライスのプリズム
            //ワールド座標でのプリズム境界線の切片を求める b = y - ax
            const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

            int oppX, oppY;
            const int bZc = pActor02->_z + pSphere02->_cz; //球の中心Z座標
            if (aZ1 < bZc && bZc < aZ2) {
                //球の中心Z座標がプリズムのZ幅範囲内ならば、予め保持している_vIH_x,_vIH_yを使用して
                //プリズム斜辺と最短距離の円周上のXY座標を求める
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_x * pSphere02->_r;
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_y * pSphere02->_r;
            } else if (bZc >= aZ2) {
                //球の中心Z座標がプリズムのZ幅範囲外の場合
                //離れる距離に応じて、球側の半径(pSphere02->_r)を小さくして差分を計算
                //小さくする割合は ROOT_1_MINUS_XX (1/4円の解のテーブル配列）を使用。
                //                 |
                //                 ＼
                //        ┌───┐ `─
                // z- ←  │      │  → z+
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_x * r;
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_y * r;
            } else { //if (aZ1 >= bZc) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_x * r;
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_y * r;
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
            const int b = ((pActor01->_z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_y+pAAPrism01->_cy)) + pAAPrism01->_b;
            int oppY, oppZ;

            const int bXc = pActor02->_x + pSphere02->_cx;
            if (aX1 < bXc && bXc < aX2) {
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_x * pSphere02->_r;
                oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_y * pSphere02->_r;
            } else {
                if (bXc >= aX2) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                    oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_x * r;
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_y * r;
                } else if (aX1 >= bXc) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                    oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_x * r;
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_y * r;
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
            const int b = ((pActor01->_x+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_z+pAAPrism01->_cz)) + pAAPrism01->_b;
            int oppZ,oppX;
            const int bYc = pActor02->_y + pSphere02->_cy;
            if (aY1 < bYc && bYc < aY2) {
                oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_x * pSphere02->_r;
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_y * pSphere02->_r;
            } else {
                if (bYc >= aY2) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_x * r;
                    oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_y * r;
                } else if (aY1 >= bYc) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_x * r;
                    oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_y * r;
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


bool StgUtil::isHit3D(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                      const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliAABox*     const pAABox02     ) {
    //ピラミッドとBOX
    const int aX1 = pActor01->_x + pAAPyramid01->_x1;
    const int aY1 = pActor01->_y + pAAPyramid01->_y1;
    const int aZ1 = pActor01->_z + pAAPyramid01->_z1;
    const int aX2 = pActor01->_x + pAAPyramid01->_x2;
    const int aY2 = pActor01->_y + pAAPyramid01->_y2;
    const int aZ2 = pActor01->_z + pAAPyramid01->_z2;

    float a = pAAPyramid01->_s_nvx;
    float b = pAAPyramid01->_s_nvy;
    float c = pAAPyramid01->_s_nvz;
    //斜面と対角線の交点
    const int px = pActor01->_x + pAAPyramid01->_l_px;
    const int py = pActor01->_y + pAAPyramid01->_l_py;
    const int pz = pActor01->_z + pAAPyramid01->_l_pz;

    const int bX1 = pActor02->_x + pAABox02->_x1;
    const int bY1 = pActor02->_y + pAABox02->_y1;
    const int bZ1 = pActor02->_z + pAABox02->_z1;
    const int bX2 = pActor02->_x + pAABox02->_x2;
    const int bY2 = pActor02->_y + pAABox02->_y2;
    const int bZ2 = pActor02->_z + pAABox02->_z2;


    if (aX2 >= bX1 && aX1 <= bX2 && aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2) {
        //この時点でAAB と AAB ならばヒット

        //ピラミッド斜面に対してピラミッド側のBOX領域内で、相手BOXの最近傍点を求める
        //
        const int pos_pyramid = pAAPyramid01->_pos_pyramid;

        int nnx, nny, nnz; //BOX内最近傍点
        if (pos_pyramid & POS_PYRAMID_p__) {
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
        if (pos_pyramid & POS_PYRAMID__p_) {
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

        if (pos_pyramid & POS_PYRAMID___p) {
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

bool StgUtil::isHit3D(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                      const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere*    const pSphere02  ) {


// 2条の距離をいかの場合わけで設定
//
//  a
//	if(o_scx < b_x1) {
//		square_length += (double)(o_scx - b_x1) * (o_scx - b_x1);
//	}

//	b
//	if(o_scx > b_x2) {
//		square_length += (double)(o_scx - b_x2) * (o_scx - b_x2);
//	}

//          a         b      c        d      e
//    -------------><---><---------><---><-----------------
//              ,─、
//             │  │   ,─、
//              `─'  _│_ │
//                  |＼ `─'
//                  |  ＼   ＼
//                  |    ＼  r＼
//                  |      ＼   ＼
//                  |        ＼    ,─、
//                  |          ＼ │| │
//                  |            ＼`+-'
//                  ----------------,─、
//              ,─、              │  │
//             │  │               `─'
//              `─'

    //まずBOXと球で当たり判定を行う
    //＜AAB と 球＞
    coord o_cx = pActor02->_x + pSphere02->_cx;
    coord o_cy = pActor02->_y + pSphere02->_cy;
    coord o_cz = pActor02->_z + pSphere02->_cz;
    coord o_r = pSphere02->_r;
    coord b_x1 = pActor01->_x + pAAPyramid01->_x1;
    coord b_x2 = pActor01->_x + pAAPyramid01->_x2;
    coord b_y1 = pActor01->_y + pAAPyramid01->_y1;
    coord b_y2 = pActor01->_y + pAAPyramid01->_y2;
    coord b_z1 = pActor01->_z + pAAPyramid01->_z1;
    coord b_z2 = pActor01->_z + pAAPyramid01->_z2;

    float a = pAAPyramid01->_s_nvx;
    float b = pAAPyramid01->_s_nvy;
    float c = pAAPyramid01->_s_nvz;


    coord lpx = pActor01->_z + pAAPyramid01->_l_px;
    coord lpy = pActor01->_z + pAAPyramid01->_l_py;
    coord lpz = pActor01->_z + pAAPyramid01->_l_pz;
    int pos_pyramid = pAAPyramid01->_pos_pyramid;

    double square_length = 0; //球の中心とAABの最短距離を二乗した値
    int sgn_x_spos, sgn_y_spos, sgn_z_spos;

    if (GgafDxCore::GgafDxInput::isPressedKey(DIK_Z)) {
        _TRACE_("kitayo");
    }



    //原点に三直角頂点をおき(POS_PYRAMID_nnn)、
    // (ex,0,0), (0,ey,0), (0,0,ez) の三直角三角錐で考えたいので、
    // 座標変換

    //三直角頂点の向きをPOS_PYRAMID_nnnに変換
    if (pos_pyramid & POS_PYRAMID_p__) {
        //x軸反転
        o_cx = -o_cx;
        b_x1 = -b_x1;
        b_x2 = -b_x2;
        a = -a;
    }

    if (pos_pyramid & POS_PYRAMID__p_) {
        //y軸反転
        o_cy = -o_cy;
        b_y1 = -b_y1;
        b_y2 = -b_y2;
        b = -b;
    }

    if (pos_pyramid & POS_PYRAMID___p) {
        //z軸反転
        o_cz = -o_cz;
        b_z1 = -b_z1;
        b_z2 = -b_z2;
        c = -c;
    }
    //三直角頂点の座標を(0,0,0) に変換
    //POS_PYRAMID_nnnなので三直角頂点（b_x1, b_y1, b_z2）
    coord offset_x = -b_x1;
    coord offset_y = -b_y1;
    coord offset_z = -b_z1;

    o_cx += offset_x;
    o_cy += offset_y;
    o_cz += offset_z;
    b_x1 += offset_x;
    b_x2 += offset_x;
    b_y1 += offset_y;
    b_y2 += offset_y;
    b_z1 += offset_z;
    b_z2 += offset_z;


    coord ex = b_x2;
    coord ey = b_y2;
    coord ez = b_z2;

///////////////////////こここここ
///
///  _r * x; の r を距離に
///
///
///
//  円の中心から、斜面に垂線を下ろしたときの交点を求める
//
    //点と斜面の距離を半径にする
//    float a = pAAPyramid01->_s_nvx;
//    float b = pAAPyramid01->_s_nvy;
//    float c = pAAPyramid01->_s_nvz;

    //円の中心から斜面に降ろした垂線
    //(x,y,z) = (o_cx,o_cy,o_cz) + t(a,b,c)  ・・・①
    //法線ベクトル (a, b, c)、点 ( lpx, lpy, lpz )を通る面は
    //a*(x-lpx) + b*(y-lpy) + c*(z-lpz) = 0  ・・・②
    //①を②に代入して、ｔを求める
    //a*((o_cx+t*a)-lpx) + b*((o_cy+t*b)-lpy) + c*((o_cz+t*c)-lpz) = 0
    //t=-(c*o_cz+b*o_cy+a*o_cx-c*lpz-b*lpy-a*lpx)/(c^2+b^2+a^2)
    double t =-(c*o_cz+b*o_cy+a*o_cx-c*lpz-b*lpy-a*lpx)/(c*c+b*b+a*a);
    //交点は
    coord cx = o_cx + t*a;
    coord cy = o_cy + t*b;
    coord cz = o_cz + t*c;


    //円の中心から、斜面に垂線を下ろしたときの交点の距離
    coord d = UTIL::getDistance(o_cx, o_cy, o_cz, cx, cy, cz);

//    //円の中心から、斜面に垂線を下ろしたときの交点のベクトルを成分わけ
//    // (vx, vy, vz) = (o_cx, o_cy, o_cz) + d(-a,-b,-c); ???
//
//    coord dvx = o_cx + d*-a;
//    coord dvy = o_cy + d*-b;
//    coord dvz = o_cz + d*-c;


//<MEMO>
//    a*(x-x0)+b*(y-y0)+c*(z-z0)=0
//    a*x*-a*x0 + b*y-b*y0 + c*z-c*z0 = 0
//    a*x + b*y + c*z + (-a*x0 - b*y0 - c*z0) = 0


//    a*(x-x0)+b*(y-y0)+c*(z-z0)=0
//    a*x*-a*x0 + b*y-b*y0 + c*z-c*z0 = 0
//    a*x + b*y + c*z + (-a*x0 - b*y0 - c*z0) = 0
//

///////////////////////////////////////////////////////////////////////////////
//    //空間分割
//
//    //原点に三直角頂点をおき、(ex,0,0), (0,ey,0), (0,0,ez) の三直角三角錐を考え
//    //斜面を底面とした三角柱（高さ無限）の範囲を考える
//
//

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
//    (ex*(ez^2+ey^2))*x + (-ey*ez^2)*y + (ey^2*ez)*z + vd = 0
//    がB(0,ey,0) を通るので、
//    (-ey*ez^2)*ey + vd = 0
//    vd=ey^2*ez^2
//
//    よって求めたい平面は
//
//    (ex*(ez^2+ey^2))*x + (-ey*ez^2)*y + (ey^2*ez)*z + (ey^2*ez^2) = 0


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

    //斜面より外か（原点の無い側）
    bool ramp = ((ey*ez)*o_cx + (ex*ez)*o_cy + (ey*ex)*o_cz - ex*ey*ez > 0);
    //A(ex,0,0), B(0,ey,0) を含む斜面に垂直な面より内（原点がある側）
    bool vramp_xy = ((-ex*ey*ey)*o_cx       + (-ex*ex*ey)*o_cy       + (ez*(ex*ex+ey*ey))*o_cz + (ex*ex*ey*ey) > 0);
    //B(0,ey,0) C(0,0,ez)  を含む斜面に垂直な面より内（原点がある側）
    bool vramp_yz = ((ex*(ey*ey+ez*ez))*o_cx + (-ey*ez*ez)*o_cy       + (ey*ey*ez)*o_cz        + (ey*ey*ez*ez) > 0);
    //C(0,0,ez) A(ex,0,0)  を含む斜面に垂直な面より内（原点がある側）
    bool vramp_zx = ((-ez*ez*ex)*o_cx       + (ey*(ez*ez+ex*ex))*o_cy + (-ez*ex*ex)*o_cz       + (ez*ez*ex*ex) > 0);
    //xy平面より内(第一象限側)か
    bool xy = (o_cz > 0);
    //yz平面より内(第一象限側)か
    bool yz = (o_cx > 0);
    //zx平面より内(第一象限側)か
    bool zx = (o_cy > 0);



    //未完成・・・

    //(a)
    if(o_cx < b_x1) {
        square_length += (double)(o_cx - b_x1) * (o_cx - b_x1);
    }
    if (b_x1 <= o_cx && o_cx <= b_x2) {
        double dx = d * cos(pAAPyramid01->_rad_xy);
        square_length += (dx * dx);
    }
    //(e)
    if(o_cx > b_x2) {
        square_length += (double)(o_cx - b_x2) * (o_cx - b_x2);
    }



    if(o_cy < b_y1) {
        square_length += (double)(o_cy - b_y1) * (o_cy - b_y1);
    }
    if (b_y1 <= o_cy && o_cy <= b_y2) {
        double dy = d * cos(pAAPyramid01->_rad_yz);
        square_length += (dy* dy);
    }
    if(o_cy > b_y2) {
        square_length += (double)(o_cy - b_y2) * (o_cy - b_y2);
    }

    if(o_cz < b_z1) {
        square_length += (double)(o_cz - b_z1) * (o_cz - b_z1);
    }
    if (b_z1 <= o_cz && o_cz <= b_z2) {
        double dz = d * cos(pAAPyramid01->_rad_zx);
        square_length += (dz* dz);
    }
    if(o_cz > b_z2) {
        square_length += (double)(o_cz - b_z2) * (o_cz - b_z2);
    } else {

    }
    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length <= pSphere02->_rr) {
        //OK、まずBOXと球でヒット、第一条件クリア
        return true;
    } else {
        return false;
    }


    return false;
}

bool StgUtil::isHit2D(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                      const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
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


bool StgUtil::isHit2D(const GgafDxCore::GgafDxGeometricActor* pActor01, const ColliAABox*  pAABox01,
                    const GgafDxCore::GgafDxGeometricActor* pActor02, const ColliSphere* pSphere02) {
    //＜AAB と 球＞
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
//    const coord o_scz = pActor02->_z + pSphere02->_cz;
    const coord bx1 = pActor01->_x + pAABox01->_x1;
    const coord bx2 = pActor01->_x + pAABox01->_x2;
    const coord by1 = pActor01->_y + pAABox01->_y1;
    const coord by2 = pActor01->_y + pAABox01->_y2;
//    const coord bz1 = pActor01->_z + pAABox01->_z1;
//    const coord bz2 = pActor01->_z + pAABox01->_z2;

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

//    if(o_scz < bz1) {
//        square_length += (double)(o_scz - bz1) * (o_scz - bz1);
//    }
//    if(o_scz > bz2) {
//        square_length += (double)(o_scz - bz2) * (o_scz - bz2);
//    }
    //↑の判定が全てハズレて、square_length == 0 ならば、
    //球の中心が、BOX内にあるという意味になる。

    //square_lengthが球の半径（の二乗）よりも短ければ衝突している
    if (square_length <= pSphere02->_rr) {
        return true;
    } else {
        return false;
    }
}

GgafDxFigureActor* StgUtil::shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int)) {
    if (prm_set_num <= 0) {  return nullptr;  }
    float vx, vy, vz;
    GgafDxUtil::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    coord x = vx * prm_r;
    coord y = vy * prm_r;
    coord z = vz * prm_r;
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
        if (pActor_shot) {
            dispatch_num++;
            pActor_shot->setPosition(prm_x + x,
                                     prm_y + y,
                                     prm_z + z);
            pActor_shot->getKuroko()->setRzRyMvAng(prm_rz, prm_ry);
            pActor_shot->getKuroko()->setMvVelo(now_velo);
            pActor_shot->getKuroko()->setMvAcce(now_acce);
            if (pFunc_call_back_dispatched) {
                pFunc_call_back_dispatched(pActor_shot, dispatch_num, n);
            }
        }
        now_velo *= prm_attenuated;
    }
    return pActor_shot;
}

GgafDxFigureActor* StgUtil::shotWay001(const GgafDxGeometricActor* prm_pFrom,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int)) {
    return shotWay001(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxFigureActor* StgUtil::shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                       coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int)) {
    angle rz,ry;
    GgafDxUtil::convVectorToRzRy(prm_to_x - prm_from_x,
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

GgafDxFigureActor* StgUtil::shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way_N,
                                       angle prm_ang_clearance_N,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    if (prm_way_N <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way_N];
    float vx, vy, vz;
    float tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    for (int i = 0; i < prm_way_N; i++) {
        rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        ry = D0ANG;
        GgafDxUtil::convRzRyToVector(rz, ry, vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
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

GgafDxCore::GgafDxFigureActor* StgUtil::shotWay002(const GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                   GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                   coord prm_r,
                                                   int prm_way_N,
                                                   angle prm_ang_clearance_N,
                                                   velo prm_velo_first, acce prm_acce,
                                                   int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                   void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxFigureActor*, int, int, int)) {
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

GgafDxFigureActor* StgUtil::shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int, int, int)) {
    if (prm_way_N <= 0 || prm_way_M <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    uint32_t* paUint32_dotmat = NEW uint32_t[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDxUtil::getWayAngle2D(0, prm_way_M, prm_ang_clearance_M, paAng_way_M);
    GgafDxGeoElem** papaGeo = NEW GgafDxGeoElem*[prm_way_N];
    float vx, vy, vz;
    float tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
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
        rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDxGeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                ry = GgafDxUtil::simplifyAng(paAng_way_M[j]);
                GgafDxUtil::convRzRyToVector(rz, ry, vx, vy, vz);
                tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
                ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
                tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
                papaGeo[i][j].x = (coord)(tx * prm_r);
                papaGeo[i][j].y = (coord)(ty * prm_r);
                papaGeo[i][j].z = (coord)(tz * prm_r);
                GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                             papaGeo[i][j].rz, papaGeo[i][j].ry);
            }
        }
    }
    GgafDxFigureActor* pActor_shot = nullptr;
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
                        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot1->dispatch(n*prm_interval_frames+1);
                        depo_no = 1;
                    } else if (prm_paUint32_dotmat2 && (prm_paUint32_dotmat2[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot2->dispatch(n*prm_interval_frames+1);
                        depo_no = 2;
                    } else if (prm_paUint32_dotmat3 && (prm_paUint32_dotmat3[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot3->dispatch(n*prm_interval_frames+1);
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
                    pActor_shot->getKuroko()->setRzRyMvAng(papaGeo[i][j].rz, papaGeo[i][j].ry);
                    pActor_shot->getKuroko()->setMvVelo(now_velo);
                    pActor_shot->getKuroko()->setMvAcce(now_acce);
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


GgafDxFigureActor* StgUtil::shotWay003(const GgafDxGeometricActor* prm_pFrom,
                                       GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int, int, int)) {
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


GgafDxFigureActor* StgUtil::shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_radial_way_num, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    if (prm_radial_way_num <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way = NEW angle[prm_radial_way_num];
    GgafDxUtil::getRadialAngle2D(0, prm_radial_way_num, paAng_way);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_radial_way_num];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RzRy(GgafDxUtil::simplifyAng(prm_rz-D90ANG), prm_ry, matWorldRot);

    float vx, vy, vz;
    float tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    for (int i = 0; i < prm_radial_way_num; i++) {
        GgafDxUtil::convRzRyToVector(expanse_rz, paAng_way[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_radial_way_num; i++) {
            pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
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

GgafDxFigureActor* StgUtil::shotWay004(const GgafDxGeometricActor* prm_pFrom,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
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





//// 点 A(a,b,c) B(d,e,f) を通る直線は
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












//点 A(x1,y2,z1) B(x2,y1,z1) を通る直線と点D(o_scx,o_scy,o_scz)の距離
//
//(x1,y2,z1) (x2,y1,z1)     (o_scx,o_scy,o_scz)
//
//sqrt(((y1^2-2*y2*y1+x2^2-2*x1*x2+y2^2+x1^2)*o_scz^2+(((2*y2-2*y1)*z1+2*z1*y1-2*y2*z1)*o_scy+((2*x1-2*x2)*z1+2*z1*x2-2*x1*z1)*o_scx+
//(2*y2*y1+2*x1*x2-2*y2^2-2*x1^2)*z1-2*z1*y1^2+2*y2*z1*y1-2*z1*x2^2+2*x1*z1*x2)*o_scz+(z1^2-2*z1*z1+x2^2-2*x1*x2+z1^2+x1^2)*o_scy^2+
//(((2*x1-2*x2)*y1+2*y2*x2-2*x1*y2)*o_scx-2*y2*z1^2+(2*z1*y1+2*y2*z1)*z1+(2*x1*x2-2*z1^2-2*x1^2)*y1-2*y2*x2^2+2*x1*y2*x2)*o_scy+
//(z1^2-2*z1*z1+y1^2-2*y2*y1+z1^2+y2^2)*o_scx^2+(-2*x1*z1^2+(2*z1*x2+2*x1*z1)*z1-2*x1*y1^2+(2*y2*x2+2*x1*y2)*y1+(-2*z1^2-2*y2^2)*x2)*o_scx+(y2^2+x1^2)*
//z1^2+(-2*y2*z1*y1-2*x1*z1*x2)*z1+(z1^2+x1^2)*y1^2-2*x1*y2*x2*y1+(z1^2+y2^2)*x2^2)/(z1^2-2*z1*z1+y1^2-2*y2*y1+x2^2-2*x1*x2+z1^2+y2^2+x1^2))
//
//
//sqrt(((y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2)*z1^2+(-2*o_scz*y2^2+4*o_scz*y1*y2-2*o_scz*y1^2-2*o_scz*x2^2+4*o_scz*x1*x2-2*o_scz*x1^2)*z1+
//(x2^2-2*o_scx*x2+o_scz^2+o_scx^2)*y2^2+
//(((2*o_scx-2*x1)*x2+2*o_scx*x1-2*o_scz^2-2*o_scx^2)*y1-2*o_scy*x2^2+(2*o_scy*x1+2*o_scx*o_scy)*x2-2*o_scx*o_scy*x1)*y2+
//(x1^2-2*o_scx*x1+o_scz^2+o_scx^2)*y1^2+((2*o_scy*x1-2*o_scx*o_scy)*x2-2*o_scy*x1^2+2*o_scx*o_scy*x1)*y1+(o_scz^2+o_scy^2)*x2^2+(-2*o_scz^2-2*o_scy^2)*x1*
//x2+(o_scz^2+o_scy^2)*x1^2)/(y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2))
//
//
//
//
//t=((z1-z1)*z0+(y1-y2)*y0+(x2-x1)*x0-z1*z1-y2*y1-x1*x2+z1^2+y2^2+x1^2)/(z1^2-2*z1*z1+y1^2-2*y2*y1+x2^2-2*x1*x2+z1^2+y2^2+x1^2)
//
//t=(y2^2+(-y1-y0)*y2+y0*y1+(x0-x1)*x2+x1^2-x0*x1)/(y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2)
