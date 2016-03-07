#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxChecker::GgafDxChecker(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pCollisionArea = nullptr;
}

void GgafDxChecker::createCollisionArea(int prm_colli_part_num) {
    if (_pCollisionArea == nullptr) {
        _pCollisionArea = NEW GgafDxCollisionArea(prm_colli_part_num);
    } else {
        throwGgafCriticalException("Šù‚É createCollisionArea ‚³‚ê‚Ä‚¢‚Ü‚·B");
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
