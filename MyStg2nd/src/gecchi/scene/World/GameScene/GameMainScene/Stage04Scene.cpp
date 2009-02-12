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
        _TRACE_("Stage04Scene::Finally „‚Í‚¢‚«‚È‚è©•ª’â~BGameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é‚Ü‚Å‘Ò‚Â‚·");
        this->inact(); //GameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é
    }
}

Stage04Scene::~Stage04Scene() {
}
