#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
    _TRACE_("Universe::Universe()");

    GgafRepeatSeq::create("CANNEL_bomb1", 0, 20);
    GgafRepeatSeq::create("CANNEL_yume_Sbend", 0, 5);
    GgafRepeatSeq::create("CANNEL_yume_shototsu", 0, 5);


    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Universe::initialize() {
    _pWorld = NEW World("WORLD");
    addSubLast(_pWorld);

    _TRACE_("Universe::initialize()");
}

void Universe::processJudgement() {
    DefaultUniverse::processJudgement();
}

void Universe::processBehavior() {
    DefaultUniverse::processBehavior();
}

Universe::~Universe() {
}
