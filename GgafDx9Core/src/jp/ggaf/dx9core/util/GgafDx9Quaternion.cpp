#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Quaternion::GgafDx9Quaternion(double prm_t, double prm_x, double prm_y, double prm_z) : GgafObject(),
    _t(prm_t),
    _x(prm_x),
    _y(prm_y),
    _z(prm_z) {
}


GgafDx9Quaternion::~GgafDx9Quaternion() {
}
