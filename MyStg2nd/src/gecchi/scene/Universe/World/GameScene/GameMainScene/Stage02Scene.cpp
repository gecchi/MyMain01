#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02Scene::Stage02Scene(const char* prm_name) : StageScene(prm_name) {
    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();
}

void Stage02Scene::initialize() {
}

void Stage02Scene::processBehavior() {

    if (getActivePartFrame() == 10) {
        _TRACE_("Stage02Scene::processBehavior Ž„‚à‹N“®‚µ‚Ü‚µ‚½‚æ");

        _TRACE_("SCENE 02 COMMING!!!!!");
        _pMessage->activateImmediately();
        _pMessage->update(400, 400, "SCENE 02 COMMING!!!!!");
        _pMessage->inactivateAfter(320);
    }

}

void Stage02Scene::processFinal() {
}

Stage02Scene::~Stage02Scene() {
}
