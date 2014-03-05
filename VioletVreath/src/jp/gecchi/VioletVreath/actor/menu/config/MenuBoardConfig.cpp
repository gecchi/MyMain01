#include "stdafx.h"
#include "MenuBoardConfig.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "MenuBoardKeyConfig.h"
#include "MenuBoardSoundConfig.h"
#include "MenuBoardScreenConfig.h"
#include "CursorConfig001.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/gecchi/VioletVreath/God.h"

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
    const char* apItemStr[] = {
          "KEY CONFIG",
          "SOUND CONFIG",
          "SCREEN CONFIG",
          "<- BACK"
    };
    for (int i = ITEM_KEY_CONFIG; i <= ITEM_BACK; i++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+((i%4)*30)));
    }
    //�\�����x���ݒ�
    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("[CONFIG MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(100), PX_C(40));
    //�L�����Z���A�C�e���ݒ�
    relateAllItemToCancel(ITEM_BACK);

    //���j���[�J�[�\����ݒ�
    CursorConfig001* pCursor = NEW CursorConfig001("CursorConfig001");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    selectItem(ITEM_BACK); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), +PX_C(100)); //�g�����W�V�����i�\����\�����̋����j

    addSubMenu(NEW MenuBoardKeyConfig("key_config"));       //0��
    addSubMenu(NEW MenuBoardSoundConfig("sound_config"));   //1��
    addSubMenu(NEW MenuBoardScreenConfig("screen_config")); //2��
}

void MenuBoardConfig::onActive() {
    _TRACE_("MenuBoardConfig::onActive()!");
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

void MenuBoardConfig::onRiseDone() {
    _TRACE_("MenuBoardConfig::onRiseDone()!");
}

void MenuBoardConfig::processBehavior() {
    MenuBoard::processBehavior();
}

void MenuBoardConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK) {
        sinkMe();
    } else if (prm_item_index == ITEM_KEY_CONFIG) {
        riseSubMenu(0, PX_C(50), PX_C(10)); //key config���j���[�N��
    } else if (prm_item_index == ITEM_SOUND_CONFIG) {
        riseSubMenu(1,  PX_C(50), PX_C(10)); //sound config���j���[�N��
    } else if (prm_item_index == ITEM_SCREEN_CONFIG) {
        riseSubMenu(2,  PX_C(50), PX_C(10)); //screen config���j���[�N��
    }
}

void MenuBoardConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

void MenuBoardConfig::onSinkDone() {
    _TRACE_("MenuBoardConfig::onSinkDone()!");
}

MenuBoardConfig::~MenuBoardConfig() {
}
