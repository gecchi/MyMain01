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
        _TRACE_("Stage05::Finally „‚Í‚¢‚«‚È‚è©•ª’â~BGameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é‚Ü‚Å‘Ò‚Â‚·");
        this->inactivateTree(); //GameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é
    }
}

Stage05::~Stage05() {
}
