#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultScene::DefaultScene(const char* prm_name) : GgafDxScene(prm_name) {
    _class_name = "DefaultScene";
    _paFrame_NextEvent = nullptr;
    _cnt_event = 0;
    _event_num = 0;
    DefaultScene::_pProg = nullptr;
    _scroll_speed = 0;
    _pFuncScrolling = nullptr;
}

void DefaultScene::useProgress(int prm_num) {
    if (GgafScene::_pProg == nullptr) {
        GgafScene::_pProg = NEW SceneProgress(this, prm_num);
        DefaultScene::_pProg = (SceneProgress*)(GgafScene::_pProg);
    } else {
        _TRACE_("＜警告＞["<<getName()<<"] は既に useProgress しています。prm_num="<<prm_num);
    }
}

void DefaultScene::scroll_X(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
            pActor->_X -= (*((coord*)p1));
        }
    }
}

void DefaultScene::processSettlementBehavior() {
    GgafDxScene::processSettlementBehavior();
    if (_pFuncScrolling && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        executeFuncLowerTree(_pFuncScrolling, &_scroll_speed, nullptr);
        //ここの executeFuncLowerTree の第２第３引数は、
        //このメソッドのエディタ上の直ぐ上に記述してある DefaultScene::scroll_X の受取り引数 p1 ,p2 と対応する
        //  this           → GgafObject* pThat
        //  &_scroll_speed → void* p1
        //  nullptr        → void* p2

    }
}

DefaultScene::~DefaultScene() {
    //シーンにイベントが無いかもしれない
    GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
}
