#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDummyActor(prm_name)  {
 	_class_name = "RotationActor";
 	setBumpableOnlySelf(false);
}
