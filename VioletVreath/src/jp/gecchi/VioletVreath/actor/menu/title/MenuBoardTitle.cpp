#include "stdafx.h"
#include "MenuBoardTitle.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "CursorTitleMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"

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
    //���j���[�A�C�e���ݒ�
    const char* apItemStr[] = {
          "GAME START",   //0
          "CONFIG",       //1
          "REBOOT",       //2
          "QUIT",         //3
    };
    for (int i = ITEM_GAME_START; i <= ITEM_QUIT; i++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        pLabel->setAlpha(0.7);
        addItem(pLabel, PX_C(100), PX_C(40+(i*18)));
    }
    //�L�����Z���������ړ���A�C�e��
    relateAllItemToCancel(ITEM_QUIT);
    //�J�[�\���ݒ�
    CursorTitleMenu* pCursor = NEW CursorTitleMenu("CursorTitleMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    //�X���C�h�\���̐ݒ�
    setTransition(10, PX_C(0), +PX_C(100));
    //�����I��
    selectItem(ITEM_GAME_START);
    //�m�F�T�u���j���[
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0
    //�R���t�B�O�T�u���j���[
    addSubMenu(NEW MenuBoardConfig("config"));
}
bool MenuBoardTitle::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardTitle::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardTitle::condSelectExNext() {
    return false;
}
bool MenuBoardTitle::condSelectExPrev() {
    return false;
}

void MenuBoardTitle::onSelect(int prm_from, int prm_to) {
    if (prm_from > -1) {
        //��I�����ڂ͓_�ł����Ȃ�
        //�ŁA������ƈÂ�
        getItem(prm_from)->_pAFader->reset();
        getItem(prm_from)->_pAFader->setAlpha(0.7);
        getItem(prm_from)->_pAFader->behave();
    }
    //�I�����ڂ�_��
    if (prm_to > -1) {
        getItem(prm_to)->_pAFader->beat(20,10,0,0,-1);
    }
}

void MenuBoardTitle::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_GAME_START) {
        //GameTitleScene�N���X���ŃC�x���g���s
    } else if (prm_item_index == ITEM_CONFIG) {
        //CONFIG���j���[�N��
        riseSubMenu(1, PX_C(50), PX_C(50));
    } else if (prm_item_index == ITEM_REBOOT) {
        //�m�F���j���[�N��
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y);
    } else if (prm_item_index == ITEM_QUIT) {
        //�m�F���j���[�N��
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y);
    }
}

void MenuBoardTitle::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

void MenuBoardTitle::processBehavior() {
    MenuBoard::processBehavior();
    int selected = getSelectedIndex();
    if (selected == ITEM_QUIT) { //���g�̃��j���[��"ITEM_QUIT"���w���Ă���ꍇ
        //�m�F���j���[�̌��ʂ̐U�镑�����s
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            PostQuitMessage(0);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkCurrentSubMenu();
        } else {

        }
    } else if (selected == ITEM_REBOOT) { //���g�̃��j���[��"ITEM_REBOOT"���w���Ă���ꍇ
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) {
            VioletVreath::God::g_should_reboot_ = true; //�ċN���t���O�Z�b�g
            PostQuitMessage(0);
        } else if (pSubConfirm->isJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    GgafDxDrawableActor* pItem = getSelectedItem();
    if (getRisingSubMenu()) {
        pItem->setAlpha(1.0); //�_�ł��~
    } else {
        pItem->_pAFader->behave();
    }

}
MenuBoardTitle::~MenuBoardTitle() {
}
