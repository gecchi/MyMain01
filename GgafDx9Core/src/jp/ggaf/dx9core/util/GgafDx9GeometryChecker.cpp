#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9GeometryChecker::GgafDx9GeometryChecker(GgafDx9UntransformedActor* prm_pActor) : GgafObject() {
	_pActor = prm_pActor;
}

void GgafDx9GeometryChecker::behave() {
}

GgafDx9GeometryChecker::~GgafDx9GeometryChecker() {
	TRACE("GgafDx9GeometryChecker::~GgafDx9GeometryChecker() _pActor="<<_pActor->getName()<<" start--->");
	TRACE("GgafDx9GeometryChecker::~GgafDx9GeometryChecker() _pActor="<<_pActor->getName()<<" <---end");
}
