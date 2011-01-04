#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliAAPrism::ColliAAPrism() : ColliAAB() {
    _pos_prism = 0;
    _shape_kind = COLLI_AAPRISM;
}

void ColliAAPrism::set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ) {
    ColliAAB::set(x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);

    //   y  = ax + b
    //   a  = (y2-y1)/(x2-x1)
    //   b  = (x1y2-x2y1) / (x1-x2)

    //   y  = {(y2-y1)/(x2-x1)} (x-x1) + y1
    //+90度で法泉で行こう
    int x1_s, y1_s, x2_e, y2_e;
    _pos_prism = pos_prism;
    if (_pos_prism & POS_PRISM_XY) {
        if (_pos_prism & POS_PRISM_pp) {
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │＼こち│
            // x- ←  │　＼ら│  → x+
            //        │　　＼│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x2;
            y1_s = _y1;
            x2_e = _x1;
            y2_e = _y2;
        } else if (_pos_prism & POS_PRISM_np) {
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │こち／│
            // x- ←  │ら／　│  → x+
            //        │／　　│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x2;
            y1_s = _y2;
            x2_e = _x1;
            y2_e = _y1;
        } else if (_pos_prism & POS_PRISM_pn) {
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │　　／│
            // x- ←  │　／こ│  → x+
            //        │／ちら│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x1;
            y1_s = _y1;
            x2_e = _x2;
            y2_e = _y2;
        } else { // のこりは POS_PRISM_nn
            //            ↑ y+
            // (_x1,_y2)      (_x2,_y2)
            //        ┌───┐
            //        │＼　　│
            // x- ←  │こ＼　│  → x+
            //        │ちら＼│
            //        └───┘
            // (_x1,_y1)      (_x2,_y1)
            //            ↓ y-
            x1_s = _x1;
            y1_s = _y2;
            x2_e = _x2;
            y2_e = _y1;
        }


    } else if (_pos_prism & POS_PRISM_YZ) {

        if (_pos_prism & POS_PRISM_pp) {
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │＼こち│
            // y- ←  │　＼ら│  → y+
            //        │　　＼│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y2;
            y1_s = _z1;
            x2_e = _y1;
            y2_e = _z2;
        } else if (_pos_prism & POS_PRISM_np) {
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │こち／│
            // y- ←  │ら／　│  → y+
            //        │／　　│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y2;
            y1_s = _z2;
            x2_e = _y1;
            y2_e = _z1;
        } else if (_pos_prism & POS_PRISM_pn) {
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │　　／│
            // y- ←  │　／こ│  → y+
            //        │／ちら│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y1;
            y1_s = _z1;
            x2_e = _y2;
            y2_e = _z2;
        } else { // のこりは POS_PRISM_nn
            //            ↑ z+
            // (_y1,_z2)      (_y2,_z2)
            //        ┌───┐
            //        │＼　　│
            // y- ←  │こ＼　│  → y+
            //        │ちら＼│
            //        └───┘
            // (_y1,_z1)      (_y2,_z1)
            //            ↓ z-
            x1_s = _y1;
            y1_s = _z2;
            x2_e = _y2;
            y2_e = _z1;
        }

    } else if (_pos_prism & POS_PRISM_ZX) {
        if (_pos_prism & POS_PRISM_pp) {
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │＼こち│
            // z- ←  │　＼ら│  → z+
            //        │　　＼│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z2;
            y1_s = _x1;
            x2_e = _z1;
            y2_e = _x2;
        } else if (_pos_prism & POS_PRISM_np) {
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │こち／│
            // z- ←  │ら／　│  → z+
            //        │／　　│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z2;
            y1_s = _x2;
            x2_e = _z1;
            y2_e = _x1;
        } else if (_pos_prism & POS_PRISM_pn) {
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │　　／│
            // z- ←  │　／こ│  → z+
            //        │／ちら│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z1;
            y1_s = _x1;
            x2_e = _z2;
            y2_e = _x2;
        } else { // のこりは POS_PRISM_nn
            //            ↑ x+
            // (_z1,_x2)      (_z2,_x2)
            //        ┌───┐
            //        │＼　　│
            // z- ←  │こ＼　│  → z+
            //        │ちら＼│
            //        └───┘
            // (_z1,_x1)      (_z2,_x1)
            //            ↓ x-
            x1_s = _z1;
            y1_s = _x2;
            x2_e = _z2;
            y2_e = _x1;
        }
    }
    //プリズム斜辺の境界線傾き
    _a = 1.0*(y2_e - y1_s) / (x2_e - x1_s);
    //プリズム斜辺の境界線の切片
    _b = (x1_s*y2_e - x2_e*y1_s) / (x1_s - x2_e);

    //斜辺ベクトル(x2_e-x1_s, y2_e-y1_s)に90度加えると
    //斜辺面法線ベクトルとなるようにしてある。
    //ここで保持しておきたいのは-90度(+270度)のベクトルである
    angle angIH = GgafDx9Util::simplifyAng(
        GgafDx9Util::getAngle2D(x2_e-x1_s, y2_e-y1_s)
        + ANGLE270
        );
    
    
    _vIH_x = GgafDx9Util::COS[angIH/ANGLE_RATE];
    _vIH_y = GgafDx9Util::SIN[angIH/ANGLE_RATE];

}


ColliAAPrism::~ColliAAPrism() {
    TRACE("ColliAAPrism::~ColliAAPrism()");
}
