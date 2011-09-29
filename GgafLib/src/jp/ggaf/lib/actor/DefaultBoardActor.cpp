#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model) :
    GgafDxBoardActor(prm_name, prm_model, "DefaultBoardEffect", "DefaultBoardTechnique")
{
    _class_name = "DefaultBoardActor";
}

DefaultBoardActor::~DefaultBoardActor() {
}

