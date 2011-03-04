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
    _TRACE_("�S�~��(Actor) GgafGarbageBox::add("<<prm_pActor->getName()<<")");
    ::LeaveCriticalSection(&CS);
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    ::EnterCriticalSection(&CS);
    _pDisusedScene->addSubLast(prm_pScene->extract());
    _TRACE_("�S�~��(Scene) GgafGarbageBox::add("<<prm_pScene->getName()<<")");
    ::LeaveCriticalSection(&CS);
}

void GgafGarbageBox::clean(int prm_num_cleaning) {
    ::EnterCriticalSection(&CS);
    _pDisusedActor->clean(prm_num_cleaning);
    _pDisusedScene->clean(prm_num_cleaning);
    ::LeaveCriticalSection(&CS);
}

GgafGarbageBox::~GgafGarbageBox() {
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() begin");
    ::DeleteCriticalSection(&CS);
    DELETE_IMPOSSIBLE_NULL(_pDisusedScene);
    DELETE_IMPOSSIBLE_NULL(_pDisusedActor);
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() done");
}

