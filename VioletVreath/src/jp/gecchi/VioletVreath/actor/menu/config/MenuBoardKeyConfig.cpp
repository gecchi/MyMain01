#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardKeyConfig::MenuBoardKeyConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardKeyConfig";
    //メニューウィンドウ設定
    update("%&&&&&&&&&&&&&&&&&&&'\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           ")*******************+\n"
           "-.................../");
    _Z = 5; //プライオリティ

    //メニューアイテム（選択可）設定
    char* apItemStr[] = {
          "MAIN SHOT",      //0
          "SUB SHOT",      //1
          "TURBO",         //2
          "CONTROLL",      //3
          "MAGIC",         //4
          "VAM",           //5
          "SAVE AND EXIT", //6
          "CANCEL"         //7
    };
    for (int i = ITEM_MAIN_SHOT; i <= ITEM_CANCEL; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+((i%4)*30)), -1);
    }
    //メニューアイテム（選択不可）設定
    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("[PAUSE MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispLabel(pMsg, PX_C(100), PX_C(20), -1);
    //特別なメニューカーソルオーダーを構築
    relateAllItemCancel(ITEM_CANCEL);

    //メニューカーソルを設定
    CursorKeyConfigMenu* pCursor = NEW CursorKeyConfigMenu("CursorKeyConfigMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedIndex(0); //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加
}
bool MenuBoardKeyConfig::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardKeyConfig::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardKeyConfig::condMoveCursorExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardKeyConfig::condMoveCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}

void MenuBoardKeyConfig::processBehavior() {
    MenuBoard::processBehavior();

    //サブメニュー判定
    StringBoardMenu* pSub = getSubMenu(0);
    if (pSub) {
        if (pSub->isJustDecided()) {
            if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {

                sinkSubMenu();

            } else if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSubMenu();
            } else {
            }
        } else {

        }
    }
}

void MenuBoardKeyConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_CANCEL) {
        sink();
    } else if (prm_item_index == ITEM_SAVE_AND_EXIT) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50)); //サブメニュー起動
    }
}
void MenuBoardKeyConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardKeyConfig::~MenuBoardKeyConfig() {
}
