#include "jp/ggaf/lib/actor/DefaultRegularPolygonBoardActor.h"



using namespace GgafLib;

DefaultRegularPolygonBoardActor::DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat) :
        GgafDx::RegularPolygonBoardActor(prm_name,
                                       prm_model,
                                       "DefaultRegularPolygonBoardEffect",
                                       "DefaultRegularPolygonBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultRegularPolygonBoardActor";
}

DefaultRegularPolygonBoardActor::~DefaultRegularPolygonBoardActor() {
}

