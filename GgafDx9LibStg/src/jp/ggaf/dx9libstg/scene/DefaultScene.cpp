#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultScene::DefaultScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "DefaultScene";
    _paFrame_NextEvent = NULL;
    _iCnt_Event = 0;
}

DefaultScene::~DefaultScene() {
    //シーンにイベントが無いかもしれない
    DELETEARR_POSSIBLE_NULL(_paFrame_NextEvent);
}
