#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9GeometryChecker::GgafDx9GeometryChecker(GgafDx9UntransformedActor* prm_pActor) {
	_pActor = prm_pActor;
}

void GgafDx9GeometryChecker::behave() {
}

GgafDx9GeometryChecker::~GgafDx9GeometryChecker() {
	TRACE("GgafDx9GeometryChecker::~GgafDx9GeometryChecker() _pActor="<<_pActor->getName()<<" start--->");
	TRACE("GgafDx9GeometryChecker::~GgafDx9GeometryChecker() _pActor="<<_pActor->getName()<<" <---end");
}
