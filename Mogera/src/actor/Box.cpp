#include "actor/Box.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/RikishaFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/RikishaMvAngAssistant.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
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

