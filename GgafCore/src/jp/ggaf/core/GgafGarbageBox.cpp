#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
    _pSayonaraActor = NEW GgafSayonaraActor();
    _pSayonaraScene = NEW GgafSayonaraScene();
}

void GgafGarbageBox::add(GgafActor* prm_pActor) {
    _pSayonaraActor->addSubLast(prm_pActor->extract());
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    _pSayonaraScene->addSubLast(prm_pScene->extract());
}

void GgafGarbageBox::cleane(int prm_num_cleaning) {
    _pSayonaraScene->cleane(prm_num_cleaning);
    _pSayonaraActor->cleane(prm_num_cleaning);
}

GgafGarbageBox::~GgafGarbageBox() {
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() begin");
    DELETE_IMPOSSIBLE_NULL(_pSayonaraScene);

    DELETE_IMPOSSIBLE_NULL(_pSayonaraActor);
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() done");
}

