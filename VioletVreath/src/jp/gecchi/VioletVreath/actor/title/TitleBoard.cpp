#include "TitleBoard.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    setZEnableDraw(false);
    setZWriteEnable(false);
}

void TitleBoard::initialize() {
    _z = 10; //メニューを表に出すために、タイトルは奥へ・・・
}

void TitleBoard::onActive() {
}

void TitleBoard::processBehavior() {
}

void TitleBoard::processJudgement() {
}

void TitleBoard::processDraw() {
    //横に２連結
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtn(0);
    DefaultBoardActor::processDraw();
    coord tmpX = _x;
    _x += PX_C(600);
    pUvFlipper->setActivePtn(1);
    DefaultBoardActor::processDraw();
    _x = tmpX;
}

TitleBoard::~TitleBoard() {
}
