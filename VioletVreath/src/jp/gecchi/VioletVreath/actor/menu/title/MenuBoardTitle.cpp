#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardTitle::MenuBoardTitle(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardPause";
    //メニューウィンドウ設定
    update("%&&&&&&&'\n"
           ")*******+\n"
           ")*******+\n"
           ")*******+\n"
           ")*******+\n"
           "-......./");
    _Z = 3;
    //メニューアイテム設定
    char* apItemStr[] = {
          "GAME START",   //0
          "CONFIG",       //1
          "DEBUG",        //2
          "QUIT",         //3
    };
    for (int i = ITEM_GAME_START; i <= ITEM_QUIT; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100), PX_C(40+(i*18)), -1);
    }
    //キャンセル押下時移動先アイテム
    relateAllItemCancel(ITEM_QUIT);
    //カーソル設定
    CursorTitleMenu* pCursor = NEW CursorTitleMenu("CursorTitleMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);
    //スライド表示の設定
    setTransition(10, PX_C(0), +PX_C(100));
    //初期選択
    setSelectedIndex(ITEM_GAME_START);
    //確認サブメニュー
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0
    //コンフィグサブメニュー
    addSubMenu(NEW MenuBoardConfig("config"));
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
void MenuBoardTitle::processBehavior() {
    MenuBoard::processBehavior();

    if (getSelectedIndex() == ITEM_QUIT) { //自身のメニューが"ITEM_QUIT"を指している場合
        //確認メニューの結果の振る舞い実行
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->wasDecidedOk()) {
            PostQuitMessage(0);
        } else if (pSubConfirm->wasDecidedCancel()) {
            sinkSubMenu();
        } else {

        }
    } else if (getSelectedIndex() == ITEM_QUIT) {

    }

}
void MenuBoardTitle::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_GAME_START) {
        //GameTitleSceneクラス側でイベント実行
    } else if (prm_item_index == ITEM_CONFIG) {
        riseSubMenu(1, PX_C(50), PX_C(50));
    } else if (prm_item_index == ITEM_DEBUG) {
        //
    } else if (prm_item_index == ITEM_QUIT) {
        //確認メニュー起動
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y);
    }
}
void MenuBoardTitle::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardTitle::~MenuBoardTitle() {
}
