#include "jp/ggaf/lib/util/ColliAAPrism.h"

#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

ColliAAPrism::ColliAAPrism() : ColliAABox() {
    _shape_kind = COLLI_AAPRISM;
    _a = 0;
    _b = 0;
    _vIH_x = 0;
    _vIH_y = 0;
}

void ColliAAPrism::set(int x1, int y1, int z1, int x2, int y2, int z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (rot_x || rot_y || rot_z) {
        //TODO:ひまならプリズム要素は回転平行移動実装
        throwCriticalException("当たり判定のプリズム要素は回転平行移動は未対応です。");
    }
#endif

    ColliAABox::set(x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z);

    //   y  = ax + b
    //   a  = (y2-y1)/(x2-x1)
    //   b  = (x1y2-x2y1) / (x1-x2)

    //   y  = {(y2-y1)/(x2-x1)} (x-x1) + y1
    //+90度で法線で行こう
    int x1_s=0, y1_s=0, x2_e=0, y2_e=0;
    _pos_info = pos_info;
    if (_pos_info & POS_PRISM_XY_xx) {
        if (_pos_info & POS_PRISM_xx_PP) {
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │＼こち│
            // x- ←  │  ＼ら│  → x+
            //        │    ＼│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x2;
            y1_s = _y1;
            x2_e = _x1;
            y2_e = _y2;
        } else if (_pos_info & POS_PRISM_xx_NP) {
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │こち／│
            // x- ←  │ら／  │  → x+
            //        │／    │
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x2;
            y1_s = _y2;
            x2_e = _x1;
            y2_e = _y1;
        } else if (_pos_info & POS_PRISM_xx_PN) {
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │    ／│
            // x- ←  │  ／こ│  → x+
            //        │／ちら│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x1;
            y1_s = _y1;
            x2_e = _x2;
            y2_e = _y2;
        } else { // のこりは POS_PRISM_xx_NN
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │＼    │
            // x- ←  │こ＼  │  → x+
            //        │ちら＼│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x1;
            y1_s = _y2;
            x2_e = _x2;
            y2_e = _y1;
        }


    } else if (_pos_info & POS_PRISM_YZ_xx) {

        if (_pos_info & POS_PRISM_xx_PP) {
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │＼こち│
            // y- ←  │  ＼ら│  → y+
            //        │    ＼│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y2;
            y1_s = _z1;
            x2_e = _y1;
            y2_e = _z2;
        } else if (_pos_info & POS_PRISM_xx_NP) {
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │こち／│
            // y- ←  │ら／  │  → y+
            //        │／    │
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y2;
            y1_s = _z2;
            x2_e = _y1;
            y2_e = _z1;
        } else if (_pos_info & POS_PRISM_xx_PN) {
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │    ／│
            // y- ←  │  ／こ│  → y+
            //        │／ちら│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y1;
            y1_s = _z1;
            x2_e = _y2;
            y2_e = _z2;
        } else { // のこりは POS_PRISM_xx_NN
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │＼    │
            // y- ←  │こ＼  │  → y+
            //        │ちら＼│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y1;
            y1_s = _z2;
            x2_e = _y2;
            y2_e = _z1;
        }

    } else if (_pos_info & POS_PRISM_ZX_xx) {
        if (_pos_info & POS_PRISM_xx_PP) {
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │＼こち│
            // z- ←  │  ＼ら│  → z+
            //        │    ＼│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z2;
            y1_s = _x1;
            x2_e = _z1;
            y2_e = _x2;
        } else if (_pos_info & POS_PRISM_xx_NP) {
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │こち／│
            // z- ←  │ら／  │  → z+
            //        │／    │
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z2;
            y1_s = _x2;
            x2_e = _z1;
            y2_e = _x1;
        } else if (_pos_info & POS_PRISM_xx_PN) {
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │    ／│
            // z- ←  │  ／こ│  → z+
            //        │／ちら│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z1;
            y1_s = _x1;
            x2_e = _z2;
            y2_e = _x2;
        } else { // のこりは POS_PRISM_xx_NN
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │＼    │
            // z- ←  │こ＼  │  → z+
            //        │ちら＼│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z1;
            y1_s = _x2;
            x2_e = _z2;
            y2_e = _x1;
        }
    } else {
        //memo WallAAPrismActor の 空new時はプリズム位置 0 にすることとしたので、
        //以下のエラーはスルーするように変更した。

        //throwCriticalException("おかしなプリズム位置 _pos_info="<<_pos_info)
    }

    //当たり判定時に使用する計算用の値を予め求めておく。
    if (x2_e == x1_s) {
        _a = 0;
        _b = 0;
    } else {
        //プリズム斜辺の境界線傾き
        _a = 1.0*(y2_e - y1_s) / (x2_e - x1_s);
        //プリズム斜辺の境界線の切片
        _b = (x1_s*y2_e - x2_e*y1_s) / (x1_s - x2_e);
    }
    //あとで計算が楽になるため、
    //プリズム斜辺面の法線ベクトルの逆方向のベクトル _vIH_x, _vIH_yを求めておく
    //斜辺ベクトル(x2_e-x1_s, y2_e-y1_s)に90度加えると
    //斜辺面の法線ベクトルとなるようにしてある。
    //ここで保持しておきたいのは-90度(+270度)のベクトルである
    if (x2_e-x1_s != 0 && y2_e-y1_s != 0) {
        angle angIH = UTIL::simplifyAng(
            UTIL::getAngle2D(x2_e-x1_s, y2_e-y1_s)
            + D270ANG
            );
        _vIH_x = ANG_COS(angIH);
        _vIH_y = ANG_SIN(angIH);
    } else {
        _vIH_x = 0;
        _vIH_y = 0;
    }


}


ColliAAPrism::~ColliAAPrism() {
}
