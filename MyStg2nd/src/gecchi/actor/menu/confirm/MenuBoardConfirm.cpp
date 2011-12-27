#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


MenuBoardConfirm::MenuBoardConfirm(const char* prm_name) :
        MenuBoard(prm_name, "TurboMeter") {
    _class_name = "MenuBoardPause";
    LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("itemOK");
    pLabel->update(" O K ");
    addSelectItem(pLabel, PX2CO(10), PX2CO(50));
    pLabel = NEW LabelGecchi16Font("message");
    pLabel->update("CANCEL");
    addSelectItem(pLabel, PX2CO(100), PX2CO(50));

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("ARE YOU SURE ?", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispActor(pMsg, PX2CO(50), PX2CO(5));

    relationItemCancel(CONFIRM_MENU_ITEM_CANCEL);

    CursorConfirmMenu* pCursor = NEW CursorConfirmMenu("CursorConfirmMenu");
    setCursor(pCursor);
    config(30, 8, 0.2, 0.7);

    setSelectedItemIndex(0); //‰Šú‘I‘ð
    setTargetLocate(PX2CO(500), PX2CO(80),  0, -PX2CO(100));
}
bool MenuBoardConfirm::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardConfirm::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoardConfirm::condMoveCursorExNext() {
    return false;
}
bool MenuBoardConfirm::condMoveCursorExPrev() {
    return false;
}

void MenuBoardConfirm::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == CONFIRM_MENU_ITEM_CANCEL) {
        sink();
    } else if (prm_item_index == CONFIRM_MENU_ITEM_OK) {
        sink();
    }
}
MenuBoardConfirm::~MenuBoardConfirm() {
}
