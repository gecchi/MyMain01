#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardConfig::MenuBoardConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardConfig";
    //メニューウィンドウ設定
    update("%&&&&&&&&&&&'\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           "-.........../");

    //メニューアイテム（選択可）設定
    char* apItemStr[] = {
          "KEY CONFIG",   //0
          "SOUND CONFIG", //1
          "SCREEN CONFIG",  //2
          "BACK"            //3
    };
    for (int i = ITEM_KEY_CONFIG; i <= ITEM_BACK; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+((i%4)*30)), -1);
    }
    //メニューアイテム（選択不可）設定
    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("[CONFIG MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispLabel(pMsg, PX_C(100), PX_C(20), -1);
    //キャンセルアイテム設定
    relateAllItemCancel(ITEM_BACK);

    //メニューカーソルを設定
    CursorConfigMenu* pCursor = NEW CursorConfigMenu("CursorConfigMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedIndex(ITEM_BACK); //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), +PX_C(100)); //トランジション（表示非表示時の挙動）

    addSubMenu(NEW MenuBoardKeyConfig("key_config"));
    addSubMenu(NEW MenuBoardSoundConfig("sound_config"));
}
bool MenuBoardConfig::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardConfig::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}

void MenuBoardConfig::processBehavior() {
    MenuBoard::processBehavior();
}

void MenuBoardConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK) {
        sink();
    } else if (prm_item_index == ITEM_KEY_CONFIG) {
        riseSubMenu(0, PX_C(50), PX_C(10)); //keyconfigメニュー起動
    } else if (prm_item_index == ITEM_SOUND_CONFIG) {
        riseSubMenu(1,  PX_C(50), PX_C(10)); //soundconfigメニュー起動
    } else if (prm_item_index == ITEM_SCREEN_CONFIG) {
        riseSubMenu(2, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50));
    }
}
void MenuBoardConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardConfig::~MenuBoardConfig() {
}
