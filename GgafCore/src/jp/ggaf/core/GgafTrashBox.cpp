#include "stdafx.h"

GgafTrashBox::GgafTrashBox() : GgafObject() {
	_pTrashRootActor = NEW GgafTrashRootActor();
	_pTrashRootScene = NEW GgafTrashRootScene();
}

GgafTrashBox::~GgafTrashBox() {
	DELETE_IMPOSSIBLE_NULL(_pTrashRootScene);
	DELETE_IMPOSSIBLE_NULL(_pTrashRootActor);
}

