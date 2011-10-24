#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage04::Stage04(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage04";
}

void Stage04::initialize() {

}

void Stage04::processBehavior() {
}

void Stage04::processFinal() {

    if (getBehaveingFrame() == 1) {
        _TRACE_("Stage04::Finally „‚Í‚¢‚«‚È‚è©•ª’â~BGameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é‚Ü‚Å‘Ò‚Â‚·");
        this->inactivateTree(); //GameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é
    }
}

Stage04::~Stage04() {
}
