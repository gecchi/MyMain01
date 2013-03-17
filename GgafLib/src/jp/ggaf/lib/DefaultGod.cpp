#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultGod::DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
        GgafDxGod(prm_hInstance, prm_pHWndPrimary, prm_pHWndSecondary) {
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
