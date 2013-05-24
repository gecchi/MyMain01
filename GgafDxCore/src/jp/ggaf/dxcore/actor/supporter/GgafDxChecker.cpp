#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

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
        throwGgafCriticalException("CollisionChecker3D::makeCollision Šù‚É makeCollision ‚³‚ê‚Ä‚¢‚Ü‚·B");
    }
}

void GgafDxChecker::enable(int prm_index) {
    _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = true;
}

void GgafDxChecker::disable(int prm_index) {
    _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = false;
}

bool GgafDxChecker::isEnable(int prm_index) {
    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
}

GgafDxChecker::~GgafDxChecker() {
}
