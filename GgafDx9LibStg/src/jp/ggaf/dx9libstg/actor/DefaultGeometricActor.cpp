#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultGeometricActor::DefaultGeometricActor(const char* prm_name, GgafDx9Checker* prm_pChecker) :
    GgafDx9GeometricActor(prm_name, prm_pChecker)
{
    _class_name = "DefaultGeometricActor";
}

DefaultGeometricActor::~DefaultGeometricActor() {
}

