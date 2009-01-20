#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

RotationActor::RotationActor(string prm_name) : GgafDummyActor(prm_name)  {
 	_class_name = "RotationActor";
 	setBumpableAlone(false);
}
