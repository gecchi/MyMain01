#include "stdafx.h"

FormationActor::FormationActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this), NEW StgChecker(this)) {
	_class_name = "FormationsActor";
    setBumpableOnlySelf(false);
}

FormationActor::~FormationActor() {
}
