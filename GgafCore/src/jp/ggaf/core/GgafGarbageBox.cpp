#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
	_pGarbageRootActor = NEW GgafGarbageRootActor();
	_pGarbageRootScene = NEW GgafGarbageRootScene();
}


void GgafGarbageBox::add(GgafActor* prm_pActor) {
	_pGarbageRootActor->addSubLast(prm_pActor->tear());
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
	_pGarbageRootScene->addSubLast(prm_pScene->tear());
}


void GgafGarbageBox::cleane(int prm_iNumCleanNode) {
	_pGarbageRootScene->cleane(prm_iNumCleanNode);
	_pGarbageRootActor->cleane(prm_iNumCleanNode);
}


GgafGarbageBox::~GgafGarbageBox() {
	DELETE_IMPOSSIBLE_NULL(_pGarbageRootScene);
	DELETE_IMPOSSIBLE_NULL(_pGarbageRootActor);
}

