#include "actor/Box.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAngAssistant.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"

using namespace GgafLib;
using namespace Mogera;

Box::Box(const char* prm_name) :
        GgafLib::DefaultMassMeshActor(prm_name, "Box") {
    setScaleR(4);
}

void Box::initialize() {
}

void Box::processBehavior() {
}

Box::~Box() {
}

