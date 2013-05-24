#include "stdafx.h"
#include "ScoreItem001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

ScoreItem001::ScoreItem001(const char* prm_name)
               : ScoreItem(prm_name, "ScoreItem001", STATUS(ScoreItem001)) {
    _class_name = "ScoreItem001";
}

void ScoreItem001::initialize() {
}

ScoreItem001::~ScoreItem001() {
}

