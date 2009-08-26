#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Quaternion::GgafDx9Quaternion(float prm_t, float prm_x, float prm_y, float prm_z) : GgafObject(),
    _t(prm_t),
    _x(prm_x),
    _y(prm_y),
    _z(prm_z) {
}


GgafDx9Quaternion::~GgafDx9Quaternion() {
}
