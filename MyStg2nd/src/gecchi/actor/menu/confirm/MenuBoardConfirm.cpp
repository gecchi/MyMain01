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
    relationItemCancel(ITEM_CANCEL);
    CursorConfirmMenu* pCursor = NEW CursorConfirmMenu("CursorConfirmMenu");
    setCursor(pCursor, 8, 0.2, 0.7);
    setSelectedItemIndex(ITEM_OK); //初期選択
    setTransition(10, -PX2CO(100), PX2CO(0)); //左から右へスライド
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
void MenuBoardConfirm::onRisen() {
    setSelectedItemIndex(ITEM_OK); //初期選択
    MenuBoard::onRisen();
}
void MenuBoardConfirm::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}
MenuBoardConfirm::~MenuBoardConfirm() {
}
