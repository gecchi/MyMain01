#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultScene::DefaultScene(const char* prm_name) : GgafDxScene(prm_name) {
    _class_name = "DefaultScene";
    _paFrame_NextEvent = nullptr;
    _cnt_event = 0;
    _event_num = 0;
    DefaultScene::_pProg == nullptr;
}

void DefaultScene::useProgress(int prm_num) {
    if (GgafScene::_pProg == nullptr) {
        GgafScene::_pProg = NEW SceneProgress(this, prm_num);
        DefaultScene::_pProg = (SceneProgress*)(GgafScene::_pProg);
    } else {
        _TRACE_("���x����["<<getName()<<"] �͊��� useProgress ���Ă��܂��Bprm_num="<<prm_num);
    }
}

DefaultScene::~DefaultScene() {
    //�V�[���ɃC�x���g��������������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
}
