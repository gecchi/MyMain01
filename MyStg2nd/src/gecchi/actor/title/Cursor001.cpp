#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Cursor001::Cursor001(const char* prm_name) : DefaultBoardActor(prm_name, "LockOn001") {
    _class_name = "Cursor001";
}
void Cursor001::initialize() {
}

void Cursor001::onActive() {
}

void Cursor001::processBehavior() {
    _pKurokoA->behave();
}

void Cursor001::processJudgement() {
}

void Cursor001::moveTo(int X, int Y) {
    _pKurokoA->setMvAng(X, Y, _Z);

    _pKurokoA->execSmoothMvVeloSequence(0,GgafDx9Util::getDistance(_X, _Y, X, Y),
                                            10,0.2,0.3);
}

Cursor001::~Cursor001() {
}
