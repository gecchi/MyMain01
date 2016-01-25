#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCollisionPart::GgafDxCollisionPart() : GgafObject() {
    _shape_kind = 0;
    _is_valid_flg = false;
    _dx = _dy = _dz = 0;
    _cx = _cy = _cz = 0;
    _base_cx = _base_cy = _base_cz = 0;
    _hdx = _hdy = _hdz = 0;
    _x1 = _y1 = _z1 = _x2 = _y2 = _z2 = 0;
    _rot_x = _rot_y = _rot_z = _rot = false;
}

GgafDxCollisionPart::~GgafDxCollisionPart() {
}
