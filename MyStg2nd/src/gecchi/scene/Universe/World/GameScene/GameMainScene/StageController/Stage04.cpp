#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage04::Stage04(const char* prm_name) : StageScene(prm_name) {
    _class_name = "Stage04";
}

void Stage04::initialize() {

}

void Stage04::processBehavior() {
}

void Stage04::processFinal() {

    if (getBehaveingFrame() == 1) {
        _TRACE_("Stage04::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
        this->inactivateTree(); //GameMainSceneが解除してくれる
    }
}

Stage04::~Stage04() {
}
