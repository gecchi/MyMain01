#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"

#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultGod::DefaultGod() :
        GgafDxGod() {
    _pSplSrcManager = NEW SplineSourceManager("SplineSourceManager");
    _pSplManufManager = NEW SplineManufactureManager("SplineManufactureManager");
}

HRESULT DefaultGod::initDevice() {
    StgUtil::init();  //���[�e�B���e�B����
    return GgafDxGod::initDevice();
}

void DefaultGod::clean() {
    if (!_was_cleaned) {
        _DTRACE_("DefaultGod::clean() begin");
        GgafDxGod::clean();
        GGAF_DELETE(_pSplSrcManager);
        GGAF_DELETE(_pSplManufManager);
        _DTRACE_("DefaultGod::clean() end");
    }
}

DefaultGod::~DefaultGod() {
    clean();
    _was_cleaned = true;
}
