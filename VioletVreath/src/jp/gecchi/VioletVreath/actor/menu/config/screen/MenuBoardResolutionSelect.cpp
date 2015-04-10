#include "MenuBoardResolutionSelect.h"

#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/God.h"

#include "CursorResolutionSelect.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MenuBoardResolutionSelect::MenuBoardResolutionSelect(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardResolutionSelect";

    //���j���[�E�B���h�E�ݒ�
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
    relateAllItemToCancel(ITEM_CANCEL);
    CursorResolutionSelect* pCursor = NEW CursorResolutionSelect("CursorResolutionSelect");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    selectItem(ITEM_OK); //�����I��
    setTransition(10, -PX_C(100), PX_C(0)); //-100px������E�փX���C�h
}
bool MenuBoardResolutionSelect::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardResolutionSelect::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoardResolutionSelect::condSelectExNext() {
    return false;
}
bool MenuBoardResolutionSelect::condSelectExPrev() {
    return false;
}
void MenuBoardResolutionSelect::onRise() {
    selectItem(ITEM_OK); //�����I�������Z�b�g
    MenuBoard::onRise();
}
void MenuBoardResolutionSelect::onDecision(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) {
}
void MenuBoardResolutionSelect::onCancel(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) {
}

bool MenuBoardResolutionSelect::hasJustDecidedOk() {
    if (hasJustDecided() && getSelectedIndex() == ITEM_OK) {
        return true;
    } else {
        return false;
    }
}

bool MenuBoardResolutionSelect::hasJustDecidedCancel() {
    if (hasJustDecided() && getSelectedIndex() == ITEM_CANCEL) {
        return true;
    } else {
        return false;
    }
}
MenuBoardResolutionSelect::~MenuBoardResolutionSelect() {
}
