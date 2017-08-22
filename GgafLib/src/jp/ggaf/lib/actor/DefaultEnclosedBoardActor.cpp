#include "jp/ggaf/lib/actor/DefaultEnclosedBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultEnclosedBoardActor::DefaultEnclosedBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxEnclosedBoardActor(prm_name, prm_model, "DefaultEnclosedBoardEffect", "DefaultEnclosedBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultEnclosedBoardActor";
}

DefaultEnclosedBoardActor::~DefaultEnclosedBoardActor() {
}

