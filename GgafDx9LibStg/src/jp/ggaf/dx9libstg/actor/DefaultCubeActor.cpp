#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultCubeActor::DefaultCubeActor(const char* prm_name) :
    GgafDx9CubeActor(prm_name, NEW StgChecker(this))
{
    _class_name = "DefaultCubeActor";
    _pStgChecker = (StgChecker*)_pChecker;
}

DefaultCubeActor::~DefaultCubeActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
}
