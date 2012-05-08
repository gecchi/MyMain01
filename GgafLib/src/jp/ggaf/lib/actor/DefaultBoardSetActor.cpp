#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultBoardSetActor::DefaultBoardSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxBoardSetActor(prm_name, prm_model, "DefaultBoardSetEffect", "DefaultBoardSetTechnique")
{
    _class_name = "DefaultBoardSetActor";
}

DefaultBoardSetActor::~DefaultBoardSetActor() {
}

