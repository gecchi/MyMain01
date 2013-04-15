#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Item::Item(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat)
               : DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "Item";
    pTractorMagic_ = nullptr;
}

TractorMagic* Item::getTractorMagic() {
    if (pTractorMagic_ == nullptr) {
        pTractorMagic_ = dynamic_cast<TractorMagic*>(P_MAGICMETER->lstMagic_.getFromFirst(0));
#ifdef MY_DEBUG
        if (pTractorMagic_ == nullptr) {
            throwGgafCriticalException("Item::Item TractorMagicのメーター位置がおかしいです。");
        }
#endif
    }
    return pTractorMagic_;
}

void Item::initialize() {
}

void Item::onReset() {
}

void Item::onActive() {
}

void Item::processBehavior() {
}

void Item::processJudgement() {
}

void Item::onInactive() {
}

Item::~Item() {
}
