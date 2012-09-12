#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MenuBoardConfirm::MenuBoardConfirm(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardPause";

    //���j���[�E�B���h�E�ݒ�
    update("%&&&&&&&&&&'\n"
           ")**********+\n"
           ")**********+\n"
           ")**********+\n"
           "-........../");
    _Z = 3; //�v���C�I���e�B�𑼂̃��j���[����O


    LabelGecchi16Font* pLabel_ = NEW LabelGecchi16Font("itemOK");
    pLabel_->update(" O K ");
    addSelectItem(pLabel_, PX_C(10) , PX_C(50), -1);
    pLabel_ = NEW LabelGecchi16Font("message");
    pLabel_->update("CANCEL");
    addSelectItem(pLabel_, PX_C(100), PX_C(50), -1);

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("ARE YOU SURE ?", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispActor(pMsg, PX_C(50), PX_C(5), -1);
    relationItemCancel(ITEM_CANCEL);
    CursorConfirmMenu* pCursor = NEW CursorConfirmMenu("CursorConfirmMenu");
    setCursor(pCursor, 8, 0.2, 0.7);
    setSelectedItemIndex(ITEM_OK); //�����I��
    setTransition(10, -PX_C(100), PX_C(0)); //������E�փX���C�h
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
    setSelectedItemIndex(ITEM_OK); //�����I��
    MenuBoard::onRisen();
}
void MenuBoardConfirm::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}
MenuBoardConfirm::~MenuBoardConfirm() {
}
