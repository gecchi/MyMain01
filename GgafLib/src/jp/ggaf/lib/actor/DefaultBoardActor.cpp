#include "stdafx.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxBoardActor(prm_name, prm_model, "DefaultBoardEffect", "DefaultBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultBoardActor";
}

DefaultBoardActor::~DefaultBoardActor() {
}

