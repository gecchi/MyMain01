#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardTitle::MenuBoardTitle(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardPause";
    //���j���[�E�B���h�E�ݒ�
    update("%&&&&&&&'\n"
           ")*******+\n"
           ")*******+\n"
           ")*******+\n"
           ")*******+\n"
           "-......./");
    _Z = 3;
    //���j���[�A�C�e���ݒ�
    char* apItemStr[] = {
          "GAME START",   //0
          "CONFIG",       //1
          "DEBUG",        //2
          "QUIT",         //3
    };
    for (int i = ITEM_GAME_START; i <= ITEM_QUIT; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100), PX_C(40+(i*18)), -1);
    }
    //�L�����Z���������ړ���A�C�e��
    relateAllItemCancel(ITEM_QUIT);
    //�J�[�\���ݒ�
    CursorTitleMenu* pCursor = NEW CursorTitleMenu("CursorTitleMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);
    //�X���C�h�\���̐ݒ�
    setTransition(10, PX_C(0), +PX_C(100));
    //�����I��
    setSelectedIndex(ITEM_GAME_START);
    //�m�F�T�u���j���[
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0
    //�R���t�B�O�T�u���j���[
    addSubMenu(NEW MenuBoardConfig("config"));
}
bool MenuBoardTitle::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardTitle::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardTitle::condMoveCursorExNext() {
    return false;
}
bool MenuBoardTitle::condMoveCursorExPrev() {
    return false;
}
void MenuBoardTitle::processBehavior() {
    MenuBoard::processBehavior();

    if (getSelectedIndex() == ITEM_QUIT) { //���g�̃��j���[��"ITEM_QUIT"���w���Ă���ꍇ
        //�m�F���j���[�̌��ʂ̐U�镑�����s
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->wasDecidedOk()) {
            PostQuitMessage(0);
        } else if (pSubConfirm->wasDecidedCancel()) {
            sinkSubMenu();
        } else {

        }
    } else if (getSelectedIndex() == ITEM_QUIT) {

    }

}
void MenuBoardTitle::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_GAME_START) {
        //GameTitleScene�N���X���ŃC�x���g���s
    } else if (prm_item_index == ITEM_CONFIG) {
        riseSubMenu(1, PX_C(50), PX_C(50));
    } else if (prm_item_index == ITEM_DEBUG) {
        //
    } else if (prm_item_index == ITEM_QUIT) {
        //�m�F���j���[�N��
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y);
    }
}
void MenuBoardTitle::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardTitle::~MenuBoardTitle() {
}
