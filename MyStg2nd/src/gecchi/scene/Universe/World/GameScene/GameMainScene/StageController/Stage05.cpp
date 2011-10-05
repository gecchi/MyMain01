#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage05::Stage05(const char* prm_name) : StageScene(prm_name) {
    _class_name = "Stage05";
}

void Stage05::initialize() {

}

void Stage05::processBehavior() {
}

void Stage05::processFinal() {

    if (getBehaveingFrame() == 1) {
        _TRACE_("Stage05::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
        this->inactivateTree(); //GameMainSceneが解除してくれる
    }
}

Stage05::~Stage05() {
}
