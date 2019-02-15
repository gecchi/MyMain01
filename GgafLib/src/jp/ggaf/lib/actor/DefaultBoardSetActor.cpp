#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"



using namespace GgafLib;

DefaultBoardSetActor::DefaultBoardSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::BoardSetActor(prm_name, prm_model, "DefaultBoardSetEffect", "DefaultBoardSetTechnique")
{
    _class_name = "DefaultBoardSetActor";
}

DefaultBoardSetActor::~DefaultBoardSetActor() {
}

