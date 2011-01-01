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

    int x1_s, y1_s, x2_e, y2_e;
    _pos_prism = pos_prism;
    if (_pos_prism & POS_PRISM_XY) {
        if (_pos_prism & POS_PRISM_pp) {
            //            Å™ y+
            // (_x1,_y2)      (_x2,_y2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å_Ç±ÇøÑ†
            // x- Å©  Ñ†Å@Å_ÇÁÑ†  Å® x+
            //        Ñ†Å@Å@Å_Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_x1,_y1)      (_x2,_y1)
            //            Å´ y-
            x1_s = _x1;
            y1_s = _y2;
            x2_e = _x2;
            y2_e = _y1;
        } else if (_pos_prism & POS_PRISM_np) {
            //            Å™ y+
            // (_x1,_y2)      (_x2,_y2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Ç±ÇøÅ^Ñ†
            // x- Å©  Ñ†ÇÁÅ^Å@Ñ†  Å® x+
            //        Ñ†Å^Å@Å@Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_x1,_y1)      (_x2,_y1)
            //            Å´ y-
            x1_s = _x1;
            y1_s = _y1;
            x2_e = _x2;
            y2_e = _y2;
        } else if (_pos_prism & POS_PRISM_pn) {
            //            Å™ y+
            // (_x1,_y2)      (_x2,_y2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å@Å@Å^Ñ†
            // x- Å©  Ñ†Å@Å^Ç±Ñ†  Å® x+
            //        Ñ†Å^ÇøÇÁÑ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_x1,_y1)      (_x2,_y1)
            //            Å´ y-
            x1_s = _x1;
            y1_s = _y1;
            x2_e = _x2;
            y2_e = _y2;
        } else { // ÇÃÇ±ÇËÇÕ POS_PRISM_nn
            //            Å™ y+
            // (_x1,_y2)      (_x2,_y2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å_Å@Å@Ñ†
            // x- Å©  Ñ†Ç±Å_Å@Ñ†  Å® x+
            //        Ñ†ÇøÇÁÅ_Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_x1,_y1)      (_x2,_y1)
            //            Å´ y-
            x1_s = _x1;
            y1_s = _y2;
            x2_e = _x2;
            y2_e = _y1;
        }


    } else if (_pos_prism & POS_PRISM_YZ) {

        if (_pos_prism & POS_PRISM_pp) {
            //            Å™ z+
            // (_y1,_z2)      (_y2,_z2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å_Ç±ÇøÑ†
            // y- Å©  Ñ†Å@Å_ÇÁÑ†  Å® y+
            //        Ñ†Å@Å@Å_Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_y1,_z1)      (_y2,_z1)
            //            Å´ z-
            x1_s = _y1;
            y1_s = _z2;
            x2_e = _y2;
            y2_e = _z1;
        } else if (_pos_prism & POS_PRISM_np) {
            //            Å™ z+
            // (_y1,_z2)      (_y2,_z2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Ç±ÇøÅ^Ñ†
            // y- Å©  Ñ†ÇÁÅ^Å@Ñ†  Å® y+
            //        Ñ†Å^Å@Å@Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_y1,_z1)      (_y2,_z1)
            //            Å´ z-
            x1_s = _y1;
            y1_s = _z1;
            x2_e = _y2;
            y2_e = _z2;
        } else if (_pos_prism & POS_PRISM_pn) {
            //            Å™ z+
            // (_y1,_z2)      (_y2,_z2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å@Å@Å^Ñ†
            // y- Å©  Ñ†Å@Å^Ç±Ñ†  Å® y+
            //        Ñ†Å^ÇøÇÁÑ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_y1,_z1)      (_y2,_z1)
            //            Å´ z-
            x1_s = _y1;
            y1_s = _z1;
            x2_e = _y2;
            y2_e = _z2;
        } else { // ÇÃÇ±ÇËÇÕ POS_PRISM_nn
            //            Å™ z+
            // (_y1,_z2)      (_y2,_z2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å_Å@Å@Ñ†
            // y- Å©  Ñ†Ç±Å_Å@Ñ†  Å® y+
            //        Ñ†ÇøÇÁÅ_Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_y1,_z1)      (_y2,_z1)
            //            Å´ z-
            x1_s = _y1;
            y1_s = _z2;
            x2_e = _y2;
            y2_e = _z1;
        }

    } else if (_pos_prism & POS_PRISM_ZX) {
        if (_pos_prism & POS_PRISM_pp) {
            //            Å™ x+
            // (_z1,_x2)      (_z2,_x2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å_Ç±ÇøÑ†
            // z- Å©  Ñ†Å@Å_ÇÁÑ†  Å® z+
            //        Ñ†Å@Å@Å_Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_z1,_x1)      (_z2,_x1)
            //            Å´ x-
            x1_s = _z1;
            y1_s = _x2;
            x2_e = _z2;
            y2_e = _x1;
        } else if (_pos_prism & POS_PRISM_np) {
            //            Å™ x+
            // (_z1,_x2)      (_z2,_x2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Ç±ÇøÅ^Ñ†
            // z- Å©  Ñ†ÇÁÅ^Å@Ñ†  Å® z+
            //        Ñ†Å^Å@Å@Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_z1,_x1)      (_z2,_x1)
            //            Å´ x-
            x1_s = _z1;
            y1_s = _x1;
            x2_e = _z2;
            y2_e = _x2;
        } else if (_pos_prism & POS_PRISM_pn) {
            //            Å™ x+
            // (_z1,_x2)      (_z2,_x2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å@Å@Å^Ñ†
            // z- Å©  Ñ†Å@Å^Ç±Ñ†  Å® z+
            //        Ñ†Å^ÇøÇÁÑ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_z1,_x1)      (_z2,_x1)
            //            Å´ x-
            x1_s = _z1;
            y1_s = _x1;
            x2_e = _z2;
            y2_e = _x2;
        } else { // ÇÃÇ±ÇËÇÕ POS_PRISM_nn
            //            Å™ x+
            // (_z1,_x2)      (_z2,_x2)
            //        Ñ°ÑüÑüÑüÑ¢
            //        Ñ†Å_Å@Å@Ñ†
            // z- Å©  Ñ†Ç±Å_Å@Ñ†  Å® z+
            //        Ñ†ÇøÇÁÅ_Ñ†
            //        Ñ§ÑüÑüÑüÑ£
            // (_z1,_x1)      (_z2,_x1)
            //            Å´ x-
            x1_s = _z1;
            y1_s = _x2;
            x2_e = _z2;
            y2_e = _x1;
        }
    }
    _a = 1.0*(y2_e - y1_s) / (x2_e - x1_s);
    _b = (x1_s*y2_e - x2_e*y1_s) / (x1_s - x2_e);

}


ColliAAPrism::~ColliAAPrism() {
    TRACE("ColliAAPrism::~ColliAAPrism()");
}
