#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model) :
    GgafDx::BoardActor(prm_name, prm_model, "DefaultBoardEffect", "DefaultBoardTechnique") {  
    _class_name = "DefaultBoardActor";
}

DefaultBoardActor::~DefaultBoardActor() {
}

