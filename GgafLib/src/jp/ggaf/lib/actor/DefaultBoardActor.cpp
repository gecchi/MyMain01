#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat) :
    GgafDx::BoardActor(prm_name, prm_model, "DefaultBoardEffect", "DefaultBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultBoardActor";
}

DefaultBoardActor::~DefaultBoardActor() {
}

