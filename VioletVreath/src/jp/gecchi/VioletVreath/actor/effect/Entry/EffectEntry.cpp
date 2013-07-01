#include "stdafx.h"
#include "EffectEntry.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry::EffectEntry(const char* prm_name, const char* prm_model) :
        DefaultMeshSetActor(prm_name, prm_model, nullptr) {
    _class_name = "EffectEntry";
    setZEnable(false);
    setZWriteEnable(false);
    setHitAble(false);
    pTarget_ = nullptr;
}

void EffectEntry::processJudgement() {
    //TODO:シーンinactiveでの終了時 pTarget_ は残ってしまう
    if (pTarget_) {
        if (pTarget_->onChangeToInactive()) {
            pTarget_ = nullptr;
        } else {
            positionAs(pTarget_);
        }
    }
    if (getActiveFrame() >= GGAF_SAYONARA_DELAY) {
        pTarget_ = nullptr;
        sayonara();
    }
    if (isOutOfUniverse()) {
        pTarget_ = nullptr;
        sayonara();
    }
}

void EffectEntry::onInactive() {
    pTarget_ = nullptr;
}

void EffectEntry::positionFollow(GgafDxCore::GgafDxGeometricActor* prm_pTarget) {
    pTarget_  = prm_pTarget;
}

EffectEntry::~EffectEntry() {
    pTarget_ = nullptr;
}
