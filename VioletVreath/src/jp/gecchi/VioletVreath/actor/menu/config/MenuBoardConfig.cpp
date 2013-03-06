#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardConfig::MenuBoardConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardConfig";
    //���j���[�E�B���h�E�ݒ�
    update("%&&&&&&&&&&&'\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           ")***********+\n"
           "-.........../");

    //���j���[�A�C�e���i�I���j�ݒ�
    char* apItemStr[] = {
          "KEY CONFIG",
          "SOUND CONFIG",
          "<- BACK"
    };
    for (int i = ITEM_KEY_CONFIG; i <= ITEM_BACK; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+((i%4)*30)));
    }
    //�\�����x���ݒ�
    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("[CONFIG MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(100), PX_C(40));
    //�L�����Z���A�C�e���ݒ�
    relateAllItemCancel(ITEM_BACK);

    //���j���[�J�[�\����ݒ�
    CursorConfigMenu* pCursor = NEW CursorConfigMenu("CursorConfigMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    selectItem(ITEM_BACK); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), +PX_C(100)); //�g�����W�V�����i�\����\�����̋����j

    addSubMenu(NEW MenuBoardKeyConfig("key_config"));       //0��
    addSubMenu(NEW MenuBoardSoundConfig("sound_config"));   //1��
}
bool MenuBoardConfig::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardConfig::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}

void MenuBoardConfig::onRise() {
    selectItem(ITEM_KEY_CONFIG); //�J�[�\���̏����I���A�C�e����ݒ�
    MenuBoard::onRise();
}

void MenuBoardConfig::processBehavior() {
    MenuBoard::processBehavior();
}

void MenuBoardConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK) {
        sink();
    } else if (prm_item_index == ITEM_KEY_CONFIG) {
        riseSubMenu(0, PX_C(50), PX_C(10)); //keyconfig���j���[�N��
    } else if (prm_item_index == ITEM_SOUND_CONFIG) {
        riseSubMenu(1,  PX_C(50), PX_C(10)); //soundconfig���j���[�N��
    }
}
void MenuBoardConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardConfig::~MenuBoardConfig() {
}
