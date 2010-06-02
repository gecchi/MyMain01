#include "stdafx.h"
using namespace std;
using namespace GgafCore;


CRITICAL_SECTION GgafGarbageBox::CS;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
    _pDisusedActor = NEW GgafDisusedActor();
    _pDisusedScene = NEW GgafDisusedScene();
    ::InitializeCriticalSection(&CS);
}

void GgafGarbageBox::add(GgafActor* prm_pActor) {
    ::EnterCriticalSection(&CS);
    _pDisusedActor->addSubLast(prm_pActor->extract());
    ::LeaveCriticalSection(&CS);
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    ::EnterCriticalSection(&CS);
    _pDisusedScene->addSubLast(prm_pScene->extract());
    ::LeaveCriticalSection(&CS);
}

void GgafGarbageBox::cleane(int prm_num_cleaning) {
    ::EnterCriticalSection(&CS);
    _pDisusedScene->cleane(prm_num_cleaning);
    _pDisusedActor->cleane(prm_num_cleaning);
    ::LeaveCriticalSection(&CS);
}

GgafGarbageBox::~GgafGarbageBox() {
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() begin");
    ::DeleteCriticalSection(&CS);
    DELETE_IMPOSSIBLE_NULL(_pDisusedScene);
    DELETE_IMPOSSIBLE_NULL(_pDisusedActor);
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() done");
}

