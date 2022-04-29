#include "Cursor001.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"



using namespace GgafLib;
using namespace VioletVreath;


Cursor001::Cursor001(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "Cursor001";

}
void Cursor001::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void Cursor001::onActive() {

}

void Cursor001::processBehavior() {
    getVecVehicle()->behave();
    getUvFlipper()->behave();
}

void Cursor001::processJudgement() {
}

void Cursor001::moveTo(coord tx, coord ty) {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setMvAngTwd(tx, ty);
    pVecVehicle->asstMv()->slideByDt(UTIL::getDistance(_x, _y, tx, ty),
                                  8, 0.2, 0.3, 0, true);
}

Cursor001::~Cursor001() {

}
