#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardKeyConfig::MenuBoardKeyConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardKeyConfig";
    //���j���[�E�B���h�E�ݒ�
    update( "%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            ")*******************************************+\n"
            "-.........................................../");

    //���j���[�A�C�e���i�I���j�ݒ�
    char* apItemStr[] = {
          "MAIN SHOT KEY & BUTTON",
          "SUB SHOT  KEY & BUTTON",
          "TURBO     KEY & BUTTON",
          "CONTROLL  KEY & BUTTON",
          "MAGIC     KEY & BUTTON",
          "VAM       KEY & BUTTON",
          "PAUSE     KEY & BUTTON",
//          "SAVE AND EXIT", //6
//          "CANCEL"         //7
    };

    int item_index;
    for (item_index = ITEM_MAIN_SHOT; item_index <= ITEM_PAUSE; item_index++) {
        LabelFix16Font01* pLabel = NEW LabelFix16Font01("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+(item_index*20)), -1);
    }

    LabelFix16Font01* pLabel_OK = NEW LabelFix16Font01("item");
    pLabel_OK->update("OK", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350), -1);
    ITEM_INDEX_OK_ = item_index;

    LabelFix16Font01* pLabel_CANCEL = NEW LabelFix16Font01("item");
    pLabel_CANCEL->update("CANCEL", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350), -1);
    ITEM_INDEX_CANCEL_ = item_index + 1;

    paVBProperties = NEW VBProperty[item_index+1];
    for (int i = ITEM_MAIN_SHOT; i <= ITEM_PAUSE; i++) {
        paVBProperties[i].pKey = NEW LabelFix16Font01("DISP_KEY");
        paVBProperties[i].pKey->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addDispLabel(paVBProperties[i].pKey, PX_C(600), PX_C(100+(i*20)), -1);
        paVBProperties[i].pJoy = NEW LabelFix16Font01("DISP_JOY");
        paVBProperties[i].pJoy->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addDispLabel(paVBProperties[i].pJoy, PX_C(800), PX_C(100+(i*20)), -1);
    }
    paVBProperties[ITEM_MAIN_SHOT].pKey->update(GGAF_PROPERTY(MY_KEY_SHOT1  ).c_str());
    paVBProperties[ITEM_SUB_SHOT ].pKey->update(GGAF_PROPERTY(MY_KEY_SHOT2  ).c_str());
    paVBProperties[ITEM_TURBO    ].pKey->update(GGAF_PROPERTY(MY_KEY_TURBO  ).c_str());
    paVBProperties[ITEM_CONTROLL ].pKey->update(GGAF_PROPERTY(MY_KEY_OPTION ).c_str());
    paVBProperties[ITEM_MAGIC    ].pKey->update(GGAF_PROPERTY(MY_KEY_POWERUP).c_str());
    paVBProperties[ITEM_VAM      ].pKey->update(GGAF_PROPERTY(MY_KEY_VIEW   ).c_str());
    paVBProperties[ITEM_PAUSE    ].pKey->update(GGAF_PROPERTY(MY_KEY_PAUSE  ).c_str());

    paVBProperties[ITEM_MAIN_SHOT].pJoy->update(GGAF_PROPERTY(MY_JOY_SHOT1  ).c_str());
    paVBProperties[ITEM_SUB_SHOT ].pJoy->update(GGAF_PROPERTY(MY_JOY_SHOT2  ).c_str());
    paVBProperties[ITEM_TURBO    ].pJoy->update(GGAF_PROPERTY(MY_JOY_TURBO  ).c_str());
    paVBProperties[ITEM_CONTROLL ].pJoy->update(GGAF_PROPERTY(MY_JOY_OPTION ).c_str());
    paVBProperties[ITEM_MAGIC    ].pJoy->update(GGAF_PROPERTY(MY_JOY_POWERUP).c_str());
    paVBProperties[ITEM_VAM      ].pJoy->update(GGAF_PROPERTY(MY_JOY_VIEW   ).c_str());
    paVBProperties[ITEM_PAUSE    ].pJoy->update(GGAF_PROPERTY(MY_JOY_PAUSE  ).c_str());

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("SELECT AND PUSH KEY, JOY BUTTON!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispLabel(pMsg, PX_C(100), PX_C(20), -1);



    //���ʂȃ��j���[�J�[�\���I�[�_�[���\�z
    relateAllItemCancel(ITEM_INDEX_CANCEL_);

    //���j���[�J�[�\����ݒ�
    CursorKeyConfigMenu* pCursor = NEW CursorKeyConfigMenu("CursorKeyConfigMenu");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedIndex(ITEM_MAIN_SHOT); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
                                            //�ォ�牺�֏����X���C�h������
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No �₢���킹���j���[���T�u���j���[�ɒǉ�
}
bool MenuBoardKeyConfig::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardKeyConfig::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}

void MenuBoardKeyConfig::processBehavior() {
    MenuBoard::processBehavior();

    //�T�u���j���[����
    MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
    if (pSubConfirm->wasDecidedOk()) {
        //���v���p�e�B�ɕۑ����ăZ�[�u�I
        GGAF_PROPERTY(MY_KEY_SHOT1  ) = paVBProperties[ITEM_MAIN_SHOT].pKey->_draw_string;
        GGAF_PROPERTY(MY_KEY_SHOT2  ) = paVBProperties[ITEM_SUB_SHOT ].pKey->_draw_string;
        GGAF_PROPERTY(MY_KEY_TURBO  ) = paVBProperties[ITEM_TURBO    ].pKey->_draw_string;
        GGAF_PROPERTY(MY_KEY_OPTION ) = paVBProperties[ITEM_CONTROLL ].pKey->_draw_string;
        GGAF_PROPERTY(MY_KEY_POWERUP) = paVBProperties[ITEM_MAGIC    ].pKey->_draw_string;
        GGAF_PROPERTY(MY_KEY_VIEW   ) = paVBProperties[ITEM_VAM      ].pKey->_draw_string;
        GGAF_PROPERTY(MY_KEY_PAUSE  ) = paVBProperties[ITEM_PAUSE    ].pKey->_draw_string;

        GGAF_PROPERTY(MY_JOY_SHOT1  ) = paVBProperties[ITEM_MAIN_SHOT].pJoy->_draw_string;
        GGAF_PROPERTY(MY_JOY_SHOT2  ) = paVBProperties[ITEM_SUB_SHOT ].pJoy->_draw_string;
        GGAF_PROPERTY(MY_JOY_TURBO  ) = paVBProperties[ITEM_TURBO    ].pJoy->_draw_string;
        GGAF_PROPERTY(MY_JOY_OPTION ) = paVBProperties[ITEM_CONTROLL ].pJoy->_draw_string;
        GGAF_PROPERTY(MY_JOY_POWERUP) = paVBProperties[ITEM_MAGIC    ].pJoy->_draw_string;
        GGAF_PROPERTY(MY_JOY_VIEW   ) = paVBProperties[ITEM_VAM      ].pJoy->_draw_string;
        GGAF_PROPERTY(MY_JOY_PAUSE  ) = paVBProperties[ITEM_PAUSE    ].pJoy->_draw_string;
        VioletVreath::Properties::save(VV_CONFIG_FILE);

        //�A�v���֔��f
        P_GOD->initVB();

        sinkSubMenu();
        sink();
    } else if (pSubConfirm->wasDecidedCancel()) {
        sinkSubMenu();
    } else {

    }

    int index = getSelectedIndex();
    if ( ITEM_MAIN_SHOT <= index && index <= ITEM_PAUSE ) {
        int DIK_pushed = GgafDxInput::getPushedDownKey();
        if (0x00 <= DIK_pushed && DIK_pushed <= 0xD1) {
            if (VirtualButton::_tagKeymap.UI_UP == DIK_pushed ||
                VirtualButton::_tagKeymap.UI_DOWN == DIK_pushed ||
                VirtualButton::_tagKeymap.UI_LEFT == DIK_pushed ||
                VirtualButton::_tagKeymap.UI_RIGHT == DIK_pushed  )
            {
                //UI�̃��j���[�ړ��͖���
            } else {
                paVBProperties[index].pKey->update(VirtualButton::_mapDik2Str[DIK_pushed].c_str());
                paVBProperties[index].pKey->effectFlush(10);
            }
        }

        int JOY_pushed = GgafDxInput::getPushedDownJoyRgbButton();
        if (0 <= JOY_pushed && JOY_pushed <= 12) {
            paVBProperties[index].pJoy->update(VirtualButton::_mapJoyBtn2Str[JOY_pushed].c_str());
            paVBProperties[index].pJoy->effectFlush(10);
        }
    }

}

void MenuBoardKeyConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        sink();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //�m�F���j���[�N��
    } else {

    }
}
void MenuBoardKeyConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardKeyConfig::~MenuBoardKeyConfig() {
    DELETEARR_IMPOSSIBLE_NULL(paVBProperties);
}
