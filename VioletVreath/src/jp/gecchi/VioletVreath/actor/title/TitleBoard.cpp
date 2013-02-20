#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardSetActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    setZEnable(false);
    setZWriteEnable(false);
}
void TitleBoard::initialize() {
    _Z = 10; //メニューを表に出すために、タイトルは奥へ・・・
}

void TitleBoard::onActive() {
}

void TitleBoard::processBehavior() {
}

void TitleBoard::processJudgement() {
}

void TitleBoard::processDraw() {
    //横に２連結
    _pUvFlipper->setActivePtn(0);
    DefaultBoardSetActor::processDraw();
    coord tmpX = _X;
    _X += PX_C(600);
    _pUvFlipper->setActivePtn(1);
    DefaultBoardSetActor::processDraw();
    _X = tmpX;
}

TitleBoard::~TitleBoard() {
}
