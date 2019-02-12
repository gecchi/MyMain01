#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"

#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

DefaultGod::DefaultGod() :
        GgafDx::God() {
    _pSplSrcManager = nullptr;
    _pSplManufManager = nullptr;
}

HRESULT DefaultGod::initDevice() {
    StgUtil::init();  //ユーティリティ準備
    _pSplSrcManager = createSplineSourceManager();
    _pSplManufManager = createSplineManufactureManager();
    return GgafDx::God::initDevice();
}

void DefaultGod::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" begin");
        GgafDx::God::clean();
        GGAF_DELETE(_pSplSrcManager);
        GGAF_DELETE(_pSplManufManager);
        _TRACE_(FUNC_NAME<<" end");
    }
}
DefaultEffectManager* DefaultGod::createEffectManager() {
    DefaultEffectManager* p = NEW DefaultEffectManager("EffectManager");
    return p;
}
SplineSourceManager* DefaultGod::createSplineSourceManager() {
    SplineSourceManager* p = NEW SplineSourceManager("SplineSourceManager");
    return p;
}
SplineManufactureManager* DefaultGod::createSplineManufactureManager() {
    SplineManufactureManager* p = NEW SplineManufactureManager("SplineManufactureManager");
    return p;
}

DefaultGod::~DefaultGod() {
    clean();
    _was_cleaned = true;
}
