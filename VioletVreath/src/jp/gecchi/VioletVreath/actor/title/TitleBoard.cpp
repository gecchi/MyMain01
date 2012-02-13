#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardSetActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    //_z = 0.9999999f;  //���Ԃ�Ŕw�� �i0 <= _z < 1.0�jZ=(0�`+1)
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
    //���ɂQ�A��
    _pUvFlipper->setActivePtnNo(0);
    DefaultBoardSetActor::processDraw();
    coord tmpX = _X;
    _X += PX2CO(600);
    _pUvFlipper->setActivePtnNo(1);
    DefaultBoardSetActor::processDraw();
    _X = tmpX;
}

TitleBoard::~TitleBoard() {
}
