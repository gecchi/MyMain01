#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage04Scene::Stage04Scene(const char* prm_name) : StageScene(prm_name) {
    _class_name = "Stage04Scene";
}

void Stage04Scene::initialize() {

}

void Stage04Scene::processBehavior() {
}

void Stage04Scene::processFinal() {

    if (getBehaveingFrame() == 1) {
        _TRACE_("Stage04Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
        this->inactivateTree(); //GameMainScene���������Ă����
    }
}

Stage04Scene::~Stage04Scene() {
}
