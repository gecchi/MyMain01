#include "Zakoko.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"



using namespace GgafLib;
using namespace Mogera;


Zakoko::Zakoko(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Zakoko") {
    _class_name = "Zakoko";
    pOs_ = nullptr;
}

void Zakoko::onCreateModel() {
}

void Zakoko::initialize() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(128));
}

void Zakoko::onActive() {
    if (getBaseActor()->isFirst()) {
        std::string filename = XTOS(getName()) + ".dat";
        pOs_ = NEW std::ofstream(filename.c_str());
    }
}

void Zakoko::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->behave();
}

void Zakoko::processJudgement() {
    if (pOs_) {
        (*pOs_) << _x << "  " <<  _y  << "  " << _z << std::endl;
    }
}

void Zakoko::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
}

void Zakoko::onInactive() {
}

void Zakoko::scatter() {
}

Zakoko::~Zakoko() {
    if (pOs_) {
        (*pOs_).close();
    }
}
