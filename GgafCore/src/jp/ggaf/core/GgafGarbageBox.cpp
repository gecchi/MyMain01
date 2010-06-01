#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
    _pDisusedActor = NEW GgafDisusedActor();
    _pDisusedScene = NEW GgafDisusedScene();
}

void GgafGarbageBox::add(GgafActor* prm_pActor) {
    _pDisusedActor->addSubLast(prm_pActor->extract());
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    _pDisusedScene->addSubLast(prm_pScene->extract());
}

void GgafGarbageBox::cleane(int prm_num_cleaning) {
    _pDisusedScene->cleane(prm_num_cleaning);
    _pDisusedActor->cleane(prm_num_cleaning);
}

GgafGarbageBox::~GgafGarbageBox() {
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() begin");
    DELETE_IMPOSSIBLE_NULL(_pDisusedScene);

    DELETE_IMPOSSIBLE_NULL(_pDisusedActor);
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() done");
}

