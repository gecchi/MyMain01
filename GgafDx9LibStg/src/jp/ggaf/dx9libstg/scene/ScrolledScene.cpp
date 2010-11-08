#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

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
    if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
        if (pActor->_obj_class & Obj_GgafDx9GeometricActor) {
            ((GgafDx9GeometricActor*)pActor)->_X -= (*((int*)p1));
        }
    }
}

void ScrolledScene::processSettlementBehavior() {
    DefaultScene::processSettlementBehavior();
    if (_pFuncScrolling) {
        execDownFunction(_pFuncScrolling, &_scrool_speed, NULL);
    }

}

ScrolledScene::~ScrolledScene() {
}
