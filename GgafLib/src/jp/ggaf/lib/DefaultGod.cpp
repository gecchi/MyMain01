#include "stdafx.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultGod::DefaultGod() :
        GgafDxGod() {
    _pSplSrcManager = NEW SplineSourceManager("SplineSourceManager");
    _pSplManufManager = NEW SplineManufactureManager("SplineManufactureManager");
}

void DefaultGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("DefaultGod::clean() begin");
        GgafDxGod::clean();
        GGAF_DELETE(_pSplSrcManager);
        GGAF_DELETE(_pSplManufManager);
        _TRACE_("DefaultGod::clean() end");
    }
}

DefaultGod::~DefaultGod() {
    clean();
    _was_cleaned = true;
}
