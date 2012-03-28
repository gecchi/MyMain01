#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardSetActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    //z_ = 0.9999999f;  //ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= z_ < 1.0ÅjZ=(0Å`+1)
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
    //â°Ç…ÇQòAåã
    _pUvFlipper->setActivePtn(0);
    DefaultBoardSetActor::processDraw();
    coord tmpX = _X;
    _X += PxC(600);
    _pUvFlipper->setActivePtn(1);
    DefaultBoardSetActor::processDraw();
    _X = tmpX;
}

TitleBoard::~TitleBoard() {
}
