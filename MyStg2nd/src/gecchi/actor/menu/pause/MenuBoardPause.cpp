#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
           MenuActor<DefaultBoardActor>(prm_name, "TurboMeter") {
}
    _class_name = "MenuBoardPause";
    GgafDxDrawableActor** papMenuItem[] = {
          NEW LabelGecchi16Font("BACK TO GAME");
          NEW LabelGecchi16Font("CONFIG");
          NEW LabelGecchi16Font("BACK TO TITLE");
          NEW LabelGecchi16Font("QUIT GAME");
    };
    _max_menu_item = 4;
    _papMenuItemLabel = NEW LabelGecchi16Font*[_max_menu_item];
    for (int i = 0; i < _max_menu_item; i++) {
        _papMenuItemLabel[i] = NEW LabelGecchi16Font("menu_item");
        _papMenuItemLabel[i]->_Z = 1;
        _papMenuItemLabel[i]->update(item[i], ALIGN_CENTER, VALIGN_MIDDLE);
        _papMenuItemLabel[i]->inactivateImmediately();
        getDirector()->addSubGroup(_papMenuItemLabel[i]);
    }

    _pCursor001= NEW Cursor001("Cursor001");
    _pCursor001->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    _pCursor001->inactivateImmediately();
    getDirector()->addSubGroup(_pCursor001);

    _pSeCon_exec = connectSeManager("click07_2");
    _active_item = 0;

}

void MenuBoardPause::initialize() {

    onReset();
}

void MenuBoardPause::onReset() {
}

void MenuBoardPause::onActive() {
}

void MenuBoardPause::processBehavior() {
}


void MenuBoardPause::processJudgement() {
}

void MenuBoardPause::onInactive() {
}

MenuBoardPause::~MenuBoardPause() {
}
