#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02Scene::Stage02Scene(const char* prm_name) : StageScene(prm_name) {
}

void Stage02Scene::initialize() {
}

void Stage02Scene::processBehavior() {
}

void Stage02Scene::processFinal() {
    if (getBehaveingFrame() == 1) {
        _TRACE_("Stage02Scene::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
        this->inactivateTree(); //GameMainSceneが解除してくれる
    }
}

Stage02Scene::~Stage02Scene() {
}
