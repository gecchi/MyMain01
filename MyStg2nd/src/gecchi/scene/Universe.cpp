#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
    _TRACE_("Universe::Universe()");
    //y‚ß‚àz
    //‚±‚±‚ÅActor‚âScene‚ÌNEW‚ğ‚Í‚µ‚Ä‚Í‚È‚ç‚È‚¢B
    //‚Ü‚¸‚Í‚±‚Ì¢‚ğì‚é‚±‚Æ‚ğ—Dæ‚µ‚È‚¢‚ÆA‚¢‚ë‚¢‚ë‚Æ•s“s‡‚ª‚ ‚éB
}

void Universe::initialize() {
    _pWorld = NEW World("WORLD");
    addSubLast(_pWorld);
    _TRACE_("Universe::initialize()");
}

void Universe::processJudgement() {
}


void Universe::processBehavior() {
}

Universe::~Universe() {
}
