#include "MagicPointItem002.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MagicPointItem002::MagicPointItem002(const char* prm_name)
               : MagicPointItem(prm_name, "MagicPointItem002", StatusReset(MagicPointItem002)) {
    _class_name = "MagicPointItem002";
}

void MagicPointItem002::initialize() {
}
void MagicPointItem002::onActive() {
    MagicPointItem::onActive();
    setScaleR(6.0); //BIG!
}

MagicPointItem002::~MagicPointItem002() {
}
