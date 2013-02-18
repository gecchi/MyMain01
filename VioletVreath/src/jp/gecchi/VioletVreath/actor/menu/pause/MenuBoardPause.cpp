#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardPause";
    //���j���[�E�B���h�E�ݒ�
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
    _Z = 5; //�v���C�I���e�B

    //���j���[�A�C�e���i�I���j�ݒ�
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
    for (int i = ITEM_BACK_TO_GAME; i <= ITEM_HOGEHOGE; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100+((i/4)*200)), PX_C(100+((i%4)*30)), -1);
    }
    //���j���[�A�C�e���i�I��s�j�ݒ�
    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("[PAUSE MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispLabel(pMsg, PX_C(100), PX_C(20), -1);
    //���ʂȃ��j���[�J�[�\���I�[�_�[���\�z
    relateItemExNext(ITEM_BACK_TO_GAME , ITEM_DUMMY1, ITEM_DUMMY5  , ITEM_CONFIG       );
    relateItemExNext(ITEM_CONFIG       , ITEM_DUMMY2, ITEM_DUMMY6  , ITEM_BACK_TO_TITLE);
    relateItemExNext(ITEM_BACK_TO_TITLE, ITEM_DUMMY3, ITEM_DUMMY7  , ITEM_QUIT_GAME    );
    relateItemExNext(ITEM_QUIT_GAME    , ITEM_DUMMY4, ITEM_HOGEHOGE, ITEM_BACK_TO_GAME );
    relateAllItemCancel(ITEM_BACK_TO_GAME);

    //���j���[�J�[�\����ݒ�
    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedIndex(0); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
                                            //�ォ�牺�֏����X���C�h������
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No �₢���킹���j���[���T�u���j���[�ɒǉ�
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
    StringBoardMenu* pSubConfirm = getSubMenu(0);
    if (pSubConfirm) {
        if (pSubConfirm->isJustDecided()) {
            if (pSubConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {

                if (getSelectedIndex() == ITEM_QUIT_GAME) {
                    PostQuitMessage(0);
                }

            } else if (pSubConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSubMenu();
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
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50)); //�T�u���j���[�N��
    }
}
void MenuBoardPause::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardPause::~MenuBoardPause() {
}
