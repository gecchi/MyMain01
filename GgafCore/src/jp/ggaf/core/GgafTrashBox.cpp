#include "stdafx.h"

GgafTrashBox::GgafTrashBox() : GgafObject() {
	_pTrashRootActor = NEW GgafTrashRootActor();
	_pTrashRootScene = NEW GgafTrashRootScene();
}


void GgafTrashBox::add(GgafActor* prm_pActor) {
	_pTrashRootActor->addSubLast(prm_pActor->tear());
}

void GgafTrashBox::add(GgafScene* prm_pScene) {
	_pTrashRootScene->addSubLast(prm_pScene->tear());
}


void GgafTrashBox::cleane(int prm_iNumCleanNode) {
	_pTrashRootScene->cleane(prm_iNumCleanNode);
	_pTrashRootActor->cleane(prm_iNumCleanNode);
}


GgafTrashBox::~GgafTrashBox() {
	DELETE_IMPOSSIBLE_NULL(_pTrashRootScene);
	DELETE_IMPOSSIBLE_NULL(_pTrashRootActor);
}

