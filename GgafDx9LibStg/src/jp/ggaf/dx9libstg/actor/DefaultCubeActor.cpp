#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultCubeActor::DefaultCubeActor(const char* prm_name) :
    GgafDx9CubeActor(prm_name, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
    _class_name = "DefaultCubeActor";
    _pChecker = (StgChecker*)_pGeoChecker;
}

DefaultCubeActor::~DefaultCubeActor() {
    TRACE("DefaultCubeActor::~DefaultCubeActor() "<<getName()<<" start--->");TRACE("DefaultCubeActor::~DefaultCubeActor() "<<getName()<<" <---end");
}
