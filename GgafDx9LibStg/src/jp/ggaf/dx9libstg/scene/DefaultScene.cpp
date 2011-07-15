#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultScene::DefaultScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "DefaultScene";
    _paFrame_NextEvent = NULL;
    _iCnt_Event = 0;
    _event_num = 0;
}

void DefaultScene::useProgress(int prm_num) {
    if (GgafScene::_pProg == NULL) {
        GgafScene::_pProg = NEW SceneProgress(this, prm_num);
        DefaultScene::_pProg = (SceneProgress*)(GgafScene::_pProg);
    } else {
        _TRACE_("���x����["<<getName()<<"] �͊��� useProgress ���Ă��܂��Bprm_num="<<prm_num);
    }
}

DefaultScene::~DefaultScene() {
    //�V�[���ɃC�x���g��������������Ȃ�
    DELETEARR_POSSIBLE_NULL(_paFrame_NextEvent);
}
