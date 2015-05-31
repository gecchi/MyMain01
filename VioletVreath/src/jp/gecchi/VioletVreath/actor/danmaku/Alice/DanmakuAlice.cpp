#include "DanmakuAlice.h"
#include "AliceShot.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DanmakuAlice::DanmakuAlice(const char* prm_name, const char* prm_shot_model_id) :
        DefaultGeometricActor(prm_name) {

    pShotDepo_ = NEW GgafActorDepository("AliceShotDepo");
    for (int i = 0; i < 300; i++) {
        std::string name = "AliceShot["+XTOS(i)+"]";
        pShotDepo_->put(NEW AliceShot(name.c_str(), prm_shot_model_id));
    }
    addSubGroup(pShotDepo_);
}

void DanmakuAlice::initialize() {
}

void DanmakuAlice::onReset() {
}

void DanmakuAlice::onActive() {
    getProgress()->reset(PROG_INIT);
}

void DanmakuAlice::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();

    switch (pProg->get()) {

         case PROG_INIT: {

         }
    }
}

DanmakuAlice::~DanmakuAlice() {
}

