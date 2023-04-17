#include "MenuBoardConfirm.h"

#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "CursorConfirmMenu.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardConfirm::MenuBoardConfirm(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardConfirm";
    setWidth(PX_C(12*32));
    setHeight(PX_C(5*32));

    LabelGecchi16Font* pLabel_ok = NEW LabelGecchi16Font("itemOK");
    pLabel_ok->update(" O K ", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pLabel_ok, PX_C(100), PX_C(40));
    LabelGecchi16Font* pLabel_cancel = NEW LabelGecchi16Font("itemCANCEL");
    pLabel_cancel->update("CANCEL", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pLabel_cancel, PX_C(200), PX_C(40));

    LabelGecchi16Font* pLabel_msg = NEW LabelGecchi16Font("message");
    pLabel_msg->update("ARE YOU SURE ?", ALIGN_CENTER, VALIGN_MIDDLE);
    addLabel(pLabel_msg, PX_C(150), PX_C(20));
    relateAllItemToCancel(ITEM_CANCEL);
    CursorConfirmMenu* pCursor = NEW CursorConfirmMenu("CursorConfirmMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    selectItem(ITEM_OK); //初期選択
    setTransition(10, -PX_C(100), PX_C(0)); //-100px左から右へスライド
}
bool MenuBoardConfirm::condSelectNext() {
    return VVB->isAutoRepeat(0, VVB_UI_RIGHT);
}
bool MenuBoardConfirm::condSelectPrev() {
    return VVB->isAutoRepeat(0, VVB_UI_LEFT);
}
bool MenuBoardConfirm::condSelectExNext() {
    return false;
}
bool MenuBoardConfirm::condSelectExPrev() {
    return false;
}
void MenuBoardConfirm::onRise() {
    selectItem(ITEM_OK); //初期選択をリセット
    MenuBoard::onRise();
}
void MenuBoardConfirm::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}
void MenuBoardConfirm::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}

bool MenuBoardConfirm::hasJustDecidedOk() {
    if (hasJustDecided() && getSelectedIndex() == ITEM_OK) {
        return true;
    } else {
        return false;
    }
}

bool MenuBoardConfirm::hasJustDecidedCancel() {
    if (hasJustDecided() && getSelectedIndex() == ITEM_CANCEL) {
        return true;
    } else {
        return false;
    }
}
MenuBoardConfirm::~MenuBoardConfirm() {
}
