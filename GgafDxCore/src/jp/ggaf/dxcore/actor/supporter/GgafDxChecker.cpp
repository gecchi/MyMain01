#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxChecker::GgafDxChecker(GgafDxGeometricActor* prm_pActor) :
    GgafObject() {
    _pCollisionArea = nullptr;
    _pActor = prm_pActor;
//    _blown_sgn_vX = 0;
//    _blown_sgn_vY = 0;
//    _blown_sgn_vZ = 0;
//    _is_blown = false;
}

void GgafDxChecker::makeCollision(int prm_colli_part_num) {
    if (_pCollisionArea == nullptr) {
        _pCollisionArea = NEW GgafDxCollisionArea(prm_colli_part_num);
    } else {
        throwGgafCriticalException("CollisionChecker3D::makeCollision ä˘Ç… makeCollision Ç≥ÇÍÇƒÇ¢Ç‹Ç∑ÅB");
    }
}

GgafDxChecker::~GgafDxChecker() {
}
