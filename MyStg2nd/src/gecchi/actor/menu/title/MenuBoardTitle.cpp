#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MenuBoardTitle::MenuBoardTitle(const char* prm_name) :
        MenuBoard(prm_name, "Menuback001") {
    _class_name = "MenuBoardPause";
    //���j���[�E�B���h�E�ݒ�
    setScaleR(160, 90, 1);
    //���j���[�A�C�e���ݒ�
    char* apItemStr[] = {
          "GAME START",   //0
          "CONFIG",       //1
          "DEBUG",        //2
          "QUIT",         //3
    };
    for (int i = 0; i <= ITEM_QUIT; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addSelectItem(pLabel, PX2CO(80), PX2CO(5+(i*20)));
    }
    //�L�����Z���������ړ���A�C�e��
    relationItemCancel(ITEM_QUIT);
    //�J�[�\���ݒ�
    CursorTitleMenu* pCursor = NEW CursorTitleMenu("CursorTitleMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor, 0, 0, 0, 8, 0.2, 0.7);
    //�X���C�h�\���ݒ�
    setTransition(10, PX2CO(0), +PX2CO(100));
    //�����I��
    setSelectedItemIndex(ITEM_GAME_START);
    //�m�F�T�u���j���[
    _pConfirmMenu = NEW MenuBoardConfirm("confirm");
    addSubLast(_pConfirmMenu);
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

void MenuBoardTitle::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

void MenuBoardTitle::riseConfirm() {
    riseSub(_pConfirmMenu,
            getSelectedItem()->_X + PX2CO(50), getSelectedItem()->_Y + PX2CO(50));
}
void MenuBoardTitle::sinkConfirm() {
    sinkSub();
}

MenuBoardTitle::~MenuBoardTitle() {
}
