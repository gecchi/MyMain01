#include "jp/ggaf/core/GgafGarbageBox.h"

#include "jp/ggaf/core/actor/GgafDisusedActor.h"
#include "jp/ggaf/core/scene/GgafDisusedScene.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include <windows.h>

using namespace GgafCore;

#define GgafGarbage_MAX_WAIT 2000
//CRITICAL_SECTION GgafGarbageBox::CS;
bool GgafGarbageBox::_wait = false;
GgafGarbageBox* GgafGarbageBox::_pGarbageBox = nullptr;
int GgafGarbageBox::_cnt_cleaned = 0;


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
                _TRACE_("ÅÉåxçêÅÑ GgafGarbageBox::add("<<prm_pActor<<"["<<prm_pActor->getName()<<"]) ã≠êßadd");
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    prm_pActor->_can_live_flg = false;
    prm_pActor->inactivateTreeImmed();
    _pDisusedActor->addSubFirst(prm_pActor->extract()); //addSubFirstÇ≈Ç∑ÅIaddSubLastÇ…îÒÇ∏
    _TRACE_("ÉSÉ~î†(Actor) GgafGarbageBox::add("<<prm_pActor<<"["<<prm_pActor->getName()<<"])");
    GgafGarbageBox::_wait = false;
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    prm_pScene->_can_live_flg = false;
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("ÅÉåxçêÅÑ GgafGarbageBox::add("<<prm_pScene<<"["<<prm_pScene->getName()<<"]) ã≠êßadd");
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    prm_pScene->_can_live_flg = false;
    prm_pScene->inactivateTreeImmed();
    if (prm_pScene->_pSceneDirector) { //äƒì¬Ç™Ç¢ÇÈèÍçáÇÕÅAäƒì¬ÇÕGgafGarbageBox::add(GgafActor* prm_pActor)Ç÷
        GgafSceneDirector* pSceneDirector = prm_pScene->_pSceneDirector;
        prm_pScene->_pSceneDirector = nullptr;
        //GgafGarbageBox::add(GgafActor* prm_pActor) Ç∆ìØÇ∂èàóùÇãLèqÇ∑ÇÈÇ±Ç∆
        pSceneDirector->_can_live_flg = false;
        pSceneDirector->inactivateTreeImmed();
        _pDisusedActor->addSubFirst(pSceneDirector); //addSubFirstÇ≈Ç∑ÅIaddSubLastÇ…îÒÇ∏
        _TRACE_("ÉSÉ~î†(Actor) GgafGarbageBox::add("<<prm_pScene<<"["<<prm_pScene->getName()<<"] ÇÃäƒì¬"<<pSceneDirector<<"["<<pSceneDirector->getName()<<"])");
    }
    _pDisusedScene->addSubFirst(prm_pScene->extract()); //addSubFirstÇ≈Ç∑ÅIaddSubLastÇ…îÒÇ∏
    _TRACE_("ÉSÉ~î†(Scene) GgafGarbageBox::add("<<prm_pScene<<"["<<prm_pScene->getName()<<"])");
    GgafGarbageBox::_wait = false;
}

void GgafGarbageBox::clean(int prm_num_cleaning) {
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("ÅÉåxçêÅÑ GgafGarbageBox::clean() ã≠êßreturn");
                return;
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    _pDisusedActor->clean(prm_num_cleaning);
    _pDisusedScene->clean(prm_num_cleaning);
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
    GGAF_DELETE(_pDisusedScene);
    GGAF_DELETE(_pDisusedActor);
    _TRACE_("GgafGarbageBox::~GgafGarbageBox() done");
}

