#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultFramedBoardActor::DefaultFramedBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxFramedBoardActor(prm_name, prm_model, "DefaultFramedBoardEffect", "DefaultFramedBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultFramedBoardActor";
}

DefaultFramedBoardActor::~DefaultFramedBoardActor() {
}

