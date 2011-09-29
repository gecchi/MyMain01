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
        _TRACE_("Stage04Scene::Finally „‚Í‚¢‚«‚È‚è©•ª’â~BGameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é‚Ü‚Å‘Ò‚Â‚·");
        this->inactivateTree(); //GameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é
    }
}

Stage04Scene::~Stage04Scene() {
}
