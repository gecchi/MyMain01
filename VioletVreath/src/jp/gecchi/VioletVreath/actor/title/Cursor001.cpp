#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Cursor001::Cursor001(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "Cursor001";
}
void Cursor001::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_OSCILLATE_LOOP, 10);
}

void Cursor001::onActive() {

}

void Cursor001::processBehavior() {
    _pKurokoA->behave();
    _pUvFlipper->behave();
}

void Cursor001::processJudgement() {
}

void Cursor001::moveTo(int X, int Y) {
    _pKurokoA->setMvAng(X, Y);
    _pKurokoA->execSmoothMvVeloSequence(0, UTIL::getDistance(_X, _Y, X, Y),
                                        8, 0.2, 0.3);
}

Cursor001::~Cursor001() {
}
