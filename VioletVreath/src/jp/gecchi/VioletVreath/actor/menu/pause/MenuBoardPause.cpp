#include "MenuBoardPause.h"

#include "CursorPauseMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardKeyConfig.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardSoundConfig.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardPause::MenuBoardPause(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardPause";
    //���j���[�E�B���h�E�ݒ�
    update("%&&&&&&&&&&&&&&&'\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           ")***************+\n"
           "-.............../");

    //���j���[�A�C�e���i�I���j�ݒ�
    const char* apItemStr[] = {
          "BACK TO GAME",
          "GO TO TITLE",
          "HIDE MENU",
          "DUMMY1",

          "KEY CONFIG",
          "SOUND CONFIG",
          "REBOOT",
          "QUIT GAME"
    };
    for (int i = ITEM_BACK_TO_GAME; i < ITEM_BANPEI; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100+((i/4)*300)), PX_C(100+((i%4)*30)));
    }
    //���j���[�A�C�e���i�\�����x���j�ݒ�
    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("[PAUSE MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addLabel(pLabel_title, PX_C(100), PX_C(20));

    //���ʂȃ��j���[�J�[�\���I�[�_�[���\�z
    relateItemToExNext(ITEM_BACK_TO_GAME , ITEM_KEY_CONFIG ,  ITEM_GO_TO_TITLE );
    relateItemToExNext(ITEM_GO_TO_TITLE  , ITEM_SOUND_CONFIG, ITEM_HIDE_MENU   );
    relateItemToExNext(ITEM_HIDE_MENU    , ITEM_REBOOT      , ITEM_DUMMY1      );
    relateItemToExNext(ITEM_DUMMY1       , ITEM_QUIT_GAME   , ITEM_BACK_TO_GAME);
    relateAllItemToCancel(ITEM_BACK_TO_GAME);

    //���j���[�J�[�\����ݒ�
    CursorPauseMenu* pCursor = NEW CursorPauseMenu("CursorPauseMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    selectItem(0); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
                                            //�ォ�牺�֏����X���C�h������
    addSubMenu(NEW MenuBoardConfirm("confirm"));            //MENU_CONFIRM = 0 ,
    addSubMenu(NEW MenuBoardKeyConfig("key_config"));       //MENU_KEY_CONFIG,
    addSubMenu(NEW MenuBoardSoundConfig("sound_config"));   //MENU_SOUND_CONFIG,

    toggle_HIDE_MENU_ = false;
}
void MenuBoardPause::onRise() {
    getItem(ITEM_DUMMY1)->inactivate(); //�����e�X�g
    MenuBoard::onRise();
}
bool MenuBoardPause::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardPause::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardPause::condSelectExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardPause::condSelectExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}

void MenuBoardPause::processBehavior() {
    MenuBoard::processBehavior();
    //�T�u���j���[����

    int selected = getSelectedIndex();
    if (selected == ITEM_QUIT_GAME) { //���g�̃��j���[��"ITEM_QUIT"���w���Ă���ꍇ
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(MENU_CONFIRM);
        if (pSubConfirm->hasJustDecidedOk()) {
            PostQuitMessage(0);
        } else if (pSubConfirm->hasJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    if (selected == ITEM_REBOOT) { //���g�̃��j���[��"ITEM_REBOOT"���w���Ă���ꍇ
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(MENU_CONFIRM);
        if (pSubConfirm->hasJustDecidedOk()) {
            God::reboot(); //�ċN���I
        } else if (pSubConfirm->hasJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    if (selected == ITEM_GO_TO_TITLE) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(MENU_CONFIRM);
        if (pSubConfirm->hasJustDecidedOk()) {
            sinkCurrentSubMenu();
            sinkMe();
            _TRACE_(FUNC_NAME<<" throwEventUpperTree(EVENT_GO_TO_TITLE)");
            throwEventUpperTree(EVENT_GO_TO_TITLE);
        } else if (pSubConfirm->hasJustDecidedCancel()) {
            sinkCurrentSubMenu();
        }
    }

    if (selected != ITEM_HIDE_MENU) {
        if (toggle_HIDE_MENU_) {
            toggle_HIDE_MENU_ = false;
            _x += PX_C(PROPERTY::GAME_BUFFER_WIDTH);
        }
    }
}

void MenuBoardPause::onDecision(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK_TO_GAME) {
        sinkMe();
    } else if (prm_item_index == ITEM_KEY_CONFIG) {
        riseSubMenu(MENU_KEY_CONFIG, PX_C(50), PX_C(10));
    } else if (prm_item_index == ITEM_SOUND_CONFIG) {
       riseSubMenu(MENU_SOUND_CONFIG, PX_C(50), PX_C(10));
    } else if (prm_item_index == ITEM_GO_TO_TITLE) {
        riseSubMenu(MENU_CONFIRM, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y + PX_C(50)); //�m�F���j���[�N��
    } else if (prm_item_index == ITEM_REBOOT) {
        riseSubMenu(MENU_CONFIRM, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y + PX_C(50)); //�m�F���j���[�N��
    } else if (prm_item_index == ITEM_QUIT_GAME) {
        riseSubMenu(MENU_CONFIRM, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y + PX_C(50)); //�m�F���j���[�N��
    } else if (prm_item_index == ITEM_HIDE_MENU) {
        if (toggle_HIDE_MENU_) {
            toggle_HIDE_MENU_ = false;
            _x += PX_C(PROPERTY::GAME_BUFFER_WIDTH);
        } else {
            toggle_HIDE_MENU_ = true;
            _x -= PX_C(PROPERTY::GAME_BUFFER_WIDTH);
        }
    }
}
void MenuBoardPause::onCancel(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) {
}

MenuBoardPause::~MenuBoardPause() {
}
