#include "ScoreItem001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

ScoreItem001::ScoreItem001(const char* prm_name)
               : ScoreItem(prm_name, "ScoreItem001") {
    _class_name = "ScoreItem001";
    getStatus()->reset(statusResetFunction(ScoreItem001));
}

void ScoreItem001::initialize() {
}

ScoreItem001::~ScoreItem001() {
}

