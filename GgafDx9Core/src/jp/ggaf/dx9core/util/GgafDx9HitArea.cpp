#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9HitArea::GgafDx9HitArea(int prm_iAreaNum) : GgafObject() {
    if (prm_iAreaNum > 0) {
        _iAreaNum = prm_iAreaNum;
    } else {
        throwGgafCriticalException("GgafDx9HitArea::GgafDx9HitArea Box”‚ª•s³Bprm_iAreaNum="<<prm_iAreaNum);
    }
}

GgafDx9HitArea::~GgafDx9HitArea() {
    TRACE("GgafDx9HitArea::~GgafDx9HitArea()");
}
