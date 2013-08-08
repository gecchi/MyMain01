#include "stdafx.h"
#include "MenuBoardTitle.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "CursorTitleMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"

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
    //メニューアイテム設定
    const char* apItemStr[] = {
          "GAME START",   //0
          "CONFIG",       //1
          "DEBUG",        //2
          "QUIT",         //3
    };
    for (int i = ITEM_GAME_START; i <= ITEM_QUIT; i++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100), PX_C(40+(i*18)));
    }
    //キャンセル押下時移動先アイテム
    relateAllItemCancel(ITEM_QUIT);
    //カーソル設定
    CursorTitleMenu* pCursor = NEW CursorTitleMenu("CursorTitleMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    //スライド表示の設定
    setTransition(10, PX_C(0), +PX_C(100));
    //初期選択
    selectItem(ITEM_GAME_START);
    //確認サブメニュー
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0
    //コンフィグサブメニュー
    addSubMenu(NEW MenuBoardConfig("config"));
}
bool MenuBoardTitle::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardTitle::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardTitle::condSelectExNext() {
    return false;
}
bool MenuBoardTitle::condSelectrExPrev() {
    return false;
}

void MenuBoardTitle::onSelect(int prm_from, int prm_to) {
    //非選択項目は点滅させない
    if (prm_from > -1) {
        getItem(prm_from)->_pAFader->reset();
        getItem(prm_from)->_pAFader->setAlpha(1.0);
    }
    //選択項目を点滅
    if (prm_to > -1) {
        getItem(prm_to)->_pAFader->beat(20,10,0,0,-1);
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

void MenuBoardTitle::processBehavior() {
    MenuBoard::processBehavior();
    int selected = getSelectedIndex();
    if (selected == ITEM_QUIT) { //自身のメニューが"ITEM_QUIT"を指している場合
        //確認メニューの結果の振る舞い実行
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            ::PostQuitMessage(0);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkCurrentSubMenu();
        } else {

        }
    } else if (selected == ITEM_QUIT) {

    }

    GgafDxDrawableActor* pItem = getSelectedItem();
    pItem->_pAFader->behave();
    if (getRisingSubMenu()) {
        pItem->setAlpha(pItem->_pAFader->_top_alpha); //点滅を停止
    }

}
MenuBoardTitle::~MenuBoardTitle() {
}
