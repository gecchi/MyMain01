#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultBoardSetActor::DefaultBoardSetActor(const char* prm_name, const char* prm_model) :
    GgafDx9BoardSetActor(prm_name, prm_model, "DefaultBoardSetEffect", "DefaultBoardSetTechnique")
{
    _class_name = "DefaultBoardSetActor";
}

DefaultBoardSetActor::~DefaultBoardSetActor() {
}

