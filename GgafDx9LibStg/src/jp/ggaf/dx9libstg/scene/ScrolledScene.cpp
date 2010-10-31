#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ScrolledScene::ScrolledScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "ScrolledScene";
    _ground_speed = 0;
    _pFuncWallMove = NULL;
}




void ScrolledScene::processSettlementBehavior() {
    DefaultScene::processSettlementBehavior();
    if (_pFuncWallMove) {
        execDownFunction(_pFuncWallMove, &_ground_speed, NULL);
    }

}

ScrolledScene::~ScrolledScene() {
}
