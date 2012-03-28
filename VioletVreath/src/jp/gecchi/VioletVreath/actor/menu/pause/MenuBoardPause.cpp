#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
        MenuBoard(prm_name, "TurboMeter") {
    _class_name = "MenuBoardPause";
    char* apItemStr[] = {
          "BACK TO GAME",   //0
          "CONFIG",         //1
          "BACK TO TITLE",  //2
          "QUIT GAME",      //3

          "DUMMY1",         //4
          "DUMMY2",         //5
          "DUMMY3",         //6
          "DUMMY4",         //7

          "DUMMY5",         //8
          "DUMMY6",         //9
          "DUMMY7",         //10
          "HOGEHOGE"        //11
    };
    for (int i = 0; i < 12; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addSelectItem(pLabel, P2C(10+((i/4)*300)), P2C(100+((i%4)*40)));
    }

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("PAUSE MENU !!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispActor(pMsg, P2C(100), P2C(20));

    relationItemExNext(0, 4);
    relationItemExNext(4, 8);
    relationItemExNext(8, 1);

    relationItemExNext(1, 5);
    relationItemExNext(5, 9);
    relationItemExNext(9, 2);

    relationItemExNext(2, 6);
    relationItemExNext(6, 10);
    relationItemExNext(10, 3);

    relationItemExNext(3, 7);
    relationItemExNext(7, 11);
    relationItemExNext(11, 0);

    relationItemCancel(ITEM_BACK_TO_GAME);

    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor, 8, 0.2, 0.7);
    setSelectedItemIndex(0); //初期選択
    setTransition(30, P2C(0), -P2C(100)); //上から下へ少しスライド
    pConfirmMenu_ = NEW MenuBoardConfirm("confirm");
    addSubLast(pConfirmMenu_);
}
bool MenuBoardPause::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardPause::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardPause::condMoveCursorExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardPause::condMoveCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}

void MenuBoardPause::processBehavior() {
    MenuBoard::processBehavior();

    //サブメニュー判定
    DefaultBoardMenu* pSub = getSubMenu();
    if (pSub) {
        if (pSub->isJustDecided()) {
            if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {

                if (getSelectedIndex() == MenuBoardPause::ITEM_QUIT_GAME) {
                    PostQuitMessage(0);
                }

            } else if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSub();
            } else {
            }
        } else {

        }
    }
}

void MenuBoardPause::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == MenuBoardPause::ITEM_BACK_TO_GAME) {
        sink();
    } else if (prm_item_index == MenuBoardPause::ITEM_QUIT_GAME) {
        riseSub(pConfirmMenu_, getSelectedItem()->_X + P2C(50), getSelectedItem()->_Y + P2C(50)); //サブメニュー起動
    }
}
MenuBoardPause::~MenuBoardPause() {
}
