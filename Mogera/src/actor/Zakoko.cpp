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
}

void Zakoko::onCreateModel() {
}

void Zakoko::initialize() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
}

void Zakoko::onActive() {
}

void Zakoko::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    getKuroko()->behave();
}

void Zakoko::processJudgement() {
}

void Zakoko::onHit(GgafActor* prm_pOtherActor) {
}

void Zakoko::onInactive() {
}

void Zakoko::scatter() {
}

Zakoko::~Zakoko() {
}
