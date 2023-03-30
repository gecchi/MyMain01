#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

DefaultCaretaker::DefaultCaretaker() :
        GgafDx::Caretaker() {
}

HRESULT DefaultCaretaker::initDevice() {
    StgUtil::init();  //ユーティリティ準備
    return GgafDx::Caretaker::initDevice();
}

void DefaultCaretaker::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" begin");
        GgafDx::Caretaker::clean();
        _TRACE_(FUNC_NAME<<" end");
    }
}
DefaultEffectManager* DefaultCaretaker::createEffectManager() {
    DefaultEffectManager* p = NEW DefaultEffectManager("EffectManager");
    return p;
}
DefaultModelManager* DefaultCaretaker::createModelManager() {
    DefaultModelManager* p = NEW DefaultModelManager("ModelManager");
    return p;
}


DefaultCaretaker::~DefaultCaretaker() {
    calmDown();
    clean();
    _was_cleaned = true;
}
