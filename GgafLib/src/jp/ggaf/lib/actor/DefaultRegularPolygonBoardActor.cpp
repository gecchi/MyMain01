#include "jp/ggaf/lib/actor/DefaultRegularPolygonBoardActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultRegularPolygonBoardActor::DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        GgafDxRegularPolygonBoardActor(prm_name,
                                       prm_model,
                                       "DefaultRegularPolygonBoardEffect",
                                       "DefaultRegularPolygonBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultRegularPolygonBoardActor";
}

DefaultRegularPolygonBoardActor::~DefaultRegularPolygonBoardActor() {
}

