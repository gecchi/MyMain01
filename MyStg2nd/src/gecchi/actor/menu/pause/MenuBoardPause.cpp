#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
           MenuActor<DefaultBoardActor>(prm_name, "TurboMeter") {
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
        pLabel->update(apItemStr[i]);
        addItem(pLabel, PX2CO(10+((i/4)*200)), PX2CO(100+((i%4)*20)), 0);
    }
    relationItemExNext(0, 4);
    relationItemExNext(4, 8);
    relationItemExNext(8, 1);
    relationItemExNext(1, 5);
    relationItemExNext(5, 9);
    relationItemExNext(9, 0);
    setCursor(NEW CursorPauseMenu("CursorPauseMenu"), 10, 0.2, 0.7);
    setSelectedItemIndex(0); //èâä˙ëIë

    locate(PX2CO(300),PX2CO(10));
}

void MenuBoardPause::initialize() {
}

void MenuBoardPause::onReset() {
}

void MenuBoardPause::onActive() {
}

void MenuBoardPause::processBehavior() {
    MenuActor<DefaultBoardActor>::processBehavior();
}


void MenuBoardPause::processJudgement() {
}

void MenuBoardPause::onInactive() {
}

MenuBoardPause::~MenuBoardPause() {
}
