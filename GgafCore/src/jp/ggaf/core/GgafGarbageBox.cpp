#include "jp/ggaf/core/GgafGarbageBox.h"

#include "jp/ggaf/core/actor/GgafDisusedActor.h"
#include "jp/ggaf/core/scene/GgafDisusedScene.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafCore;

#define GgafGarbage_MAX_WAIT 2000

#ifdef _MSC_VER
volatile bool GgafGarbageBox::_wait = false;
#else
volatile std::atomic<bool> GgafGarbageBox::_wait(false);
#endif
GgafGarbageBox* GgafGarbageBox::_pGarbageBox = nullptr;
int GgafGarbageBox::_cnt_cleaned = 0;

GgafGarbageBox::GgafGarbageBox() : GgafObject() {
    GgafGarbageBox::_wait = false;
    _pDisusedActor = NEW GgafDisusedActor();
    _pDisusedScene = NEW GgafDisusedScene();
}

void GgafGarbageBox::add(GgafActor* prm_pActor) {
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("＜警告＞ GgafGarbageBox::add("<<NODE_INFO_P(prm_pActor)<<") 強制add");
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    prm_pActor->inactivateTreeImmed();
    prm_pActor->_can_live_flg = false;
    _pDisusedActor->addSubFirst(prm_pActor->extract()); //addSubFirstです！addSubLastに非ず
    _TRACE_("ゴミ箱(Actor) GgafGarbageBox::add("<<NODE_INFO_P(prm_pActor)<<")");
    GgafGarbageBox::_wait = false;
}

void GgafGarbageBox::add(GgafScene* prm_pScene) {
    if (strcmp(prm_pScene->_class_name, "Stage01") == 0) {
        _TRACE_("kita---");
    }
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("＜警告＞ GgafGarbageBox::add("<<NODE_INFO_P(prm_pScene)<<") 強制add");
            }
        } else {
            break;
        }
    }
    GgafGarbageBox::_wait = true;
    prm_pScene->inactivateTreeImmed();
    prm_pScene->_can_live_flg = false;
    if (prm_pScene->_pSceneMediator) { //仲介者がいる場合は、仲介者はGgafGarbageBox::add(GgafActor* prm_pActor)へ
        GgafSceneMediator* pSceneMediator = prm_pScene->_pSceneMediator;
        prm_pScene->_pSceneMediator = nullptr;
        //GgafGarbageBox::add(GgafActor* prm_pActor) と同じ処理を記述すること
        pSceneMediator->inactivateTreeImmed();
        pSceneMediator->_can_live_flg = false;
        _pDisusedActor->addSubFirst(pSceneMediator); //addSubFirstです！addSubLastに非ず
        _TRACE_("ゴミ箱(Actor) GgafGarbageBox::add( "<<NODE_INFO_P(prm_pScene)<<"の仲介者の"<<NODE_INFO_P(pSceneMediator)<<")");
    }
    _pDisusedScene->addSubFirst(prm_pScene->extract()); //addSubFirstです！addSubLastに非ず
    _TRACE_("ゴミ箱(Scene) GgafGarbageBox::add("<<NODE_INFO_P(prm_pScene)<<")");
    GgafGarbageBox::_wait = false;
}

void GgafGarbageBox::clean(int prm_num_cleaning) {
    for (int i = 0; i < GgafGarbage_MAX_WAIT; i++) {
        if (GgafGarbageBox::_wait) {
            Sleep(1);
            if (i == GgafGarbage_MAX_WAIT-1) {
                _TRACE_("＜警告＞ GgafGarbageBox::clean() 強制return");
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

