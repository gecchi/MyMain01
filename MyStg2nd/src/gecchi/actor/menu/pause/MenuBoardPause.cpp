#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;
enum {
    PAUSE_MENU_ITEM_BACK_TO_GAME = 0 ,
    PAUSE_MENU_ITEM_CONFIG,
    PAUSE_MENU_ITEM_BACK_TO_TITLE,
    PAUSE_MENU_ITEM_QUIT_GAME,
    PAUSE_MENU_ITEM_DUMMY1,
    PAUSE_MENU_ITEM_DUMMY2,
    PAUSE_MENU_ITEM_DUMMY3,
    PAUSE_MENU_ITEM_DUMMY4,
    PAUSE_MENU_ITEM_DUMMY5,
    PAUSE_MENU_ITEM_DUMMY6,
    PAUSE_MENU_ITEM_DUMMY7,
    PAUSE_MENU_ITEM_CANCEL
};

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
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("menuitem");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX2CO(10+((i/4)*300)), PX2CO(100+((i%4)*40)), 0);
    }
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


    relationItemCancel(PAUSE_MENU_ITEM_BACK_TO_GAME);

    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);
    config(30, 8, 0.2, 0.7);

    setSelectedItemIndex(0); //‰Šú‘I‘ð
    setTargetLocate(PX2CO(300), PX2CO(10),  0, -PX2CO(100));
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

void MenuBoardPause::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == PAUSE_MENU_ITEM_BACK_TO_GAME) {
        sink();
    } else if (prm_item_index == PAUSE_MENU_ITEM_QUIT_GAME) {
        PostQuitMessage(0);
    }
}
MenuBoardPause::~MenuBoardPause() {
}
