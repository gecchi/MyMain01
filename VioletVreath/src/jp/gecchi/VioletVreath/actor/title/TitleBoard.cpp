#include "stdafx.h"
#include "TitleBoard.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    setZEnable(false);
    setZWriteEnable(false);
}
void TitleBoard::initialize() {
    _z = 10; //���j���[��\�ɏo�����߂ɁA�^�C�g���͉��ցE�E�E
}

void TitleBoard::onActive() {
}

void TitleBoard::processBehavior() {
}

void TitleBoard::processJudgement() {
}

void TitleBoard::processDraw() {
    //���ɂQ�A��
    _pUvFlipper->setActivePtn(0);
    DefaultBoardActor::processDraw();
    coord tmpX = _x;
    _x += PX_C(600);
    _pUvFlipper->setActivePtn(1);
    DefaultBoardActor::processDraw();
    _x = tmpX;
}

TitleBoard::~TitleBoard() {
}
