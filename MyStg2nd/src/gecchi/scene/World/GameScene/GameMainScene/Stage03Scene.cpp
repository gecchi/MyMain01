#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage03Scene::Stage03Scene(const char* prm_name) : StageScene(prm_name) {
}

void Stage03Scene::initialize() {

}

void Stage03Scene::processBehavior() {
}

void Stage03Scene::processFinal() {

    if (_dwFrame == 1) {
        _TRACE_("Stage03Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
        this->inactivateTree(); //GameMainScene���������Ă����
    }
}

Stage03Scene::~Stage03Scene() {
}
