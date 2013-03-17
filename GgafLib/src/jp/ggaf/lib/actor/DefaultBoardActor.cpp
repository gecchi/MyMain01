#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxBoardActor(prm_name, prm_model, "DefaultBoardEffect", "DefaultBoardTechnique")  //prm_pStat–³Ž‹
{
    _class_name = "DefaultBoardActor";
    _pScaler = NEW GgafDxScaler(this);
}

DefaultBoardActor::~DefaultBoardActor() {
    GGAF_DELETE(_pScaler);
}

