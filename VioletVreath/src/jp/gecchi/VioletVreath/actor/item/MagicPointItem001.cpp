#include "MagicPointItem001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MagicPointItem001::MagicPointItem001(const char* prm_name)
               : MagicPointItem(prm_name, "MagicPointItem001", StatusReset(MagicPointItem001)) {
    _class_name = "MagicPointItem001";
}

void MagicPointItem001::initialize() {
}

MagicPointItem001::~MagicPointItem001() {
}

