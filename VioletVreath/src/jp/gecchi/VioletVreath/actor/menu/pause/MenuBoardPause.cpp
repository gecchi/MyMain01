#include "stdafx.h"
#include "MenuBoardPause.h"

#include "CursorPauseMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Properties.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardPause";
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

    //メニューアイテム（選択可）設定
    const char* apItemStr[] = {
          "BACK TO GAME",   //0
          "CONFIG",         //1
          "BACK TO TITLE",  //2
          "REBOOT",         //3

          "HIDE MENU",         //4
          "DUMMY2",         //5
          "DUMMY3",         //6
          "DUMMY4",         //7

          "DUMMY5",         //8
          "DUMMY6",         //9
          "DUMMY7",         //10
          "QUIT_GAME"       //11
    };
    for (int i = ITEM_BACK_TO_GAME; i <= ITEM_QUIT_GAME; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100+((i/4)*200)), PX_C(100+((i%4)*30)));
    }
    //メニューアイテム（選択不可）設定
    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("[PAUSE MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(100), PX_C(20));

    //特別なメニューカーソルオーダーを構築
    relateItemToExNext(ITEM_BACK_TO_GAME , ITEM_HIDE_MENU, ITEM_DUMMY5   , ITEM_CONFIG       );
    relateItemToExNext(ITEM_CONFIG       , ITEM_DUMMY2, ITEM_DUMMY6   , ITEM_BACK_TO_TITLE);
    relateItemToExNext(ITEM_BACK_TO_TITLE, ITEM_DUMMY3, ITEM_DUMMY7   , ITEM_REBOOT    );
    relateItemToExNext(ITEM_REBOOT       , ITEM_DUMMY4, ITEM_QUIT_GAME, ITEM_BACK_TO_GAME );
    relateAllItemToCancel(ITEM_BACK_TO_GAME);

    //メニューカーソルを設定
    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    selectItem(0); //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加
    //コンフィグサブメニュー
    addSubMenu(NEW MenuBoardConfig("config"));

    toggle_HIDE_MENU_ = false;
}
bool MenuBoardPause::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN) ? true : false;
}
bool MenuBoardPause::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP) ? true : false;
}
bool MenuBoardPause::condSelectExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT) ? true : false;
}
bool MenuBoardPause::condSelectExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT) ? true : false;
}

void MenuBoardPause::processBehavior() {
    MenuBoard::processBehavior();

    //サブメニュー判定

    int selected = getSelectedIndex();
    if (selected == ITEM_QUIT_GAME) { //自身のメニューが"ITEM_QUIT"を指している場合
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            PostQuitMessage(0);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    if (selected == ITEM_REBOOT) { //自身のメニューが"ITEM_REBOOT"を指している場合
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            VioletVreath::God::g_should_reboot_ = true; //再起動フラグセット
            PostQuitMessage(0);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    if (selected == ITEM_BACK_TO_TITLE) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            sinkCurrentSubMenu();
            sinkMe();
            _TRACE_("MenuBoardPause::processBehavior() throwEventUpperTree(EVENT_BACK_TO_TITLE)");
            throwEventUpperTree(EVENT_BACK_TO_TITLE);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    if (selected != ITEM_HIDE_MENU) {
        if (toggle_HIDE_MENU_) {
            toggle_HIDE_MENU_ = false;
            _x += PX_C(PROPERTY::GAME_BUFFER_WIDTH);
        }
    }
}

void MenuBoardPause::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK_TO_GAME) {
        sinkMe();
    } else if (prm_item_index == ITEM_CONFIG) {
        riseSubMenu(1, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //コンフィグメニュー起動
    } else if (prm_item_index == ITEM_BACK_TO_TITLE) {
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y + PX_C(50)); //確認メニュー起動
    } else if (prm_item_index == ITEM_REBOOT) {
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y + PX_C(50)); //確認メニュー起動
    } else if (prm_item_index == ITEM_QUIT_GAME) {
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y + PX_C(50)); //確認メニュー起動
    } else if (prm_item_index == ITEM_HIDE_MENU) {
        if (toggle_HIDE_MENU_) {
            toggle_HIDE_MENU_ = false;
            _x += PX_C(PROPERTY::GAME_BUFFER_WIDTH);
        } else {
            toggle_HIDE_MENU_ = true;
            _x -= PX_C(PROPERTY::GAME_BUFFER_WIDTH);
        }
    }
}
void MenuBoardPause::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardPause::~MenuBoardPause() {
}
