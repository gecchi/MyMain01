#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MenuBoardConfirm::MenuBoardConfirm(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardConfirm";

    //メニューウィンドウ設定
    update("%&&&&&&&&&&'\n"
           ")**********+\n"
           ")**********+\n"
           ")**********+\n"
           "-........../");

    LabelGecchi16Font* pLabel_ok = NEW LabelGecchi16Font("itemOK");
    pLabel_ok->update(" O K ", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pLabel_ok, PX_C(100), PX_C(40));
    LabelGecchi16Font* pLabel_cancel = NEW LabelGecchi16Font("itemCANCEL");
    pLabel_cancel->update("CANCEL", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pLabel_cancel, PX_C(200), PX_C(40));

    LabelGecchi16Font* pLabel_msg = NEW LabelGecchi16Font("message");
    pLabel_msg->update("ARE YOU SURE ?", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_msg, PX_C(150), PX_C(20));
    relateAllItemCancel(ITEM_CANCEL);
    CursorConfirmMenu* pCursor = NEW CursorConfirmMenu("CursorConfirmMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);
    selectByIndex(ITEM_OK); //初期選択
    setTransition(10, -PX_C(100), PX_C(0)); //-100px左から右へスライド
}
bool MenuBoardConfirm::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardConfirm::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoardConfirm::condSelectExNext() {
    return false;
}
bool MenuBoardConfirm::condSelectrExPrev() {
    return false;
}
void MenuBoardConfirm::onRisen() {
    selectByIndex(ITEM_OK); //初期選択をリセット
    MenuBoard::onRisen();
}
void MenuBoardConfirm::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}
void MenuBoardConfirm::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

bool MenuBoardConfirm::wasDecidedOk() {
    if (isJustDecided() && getSelectedIndex() == ITEM_OK) {
        return true;
    } else {
        return false;
    }
}

bool MenuBoardConfirm::wasDecidedCancel() {
    if (isJustDecided() && getSelectedIndex() == ITEM_CANCEL) {
        return true;
    } else {
        return false;
    }
}
MenuBoardConfirm::~MenuBoardConfirm() {
}
