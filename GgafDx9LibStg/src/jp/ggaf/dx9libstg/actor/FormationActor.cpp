#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

FormationActor::FormationActor(const char* prm_name) :
    GgafDx9GeometricActor(prm_name, NULL)
{
    _class_name = "FormationsActor";
    setBumpable(false);
}

FormationActor::~FormationActor() {
}
