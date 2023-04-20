#include "MagicPointItem003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MagicPointItem003::MagicPointItem003(const char* prm_name)
               : MagicPointItem(prm_name, "MagicPointItem003", StatusReset(MagicPointItem003)) {
    _class_name = "MagicPointItem003";
}

void MagicPointItem003::initialize() {
}
void MagicPointItem003::onActive() {
    MagicPointItem::onActive();
    setScaleR(15.0); //BIG!
}

MagicPointItem003::~MagicPointItem003() {
}
