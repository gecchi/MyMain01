#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CollisionPart::GgafDx9CollisionPart() : GgafObject() {
    _shape_kind = 0;
    _is_valid_flg = false;
    _dx = _dy = _dz = 0;
    _cx = _cy = _cz = 0;
    _base_cx = _base_cy = _base_cz = 0;
    _aabb_x1 = _aabb_y1 = _aabb_z1 = _aabb_x2 = _aabb_y2 = _aabb_z2 = 0;
    _rotX = _rotY = _rotZ = false;
}

GgafDx9CollisionPart::~GgafDx9CollisionPart() {
    TRACE("GgafDx9CollisionPart::~GgafDx9CollisionPart()");
}
