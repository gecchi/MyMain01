#include "jp/ggaf/lib/actor/DefaultRegularPolygonBoardActor.h"



using namespace GgafLib;

DefaultRegularPolygonBoardActor::DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model) :
        GgafDx::RegularPolygonBoardActor(prm_name,
                                       prm_model,
                                       "DefaultRegularPolygonBoardEffect",
                                       "DefaultRegularPolygonBoardTechnique") {
    _class_name = "DefaultRegularPolygonBoardActor";
}

DefaultRegularPolygonBoardActor::~DefaultRegularPolygonBoardActor() {
}

