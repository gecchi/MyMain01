#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardSetActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    //z_ = 0.9999999f;  //˝ÔńĹwĘ i0 <= z_ < 1.0jZ=(0`+1)
    setZEnable(false);
    setZWriteEnable(false);
}
void TitleBoard::initialize() {
}

void TitleBoard::onActive() {
}

void TitleBoard::processBehavior() {
}

void TitleBoard::processJudgement() {
}

void TitleBoard::processDraw() {
    //ĄÉQA
    _pUvFlipper->setActivePtn(0);
    DefaultBoardSetActor::processDraw();
    coord tmpX = _X;
    _X += PXCO(600);
    _pUvFlipper->setActivePtn(1);
    DefaultBoardSetActor::processDraw();
    _X = tmpX;
}

TitleBoard::~TitleBoard() {
}
