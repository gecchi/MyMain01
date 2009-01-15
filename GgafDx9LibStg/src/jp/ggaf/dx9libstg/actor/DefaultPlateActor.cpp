#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;

DefaultPlateActor::DefaultPlateActor(string prm_name, string prm_model) : GgafDx9PlateActor(prm_name, prm_model) {
	_class_name = "DefaultPlateActor";
}

DefaultPlateActor::~DefaultPlateActor() {
	TRACE("DefaultPlateActor::~DefaultPlateActor() "<<getName()<<" start--->");
	TRACE("DefaultPlateActor::~DefaultPlateActor() "<<getName()<<" <---end");
}

