#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model, const char* prm_technique) :
    GgafDx9BoardActor(prm_name, prm_model, prm_technique)
{
    _class_name = "DefaultBoardActor";
}

DefaultBoardActor::~DefaultBoardActor() {
    TRACE("DefaultBoardActor::~DefaultBoardActor() "<<getName()<<" start--->");TRACE("DefaultBoardActor::~DefaultBoardActor() "<<getName()<<" <---end");
}

