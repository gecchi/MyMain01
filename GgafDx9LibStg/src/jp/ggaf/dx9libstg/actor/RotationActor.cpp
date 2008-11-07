#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))  {
 	_class_name = "RotationActor";
 	setBumpableOnlySelf(true);
 	_pChecker = (StgChecker*)_pGeoChecker;
}
