#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultGeometricActor::DefaultGeometricActor(const char* prm_name, GgafStatus* prm_pStat, GgafDxChecker* prm_pChecker) :
    GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker)
{
    _class_name = "DefaultGeometricActor";
}

DefaultGeometricActor::~DefaultGeometricActor() {
}

