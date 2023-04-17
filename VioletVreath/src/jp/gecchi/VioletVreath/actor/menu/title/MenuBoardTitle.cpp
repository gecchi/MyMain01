#include "MenuBoardTitle.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "CursorTitleMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteFont32x64.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelGecchi32Font.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardKeyConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardScreenConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardSoundConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/name_entry/MenuBoardNameEntry.h"



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardTitle::MenuBoardTitle(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardTitle";
    setWidth(PX_C(14*32));
    setHeight(PX_C(6*32));

    //���j���[�A�C�e���ݒ�
    const char* apItemStr[] = {
          "GAME START",   //0
          "KEY CONFIG",
          "SOUND CONFIG",
          "SCREEN CONFIG",
          "NAME ENTRY(TEST)",
          "REBOOT",
          "QUIT",
    };
    for (int i = ITEM_GAME_START; i < ITEM_BANPEI; i++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        pLabel->getAlphaFader()->setRange(0, 0.6);
        pLabel->getAlphaFader()->transitionLinearToTop(1);
        addItem(pLabel, PX_C(200), PX_C(40+(i*18)));
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
    //�T�u���j���[
    addSubMenu(NEW MenuBoardConfirm("confirm"));            //MENU_CONFIRM = 0 ,
    addSubMenu(NEW MenuBoardKeyConfig("key_config"));       //MENU_KEY_CONFIG,
    addSubMenu(NEW MenuBoardSoundConfig("sound_config"));   //MENU_SOUND_CONFIG,
    addSubMenu(NEW MenuBoardScreenConfig("screen_config")); //MENU_SCREEN_CONFIG,

    FontSpriteActor* pLabelInputedName = NEW SpriteFont32x64("InputedName");
    FontSpriteActor*  pLabelSelectedChar = NEW SpriteFont32x64("SelectedChar");
    MenuBoardNameEntry* pNameEntryBoard = NEW MenuBoardNameEntry("pNameEntryBoard_");
    pNameEntryBoard->setNameFontBoard(pLabelInputedName, pLabelSelectedChar);
    pNameEntryBoard->addLabel(pLabelInputedName, PX_C(100), PX_C(-200), 0);
    pLabelSelectedChar->setMaterialColor(1.0, 1.0, 0);
    pNameEntryBoard->addLabel(pLabelSelectedChar, PX_C(100), PX_C(-200), 0);
    addSubMenu(pNameEntryBoard);       //MENU_NAME_ENTRY,
}
bool MenuBoardTitle::condSelectNext() {
    return VVB->isAutoRepeat(0, VVB_UI_DOWN);
}
bool MenuBoardTitle::condSelectPrev() {
    return VVB->isAutoRepeat(0, VVB_UI_UP);
}
bool MenuBoardTitle::condSelectExNext() {
    return false;
}
bool MenuBoardTitle::condSelectExPrev() {
    return false;
}

void MenuBoardTitle::onSelect(int prm_from_index, int prm_selected_index) {
    if (prm_from_index > -1) {
        //��I�����ڂ͓_�ł����Ȃ�
        GgafDx::FigureActor* pItem = getItem(prm_from_index);
        pItem->getAlphaFader()->transitionLinearToTop(1);
    }
    //�I�����ڂ�_��
    if (prm_selected_index > -1) {
        GgafDx::FigureActor* pItem = getItem(prm_selected_index);
        pItem->getAlphaFader()->beat(20, 10, 0, 10, -1);

//        GgafDx::FigureActor* pMainCursor = getMainCursor();
//        pixcoord w = ((FontBoardActor*)pItem)->getTotalWidth();
        //TODO: w�ɂ���ăJ�[�\���̑傫���ς��Ă݂�H
    }


}

void MenuBoardTitle::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_GAME_START) {
        //GameTitleScene�N���X���ŃC�x���g���s
    } else if (prm_item_index == ITEM_KEY_CONFIG) {
        //�L�[���͐ݒ胁�j���[�N��
        riseSubMenu(MENU_KEY_CONFIG, PX_C(50), PX_C(10));
    } else if (prm_item_index == ITEM_SOUND_CONFIG) {
        //���ʐݒ胁�j���[�N��
        riseSubMenu(MENU_SOUND_CONFIG, PX_C(50), PX_C(10));
    } else if (prm_item_index == ITEM_SCREEN_CONFIG) {
        //��ʐݒ胁�j���[�N��
        riseSubMenu(MENU_SCREEN_CONFIG, PX_C(50), PX_C(10));
    } else if (prm_item_index == ITEM_NAME_ENTRY) {
        //�l�[���G���g���[�N�� TODO:TEST
        riseSubMenu(MENU_NAME_ENTRY, PX_C(50), PX_C(10));
    } else if (prm_item_index == ITEM_REBOOT) {
        //�m�F���j���[�N��
        riseSubMenu(MENU_CONFIRM, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y);
    } else if (prm_item_index == ITEM_QUIT) {
        //�m�F���j���[�N��
        riseSubMenu(MENU_CONFIRM, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y);
    }
}

void MenuBoardTitle::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}

void MenuBoardTitle::processBehavior() {
    MenuBoard::processBehavior();
    int selected = getSelectedIndex();
    if (selected == ITEM_QUIT) { //���g�̃��j���[��"ITEM_QUIT"���w���Ă���ꍇ
        //�m�F���j���[�̌��ʂ̐U�镑�����s
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu();
        if (pSubConfirm->hasJustDecidedOk()) {
            PostQuitMessage(0);
        } else if (pSubConfirm->hasJustDecidedCancel()) {
            sinkCurrentSubMenu();
        } else {

        }
    } else if (selected == ITEM_REBOOT) { //���g�̃��j���[��"ITEM_REBOOT"���w���Ă���ꍇ
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu();
        if (pSubConfirm->hasJustDecidedOk()) {
            Caretaker::reboot(); //�ċN���I
        } else if (pSubConfirm->hasJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

//    if (getRisingSubMenu()) {
//        getSelectedItem()->setAlpha(1.0); //�_�ł��~���Ė��邭�I
//    }

}

void MenuBoardTitle::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    //�f�o�b�O
    GgafCore::Phase* pPhase = getPhase();
    if (prm_event_val == EVENT_MENU_NAMEENTRY_DONE) {
        _TRACE_("MenuBoardTitle::onCatchEvent(EVENT_MENU_NAMEENTRY_DONE)");
        getSubMenu(MENU_NAME_ENTRY)->sinkMe(); //�l�[���G���g���[����
    }
    //�f�o�b�O
}
MenuBoardTitle::~MenuBoardTitle() {
}
