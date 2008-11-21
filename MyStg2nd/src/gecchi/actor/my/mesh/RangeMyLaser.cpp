#include "stdafx.h"

RangeMyLaser::RangeMyLaser(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))  {
 	_class_name = "RangeMyLaser";
 	setBumpableOnlySelf(false);
 	_pChecker = (StgChecker*)_pGeoChecker;
 	_state = 0;
 	_isHead = false;
 	_dwFrame_LastObtain = 0;
}
