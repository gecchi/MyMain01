#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
        DefaultBoardSetMenu(prm_name, "TurboMeter") {
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
          "DUMMY8"          //11
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
    relationItemExNext(9, 0);
    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor, 8, 0.2, 0.7);
    setSelectedItemIndex(0); //初期選択

    locate(PX2CO(300),PX2CO(10));

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "click07_2"); //メーター移動
    _pSeTransmitter->set(1, "SwingA@11"); //レベルダウン実行
}
bool MenuBoardPause::condCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardPause::condCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardPause::condCursorExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardPause::condCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoardPause::condCursorCancel() {
    return VB->isAutoRepeat(VB_UI_CANCEL);
}
void MenuBoardPause::moveCursor() {
    DefaultBoardSetMenu::moveCursor();
    _pSeTransmitter->playImmed(0);
}

void MenuBoardPause::initialize() {
}

void MenuBoardPause::onReset() {
}

void MenuBoardPause::onActive() {
	_X = 0;
	_Y = 0;
}

void MenuBoardPause::processBehavior() {
    DefaultBoardSetMenu::processBehavior();
	_X += PX2CO(2);
	_Y += PX2CO(1);
}

void MenuBoardPause::processJudgement() {
}

void MenuBoardPause::onInactive() {
}

MenuBoardPause::~MenuBoardPause() {
}
