#include "stdafx.h"
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
        addSelectItem(pLabel, PX_C(10+((i/4)*300)), PX_C(100+((i%4)*40)));
    }

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("PAUSE MENU !!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispActor(pMsg, PX_C(100), PX_C(20));

    relationItemExNext(ITEM_BACK_TO_GAME , ITEM_DUMMY1       );
    relationItemExNext(ITEM_DUMMY1       , ITEM_DUMMY5       );
    relationItemExNext(ITEM_DUMMY5       , ITEM_CONFIG       );

    relationItemExNext(ITEM_CONFIG       , ITEM_DUMMY2       );
    relationItemExNext(ITEM_DUMMY2       , ITEM_DUMMY6       );
    relationItemExNext(ITEM_DUMMY6       , ITEM_BACK_TO_TITLE);

    relationItemExNext(ITEM_BACK_TO_TITLE, ITEM_DUMMY3       );
    relationItemExNext(ITEM_DUMMY3       , ITEM_DUMMY7       );
    relationItemExNext(ITEM_DUMMY7       , ITEM_QUIT_GAME    );

    relationItemExNext(ITEM_QUIT_GAME    , ITEM_DUMMY4       );
    relationItemExNext(ITEM_DUMMY4       , ITEM_HOGEHOGE     );
    relationItemExNext(ITEM_HOGEHOGE     , ITEM_BACK_TO_GAME );

    relationItemCancel(ITEM_BACK_TO_GAME);

    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor, 8, 0.2, 0.7);
    setSelectedItemIndex(0); //�����I��
    setTransition(30, PX_C(0), -PX_C(100)); //�ォ�牺�֏����X���C�h
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

    //�T�u���j���[����
    DefaultBoardMenu* pSub = getSubMenu();
    if (pSub) {
        if (pSub->isJustDecided()) {
            if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {

                if (getSelectedIndex() == ITEM_QUIT_GAME) {
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
    if (prm_item_index == ITEM_BACK_TO_GAME) {
        sink();
    } else if (prm_item_index == ITEM_QUIT_GAME) {
        riseSub(pConfirmMenu_, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50)); //�T�u���j���[�N��
    }
}
MenuBoardPause::~MenuBoardPause() {
}
