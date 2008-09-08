#include "stdafx.h"

FormationActor::FormationActor(string prm_name) : GgafDummyActor(prm_name) {
	_class_name = "FormationsActor";
    setBumpable(false);
}

FormationActor::~FormationActor() {
}
