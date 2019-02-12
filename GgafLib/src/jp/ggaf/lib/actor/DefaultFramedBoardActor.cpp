#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"



using namespace GgafLib;

DefaultFramedBoardActor::DefaultFramedBoardActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat) :
    GgafDx::FramedBoardActor(prm_name, prm_model, "DefaultFramedBoardEffect", "DefaultFramedBoardTechnique") {  //prm_pStat–³Ž‹
    _class_name = "DefaultFramedBoardActor";
}

DefaultFramedBoardActor::~DefaultFramedBoardActor() {
}

