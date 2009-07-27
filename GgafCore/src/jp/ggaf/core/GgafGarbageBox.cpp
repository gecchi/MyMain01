#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
    _pGarbageRootActor = NEW GgafGarbageRootActor();
    _pGarbageRootScene = NEW GgafGarbageRootScene();
}

void GgafGarbageBox::add(GgafActor* prm_pActor) {
    _pGarbageRootActor->addSubLast(prm_pActor->extract());
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    _pGarbageRootScene->addSubLast(prm_pScene->extract());
}

void GgafGarbageBox::cleane(int prm_num_cleaning) {
    _pGarbageRootScene->cleane(prm_num_cleaning);
    _pGarbageRootActor->cleane(prm_num_cleaning);
}

GgafGarbageBox::~GgafGarbageBox() {
    DELETE_IMPOSSIBLE_NULL(_pGarbageRootScene);
    DELETE_IMPOSSIBLE_NULL(_pGarbageRootActor);
}

