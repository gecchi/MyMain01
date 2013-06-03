#include "stdafx.h"
#include "MenuBoardPause.h"

#include "CursorPauseMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

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
          "QUIT",           //3

          "DUMMY1",         //4
          "DUMMY2",         //5
          "DUMMY3",         //6
          "DUMMY4",         //7

          "DUMMY5",         //8
          "DUMMY6",         //9
          "DUMMY7",         //10
          "HOGEHOGE"        //11
    };
    for (int i = ITEM_BACK_TO_GAME; i <= ITEM_HOGEHOGE; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100+((i/4)*200)), PX_C(100+((i%4)*30)));
    }
    //メニューアイテム（選択不可）設定
    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("[PAUSE MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(100), PX_C(20));

    //特別なメニューカーソルオーダーを構築
    relateItemExNext(ITEM_BACK_TO_GAME , ITEM_DUMMY1, ITEM_DUMMY5  , ITEM_CONFIG       );
    relateItemExNext(ITEM_CONFIG       , ITEM_DUMMY2, ITEM_DUMMY6  , ITEM_BACK_TO_TITLE);
    relateItemExNext(ITEM_BACK_TO_TITLE, ITEM_DUMMY3, ITEM_DUMMY7  , ITEM_QUIT_GAME    );
    relateItemExNext(ITEM_QUIT_GAME    , ITEM_DUMMY4, ITEM_HOGEHOGE, ITEM_BACK_TO_GAME );
    relateAllItemCancel(ITEM_BACK_TO_GAME);

    //メニューカーソルを設定
    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    selectItem(0); //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加
    //コンフィグサブメニュー
    addSubMenu(NEW MenuBoardConfig("config"));
}
bool MenuBoardPause::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardPause::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardPause::condSelectExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardPause::condSelectrExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
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
            sinkSubMenu();
        }
    } if (selected == ITEM_BACK_TO_TITLE) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            sinkSubMenu();
            sink();
            _TRACE_("MenuBoardPause::processBehavior() throwEventUpperTree(EVENT_BACK_TO_TITLE)");
            throwEventUpperTree(EVENT_BACK_TO_TITLE);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkSubMenu();
        }
    }

}

void MenuBoardPause::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK_TO_GAME) {
        sink();
    } else if (prm_item_index == ITEM_CONFIG) {
        riseSubMenu(1, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //コンフィグメニュー起動
    } else if (prm_item_index == ITEM_BACK_TO_TITLE) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50)); //確認メニュー起動
    } else if (prm_item_index == ITEM_QUIT_GAME) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50)); //確認メニュー起動
    }
}
void MenuBoardPause::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardPause::~MenuBoardPause() {
}
