#include "stdafx.h"

DefaultCubeActor::DefaultCubeActor(string prm_name)
	: GgafDx9CubeActor(prm_name, NEW StgMover(this), NEW StgChecker(this)) {
	_class_name = "DefaultCubeActor";
	_pMover = (StgMover*)_pGeoMover;
	_pChecker = (StgChecker*)_pGeoChecker;
}

DefaultCubeActor::~DefaultCubeActor() {
	TRACE("DefaultCubeActor::~DefaultCubeActor() "<<getName()<<" start--->");
	TRACE("DefaultCubeActor::~DefaultCubeActor() "<<getName()<<" <---end");
}
