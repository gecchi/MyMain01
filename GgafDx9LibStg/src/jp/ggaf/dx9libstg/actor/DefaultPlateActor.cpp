#include "stdafx.h"

DefaultPlateActor::DefaultPlateActor(string prm_name, string prm_xname) : GgafDx9PlateActor(prm_name, prm_xname) {
	_class_name = "DefaultPlateActor";
}

DefaultPlateActor::~DefaultPlateActor() {
	TRACE("DefaultPlateActor::~DefaultPlateActor() "<<getName()<<" start--->");
	TRACE("DefaultPlateActor::~DefaultPlateActor() "<<getName()<<" <---end");
}

