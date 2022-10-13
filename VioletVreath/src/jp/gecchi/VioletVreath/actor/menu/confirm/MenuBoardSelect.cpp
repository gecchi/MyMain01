#include "MenuBoardSelect.h"
#include "CursorSelectMenu.h"

#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#define DISP 5
#define ITM 10



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardSelect::MenuBoardSelect(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardSelect";
    setWidth(PX_C(12*32));
    setHeight(PX_C(5*32));

    for (int i = 0; i < ITM; i++) {
        LabelGecchi16Font* pSelectDisp = NEW LabelGecchi16Font("DISP");
        std::string default_name = XTOS(i) + "***";
        pSelectDisp->update(default_name.c_str(), ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pSelectDisp);
    }

    CursorSelectMenu* pCursor = NEW CursorSelectMenu("CursorSelectMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    selectItem(0); //初期選択

    setTransition(10, -PX_C(100), PX_C(0)); //-100px左から右へスライド


//    LabelGecchi16Font* pLabel_ok = NEW LabelGecchi16Font("itemOK");
//    pLabel_ok->update(" O K ", ALIGN_CENTER, VALIGN_MIDDLE);
//    addItem(pLabel_ok, PX_C(100), PX_C(40));
//    LabelGecchi16Font* pLabel_cancel = NEW LabelGecchi16Font("itemCANCEL");
//    pLabel_cancel->update("CANCEL", ALIGN_CENTER, VALIGN_MIDDLE);
//    addItem(pLabel_cancel, PX_C(200), PX_C(40));

//    LabelGecchi16Font* pLabel_msg = NEW LabelGecchi16Font("message");
//    pLabel_msg->update("ARE YOU SURE ?", ALIGN_CENTER, VALIGN_MIDDLE);
//    addLabel(pLabel_msg, PX_C(150), PX_C(20));
//    relateAllItemToCancel(ITEM_CANCEL);

}
bool MenuBoardSelect::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardSelect::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoardSelect::condSelectExNext() {
    return false;
}
bool MenuBoardSelect::condSelectExPrev() {
    return false;
}
void MenuBoardSelect::onRise() {
    selectItem(ITEM_OK); //初期選択をリセット
    MenuBoard::onRise();
}

void MenuBoardSelect::onSelect(int prm_from_index, int prm_selected_index) {
    GgafDx::FigureActor* pItem =   _lstItems.getCurrent();
    GgafDx::FigureActor* pItem2 = getItem(prm_selected_index);


}

void MenuBoardSelect::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}
void MenuBoardSelect::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}

bool MenuBoardSelect::hasJustDecidedOk() {
    if (hasJustDecided() && getSelectedIndex() == ITEM_OK) {
        return true;
    } else {
        return false;
    }
}

bool MenuBoardSelect::hasJustDecidedCancel() {
    if (hasJustDecided() && getSelectedIndex() == ITEM_CANCEL) {
        return true;
    } else {
        return false;
    }
}
MenuBoardSelect::~MenuBoardSelect() {
}
