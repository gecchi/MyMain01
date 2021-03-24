#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

DefaultGod::DefaultGod() :
        GgafDx::God() {
}

HRESULT DefaultGod::initDevice() {
    StgUtil::init();  //ユーティリティ準備
    return GgafDx::God::initDevice();
}

void DefaultGod::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" begin");
        GgafDx::God::clean();
        _TRACE_(FUNC_NAME<<" end");
    }
}
DefaultEffectManager* DefaultGod::createEffectManager() {
    DefaultEffectManager* p = NEW DefaultEffectManager("EffectManager");
    return p;
}

DefaultGod::~DefaultGod() {
    clean();
    _was_cleaned = true;
}
