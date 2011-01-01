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

    _pos_prism = pos_prism;
    if (_pos_prism & POS_PRISM_XY) {
        _a = 1.0*(_y2 - _y1) / (_x2 - _x1);
        _b = (_x1*_y2 - _x2*_y1) / (_x1 - _x2);


    } else if (_pos_prism & POS_PRISM_YZ) {
        _a = 1.0*(_z2 - _z1) / (_y2 - _y1);
        _b = (_y1*_z2 - _y2*_z1) / (_y1 - _y2);

    } else if (_pos_prism & POS_PRISM_ZX) {
        _a = 1.0*(_x2 - _x1) / (_z2 - _z1);
        _b = (_z1*_x2 - _z2*_x1) / (_z1 - _z2);
    }
   if (_pos_prism & POS_PRISM_pp) {
        //            Å™ y+
        //
        //        Ñ°ÑüÑüÑüÑ¢
        //        Ñ†Å_Ç±ÇøÑ†
        // x- Å©  Ñ†Å@Å_ÇÁÑ†  Å® x+
        //        Ñ†Å@Å@Å_Ñ†
        //        Ñ§ÑüÑüÑüÑ£
        //
        //            Å´ y-
        _a = -1.0*_a; //åXÇ´ÇÕâEâ∫Ç™ÇËÇ…Ç»ÇÈÇΩÇﬂ
    } else if (_pos_prism & POS_PRISM_np) {
        //            Å™ y+
        //
        //        Ñ°ÑüÑüÑüÑ¢
        //        Ñ†Ç±ÇøÅ^Ñ†
        // x- Å©  Ñ†ÇÁÅ^Å@Ñ†  Å® x+
        //        Ñ†Å^Å@Å@Ñ†
        //        Ñ§ÑüÑüÑüÑ£
        //
        //            Å´ y-
        
    } else if (_pos_prism & POS_PRISM_pn) {
        //            Å™ y+
        //
        //        Ñ°ÑüÑüÑüÑ¢
        //        Ñ†Å@Å@Å^Ñ†
        // x- Å©  Ñ†Å@Å^Ç±Ñ†  Å® x+
        //        Ñ†Å^ÇøÇÁÑ†
        //        Ñ§ÑüÑüÑüÑ£
        //
        //            Å´ y-

    } else { // ÇÃÇ±ÇËÇÕ POS_PRISM_nn
        //            Å™ y+
        //
        //        Ñ°ÑüÑüÑüÑ¢
        //        Ñ†Å_Å@Å@Ñ†
        // x- Å©  Ñ†Ç±Å_Å@Ñ†  Å® x+
        //        Ñ†ÇøÇÁÅ_Ñ†
        //        Ñ§ÑüÑüÑüÑ£
        //
        //            Å´ y-
        _a = -1.0*_a; //åXÇ´ÇÕâEâ∫Ç™ÇËÇ…Ç»ÇÈÇΩÇﬂ
    } 
}


ColliAAPrism::~ColliAAPrism() {
    TRACE("ColliAAPrism::~ColliAAPrism()");
}
