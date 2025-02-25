#include "jp/ggaf/core/GarbageBox.h"

#include "jp/ggaf/core/actor/DisusedActor.h"
#include "jp/ggaf/core/scene/DisusedScene.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafCore;

#define Garbage_MAX_WAIT 2000

#ifdef _MSC_VER
volatile bool GarbageBox::_wait = false;
#else
volatile std::atomic<bool> GarbageBox::_wait(false);
#endif
GarbageBox* GarbageBox::_pGarbageBox = nullptr;
int GarbageBox::_cnt_cleaned = 0;

GarbageBox::GarbageBox() : Object() {
    GarbageBox::_wait = false;
    _pDisusedActor = NEW DisusedActor();
    _pDisusedScene = NEW DisusedScene();
}

void GarbageBox::add(Actor* prm_pActor) {
    for (int i = 0; i < Garbage_MAX_WAIT; i++) {
        if (GarbageBox::_wait) {
            Sleep(1);
            if (i == Garbage_MAX_WAIT-1) {
                _TRACE_("【警告】 GarbageBox::add("<<NODE_INFO_P(prm_pActor)<<") 強制add");
            }
        } else {
            break;
        }
    }
    GarbageBox::_wait = true;
    prm_pActor->inactivateTreeImmed();
    prm_pActor->_can_live_flg = false;
    _pDisusedActor->prependChild(prm_pActor->extract()); //prependChildです！appendChildに非ず
    _TRACE_("ゴミ箱(Actor) GarbageBox::add("<<NODE_INFO_P(prm_pActor)<<")");
    GarbageBox::_wait = false;
}

void GarbageBox::add(Scene* prm_pScene) {
    for (int i = 0; i < Garbage_MAX_WAIT; i++) {
        if (GarbageBox::_wait) {
            Sleep(1);
            if (i == Garbage_MAX_WAIT-1) {
                _TRACE_("【警告】 GarbageBox::add("<<NODE_INFO_P(prm_pScene)<<") 強制add");
            }
        } else {
            break;
        }
    }
    GarbageBox::_wait = true;
    prm_pScene->inactivateTreeImmed();
    prm_pScene->_can_live_flg = false;
    if (prm_pScene->_pSceneChief) { //チーフがいる場合は、チーフはGarbageBox::add(Actor* prm_pActor)へ
        SceneChief* pSceneChief = prm_pScene->_pSceneChief;
        prm_pScene->_pSceneChief = nullptr;
        //GarbageBox::add(Actor* prm_pActor) と同じ処理を記述すること
        pSceneChief->inactivateTreeImmed();
        pSceneChief->_can_live_flg = false;
        _pDisusedActor->prependChild(pSceneChief); //prependChildです！appendChildに非ず
        _TRACE_("ゴミ箱(Actor) GarbageBox::add( "<<NODE_INFO_P(prm_pScene)<<"のチーフの"<<NODE_INFO_P(pSceneChief)<<")");
    }
    _pDisusedScene->prependChild(prm_pScene->extract()); //prependChildです！appendChildに非ず
    _TRACE_("ゴミ箱(Scene) GarbageBox::add("<<NODE_INFO_P(prm_pScene)<<")");
    GarbageBox::_wait = false;
}

void GarbageBox::clean(int prm_num_cleaning) {
    for (int i = 0; i < Garbage_MAX_WAIT; i++) {
        if (GarbageBox::_wait) {
            Sleep(1);
            if (i == Garbage_MAX_WAIT-1) {
                _TRACE_("【警告】 GarbageBox::clean() 強制return");
                return;
            }
        } else {
            break;
        }
    }
    GarbageBox::_wait = true;
    _pDisusedActor->clean(prm_num_cleaning);
    _pDisusedScene->clean(prm_num_cleaning);
    GarbageBox::_wait = false;
}

GarbageBox::~GarbageBox() {
    _TRACE_("GarbageBox::~GarbageBox() begin");
    for (int i = 0; i < Garbage_MAX_WAIT; i++) {
        if (GarbageBox::_wait) {
            Sleep(1);
        } else {
            break;
        }
    }
    GarbageBox::_wait = true;
    GGAF_DELETE(_pDisusedScene);
    GGAF_DELETE(_pDisusedActor);
    _TRACE_("GarbageBox::~GarbageBox() done");
}

