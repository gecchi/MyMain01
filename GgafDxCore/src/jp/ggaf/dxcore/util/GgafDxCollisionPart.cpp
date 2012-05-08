#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCollisionPart::GgafDxCollisionPart() : GgafObject() {
    _shape_kind = 0;
    _is_valid_flg = false;
    _dx = _dy = _dz = 0;
    _cx = _cy = _cz = 0;
    _base_cx = _base_cy = _base_cz = 0;
    _aab_x1 = _aab_y1 = _aab_z1 = _aab_x2 = _aab_y2 = _aab_z2 = 0;
    _rotX = _rotY = _rotZ = false;
}

GgafDxCollisionPart::~GgafDxCollisionPart() {
    TRACE("GgafDxCollisionPart::~GgafDxCollisionPart()");
}
