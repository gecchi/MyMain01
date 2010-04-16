#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage05Scene::Stage05Scene(const char* prm_name) : StageScene(prm_name) {
}

void Stage05Scene::initialize() {

}

void Stage05Scene::processBehavior() {
}

void Stage05Scene::processFinal() {

    if (getBehaveingFrame() == 1) {
        _TRACE_("Stage05Scene::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
        this->inactivateTree(); //GameMainSceneが解除してくれる
    }
}

Stage05Scene::~Stage05Scene() {
}
