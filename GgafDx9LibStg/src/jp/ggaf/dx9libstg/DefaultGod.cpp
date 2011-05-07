#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultGod::DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary) : GgafDx9God(prm_hInstance, prm_pHWndPrimary) {

}

void DefaultGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("DefaultGod::clean() begin");
        GgafDx9God::clean();
        _TRACE_("DefaultGod::clean() end");
    }
}

DefaultGod::~DefaultGod() {
    clean();
    _was_cleaned = true;
}
