#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
    _TRACE_("Universe::Universe()");

    GgafRepeatSeq::create("CH_bomb1", 0, 5);
    GgafRepeatSeq::create("CH_yume_Sbend", 0, 2);
    GgafRepeatSeq::create("CH_yume_shototsu", 0, 2);
    GgafRepeatSeq::create("CH_break_glass01", 0, 5);
    GgafRepeatSeq::create("CH_a_shot", 0, 3);
    GgafRepeatSeq::create("CH_bse5", 0, 1); //オプションレーザー
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
