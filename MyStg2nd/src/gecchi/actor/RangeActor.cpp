#include "stdafx.h"

RangeActor::RangeActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))  {
 	_class_name = "RangeActor";
 	setBumpableOnlySelf(false);
 	_pChecker = (StgChecker*)_pGeoChecker;
 	_pActor_RangeHeader = NULL;
}
