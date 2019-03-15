#include "jp/ggaf/core/GarbageBox.h"

#include "jp/ggaf/core/actor/DisusedActor.h"
#include "jp/ggaf/core/scene/DisusedScene.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
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
                _TRACE_("���x���� GarbageBox::add("<<NODE_INFO_P(prm_pActor)<<") ����add");
            }
        } else {
            break;
        }
    }
    GarbageBox::_wait = true;
    prm_pActor->inactivateTreeImmed();
    prm_pActor->_can_live_flg = false;
    _pDisusedActor->prependChild(prm_pActor->extract()); //prependChild�ł��IappendChild�ɔ�
    _TRACE_("�S�~��(Actor) GarbageBox::add("<<NODE_INFO_P(prm_pActor)<<")");
    GarbageBox::_wait = false;
}

void GarbageBox::add(Scene* prm_pScene) {
    if (strcmp(prm_pScene->_class_name, "Stage01") == 0) {
        _TRACE_("kita---");
    }
    for (int i = 0; i < Garbage_MAX_WAIT; i++) {
        if (GarbageBox::_wait) {
            Sleep(1);
            if (i == Garbage_MAX_WAIT-1) {
                _TRACE_("���x���� GarbageBox::add("<<NODE_INFO_P(prm_pScene)<<") ����add");
            }
        } else {
            break;
        }
    }
    GarbageBox::_wait = true;
    prm_pScene->inactivateTreeImmed();
    prm_pScene->_can_live_flg = false;
    if (prm_pScene->_pSceneMediator) { //����҂�����ꍇ�́A����҂�GarbageBox::add(Actor* prm_pActor)��
        SceneMediator* pSceneMediator = prm_pScene->_pSceneMediator;
        prm_pScene->_pSceneMediator = nullptr;
        //GarbageBox::add(Actor* prm_pActor) �Ɠ����������L�q���邱��
        pSceneMediator->inactivateTreeImmed();
        pSceneMediator->_can_live_flg = false;
        _pDisusedActor->prependChild(pSceneMediator); //prependChild�ł��IappendChild�ɔ�
        _TRACE_("�S�~��(Actor) GarbageBox::add( "<<NODE_INFO_P(prm_pScene)<<"�̒���҂�"<<NODE_INFO_P(pSceneMediator)<<")");
    }
    _pDisusedScene->prependChild(prm_pScene->extract()); //prependChild�ł��IappendChild�ɔ�
    _TRACE_("�S�~��(Scene) GarbageBox::add("<<NODE_INFO_P(prm_pScene)<<")");
    GarbageBox::_wait = false;
}

void GarbageBox::clean(int prm_num_cleaning) {
    for (int i = 0; i < Garbage_MAX_WAIT; i++) {
        if (GarbageBox::_wait) {
            Sleep(1);
            if (i == Garbage_MAX_WAIT-1) {
                _TRACE_("���x���� GarbageBox::clean() ����return");
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
