#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;

RotationActor::RotationActor(string prm_name) : GgafDummyActor(prm_name)  {
 	_class_name = "RotationActor";
 	setBumpableAlone(false);
}
