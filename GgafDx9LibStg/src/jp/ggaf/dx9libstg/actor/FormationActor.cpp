#include "stdafx.h"

FormationActor::FormationActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW StgMover(this), NEW StgChecker(this)) {
	_class_name = "FormationsActor";
    setBumpable(false);
	_pMover = (StgMover*)_pGeoMover;
	_pChecker = (StgChecker*)_pGeoChecker;
}

FormationActor::~FormationActor() {
}
