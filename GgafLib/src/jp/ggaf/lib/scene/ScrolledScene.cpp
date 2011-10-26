#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ScrolledScene::ScrolledScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "ScrolledScene";
    _scrool_speed = 1000;
    _pFuncScrolling = ScrolledScene::scroll_X;
}


void ScrolledScene::scroll_X(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->_obj_class >= Obj_GgafScene) {
        return; //ƒV[ƒ“‚È‚ç‚Î–³Ž‹
    }
    GgafActor* pActor = (GgafActor*)pThat;
    if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
        if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
            ((GgafDxGeometricActor*)pActor)->_X -= (*((int*)p1));
        }
    }
}

void ScrolledScene::processSettlementBehavior() {
    DefaultScene::processSettlementBehavior();
    if (_pFuncScrolling && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
            executeFuncToLowerTree(_pFuncScrolling, &_scrool_speed, NULL);
        }
    }

}

ScrolledScene::~ScrolledScene() {
}
