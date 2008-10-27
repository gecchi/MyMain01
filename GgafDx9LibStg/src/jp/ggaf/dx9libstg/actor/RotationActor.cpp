#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW StgMover(this), NEW StgChecker(this))  {
 		_class_name = "RotationActor";
 	    setBumpableOnlySelf(true);
 		_pMover = (StgMover*)_pGeoMover;
 		_pChecker = (StgChecker*)_pGeoChecker;
}
