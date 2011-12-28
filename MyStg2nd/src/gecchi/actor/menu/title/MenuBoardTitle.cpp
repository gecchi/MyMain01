#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MenuBoardTitle::MenuBoardTitle(const char* prm_name) :
        MenuBoard(prm_name, "TurboMeter") {
    _class_name = "MenuBoardPause";
    char* apItemStr[] = {
          "GAME START",   //0
          "CONFIG",         //1
          "DEBUG",  //2
          "QUIT",   //3
    };
    for (int i = 0; i <= ITEM_QUIT; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addSelectItem(pLabel, PX2CO(10), PX2CO(10+((i%4)*40)));
    }

    relationItemCancel(ITEM_QUIT);

    CursorTitleMenu* pCursor = NEW CursorTitleMenu("CursorTitleMenu");
    setCursor(pCursor);
    config(10, 8, 0.2, 0.7);

    setSelectedItemIndex(ITEM_GAME_START); //‰Šú‘I‘ð

    _pConfirmMenu = NEW MenuBoardConfirm("confirm");
    addSubLast(_pConfirmMenu);
}
bool MenuBoardTitle::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardTitle::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardTitle::condMoveCursorExNext() {
    return false;
}
bool MenuBoardTitle::condMoveCursorExPrev() {
    return false;
}

void MenuBoardTitle::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
//        sink();
}

void MenuBoardTitle::riseConfirm() {
    riseSub(_pConfirmMenu);
}
void MenuBoardTitle::sinkConfirm() {
    sinkSub();
}

MenuBoardTitle::~MenuBoardTitle() {
}
