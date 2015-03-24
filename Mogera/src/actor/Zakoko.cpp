#include "Zakoko.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
}

void Zakoko::onActive() {
    if (getBaseActor()->isFirst()) {
        std::string filename = XTOS(getName()) + ".dat";
        pOs_ = NEW std::ofstream(filename.c_str());
    }
}

void Zakoko::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->behave();
}

void Zakoko::processJudgement() {
    if (pOs_) {
        (*pOs_) << _x << "  " <<  _y  << "  " << _z << std::endl;
    }
}

void Zakoko::onHit(const GgafActor* prm_pOtherActor) {
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
