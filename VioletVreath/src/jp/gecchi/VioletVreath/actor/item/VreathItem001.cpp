#include "VreathItem001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

VreathItem001::VreathItem001(const char* prm_name)
               : VreathItem(prm_name, "VreathItem001", STATUS(VreathItem001)) {
    _class_name = "VreathItem001";
}

void VreathItem001::initialize() {
}

VreathItem001::~VreathItem001() {
}

