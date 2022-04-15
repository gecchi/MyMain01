#include "DanmakuAlice.h"
#include "AliceShot.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT,
    PROG_1,
    PROG_BANPEI,
};

DanmakuAlice::DanmakuAlice(const char* prm_name, const char* prm_shot_model) :
        DefaultGeometricActor(prm_name) {

    pShotDepo_ = NEW GgafCore::ActorDepository("AliceShotDepo");
    for (int i = 0; i < 300; i++) {
        std::string name = "AliceShot["+XTOS(i)+"]";
        pShotDepo_->put(NEW AliceShot(name.c_str(), prm_shot_model));
    }
    appendGroupChild(pShotDepo_);
}

void DanmakuAlice::initialize() {
}

void DanmakuAlice::onReset() {
}

void DanmakuAlice::onActive() {
    getProgress()->reset(PROG_INIT);
}

void DanmakuAlice::processBehavior() {
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafCore::Progress* const pProg = getProgress();

    switch (pProg->get()) {

         case PROG_INIT: {

         }
    }
}

DanmakuAlice::~DanmakuAlice() {
}

