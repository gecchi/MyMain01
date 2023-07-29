#include "EnemyIda.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "scene/MgrSpacetime/MgrWorld/ParallelCurveTestScene.h"

using namespace GgafLib;
using namespace Mogera;

EnemyIda::EnemyIda(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida") {
    _class_name = "EnemyIda";
    std::string filename = XTOS(getName()) + ".dat";
    pOs_ = NEW std::ofstream(filename.c_str());
    setScaleR(0.5);
}

void EnemyIda::onCreateModel() {
}

void EnemyIda::initialize() {
    getLocoVehicle()->linkFaceAngByMvAng(true);
}

void EnemyIda::onActive() {
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //ローカル座標系へ

    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->behave();

    changeGeoFinal(); //絶対座標系へ
}

void EnemyIda::processJudgement() {
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
    if (pOs_) {
        (*pOs_).close();
    }
}


