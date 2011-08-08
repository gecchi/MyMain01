#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultGod::DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) : GgafDx9God(prm_hInstance, prm_pHWndPrimary, prm_pHWndSecondary) {
    _pSplSourceManager = NEW SplineSourceManager("SplineSourceManager");
    _pSplManufactureManager = NEW SplineManufactureManager("SplineManufactureManager");
}

void DefaultGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("DefaultGod::clean() begin");
        GgafDx9God::clean();
        DELETE_IMPOSSIBLE_NULL(_pSplSourceManager);
        DELETE_IMPOSSIBLE_NULL(_pSplManufactureManager);
        _TRACE_("DefaultGod::clean() end");
    }
}

DefaultGod::~DefaultGod() {
    clean();
    _was_cleaned = true;
}
