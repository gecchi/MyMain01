#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultCubeActor::DefaultCubeActor(const char* prm_name) :
    GgafDx9CubeActor(prm_name, NEW CollisionChecker(this))
{
    _class_name = "DefaultCubeActor";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
}

DefaultCubeActor::~DefaultCubeActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
}
