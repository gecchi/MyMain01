#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage04Scene::Stage04Scene(const char* prm_name) : StageScene(prm_name) {
}

void Stage04Scene::initialize() {

}

void Stage04Scene::processBehavior() {
}

void Stage04Scene::processFinal() {

    if (_dwFrame == 1) {
        _TRACE_("Stage04Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
        this->inact(); //GameMainScene���������Ă����
    }
}

Stage04Scene::~Stage04Scene() {
}
