#include "stdafx.h"
using namespace GgafCore;

#define GgafGarbage_MAX_WAIT 2000
//CRITICAL_SECTION GgafGarbageBox::CS;
bool GgafGarbageBox::_wait = false;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
    GgafGarbageBox::_wait = false;
    _pDisusedActor = NEW GgafDisusedActor();
    _pDisusedScene = NEW GgafDisusedScene();
}

void GgafGarbageBox::add(GgafActor* prm_pActor) {
    prm_pActor->_can_live_flg = false;
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("ƒŒx„ GgafGarbageBox::add("<<this<<"["<<prm_pActor->getName()<<"]) ‹­§add");
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    prm_pActor->_can_live_flg = false;
    prm_pActor->inactivateTreeImmed();
    _pDisusedActor->addSubFirst(prm_pActor->extract()); //addSubFirst‚Å‚·IaddSubLast‚É”ñ‚¸
    _TRACE_("ƒSƒ~” (Actor) GgafGarbageBox::add("<<this<<"["<<prm_pActor->getName()<<"])");
    GgafGarbageBox::_wait = false;
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    prm_pScene->_can_live_flg = false;
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("ƒŒx„ GgafGarbageBox::add("<<this<<"["<<prm_pScene->getName()<<"]) ‹­§add");
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    prm_pScene->_can_live_flg = false;
    prm_pScene->inactivateTreeImmed();
    _pDisusedScene->addSubFirst(prm_pScene->extract()); //addSubFirst‚Å‚·IaddSubLast‚É”ñ‚¸
    _TRACE_("ƒSƒ~” (Scene) GgafGarbageBox::add("<<this<<"["<<prm_pScene->getName()<<"])");
    GgafGarbageBox::_wait = false;
}

void GgafGarbageBox::clean(int prm_num_cleaning) {
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("ƒŒx„ GgafGarbageBox::clean() ‹­§return");
                return;
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    _pDisusedActor->clean(prm_num_cleaning);
    _pDisusedScene->clean(1); //ƒV[ƒ“‚Í1ŒÂ‚¾‚¯
    GgafGarbageBox::_wait = false;
}

GgafGarbageBox::~GgafGarbageBox() {
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() begin");
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    DELETE_IMPOSSIBLE_NULL(_pDisusedScene);
    DELETE_IMPOSSIBLE_NULL(_pDisusedActor);
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() done");
}

