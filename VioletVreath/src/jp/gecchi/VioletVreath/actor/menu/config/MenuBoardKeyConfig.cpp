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
    _Z = 8; //�v���C�I���e�B

    //���j���[�A�C�e���i�I���j�ݒ�
    char* apItemStr[] = {
          "MAIN SHOT BUTTON & KEY",
          "SUB SHOT  BUTTON & KEY",
          "TURBO     BUTTON & KEY",
          "CONTROLL  BUTTON & KEY",
          "MAGIC     BUTTON & KEY",
          "VAM       BUTTON & KEY",
          "PAUSE     BUTTON & KEY",
          "UP                 KEY",
          "DOWN               KEY",
          "LEFT               KEY",
          "RIGHT              KEY",
//          "SAVE AND EXIT", //6
//          "CANCEL"         //7
    };

    int item_index;
    for (item_index = ITEM_MAIN_SHOT; item_index <= ITEM_KEY_LIGHT; item_index++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[item_index]);
        addItem(pLabel, PX_C(200), PX_C(100+(item_index*20)), -1);
    }

    LabelGecchi16Font* pLabel_OK = NEW LabelGecchi16Font("item");
    pLabel_OK->update("OK", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350), -1);
    ITEM_INDEX_OK_ = item_index;

    LabelGecchi16Font* pLabel_CANCEL = NEW LabelGecchi16Font("item");
    pLabel_CANCEL->update("CANCEL", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350), -1);
    ITEM_INDEX_CANCEL_ = item_index + 1;

    paVBProperties = NEW VBProperty[item_index+1];
    paVBProperties[ITEM_MAIN_SHOT].key = GGAF_PROPERTY(MY_KEY_SHOT1  );
    paVBProperties[ITEM_SUB_SHOT ].key = GGAF_PROPERTY(MY_KEY_SHOT2  );
    paVBProperties[ITEM_TURBO    ].key = GGAF_PROPERTY(MY_KEY_OPTION );
    paVBProperties[ITEM_CONTROLL ].key = GGAF_PROPERTY(MY_KEY_VIEW   );
    paVBProperties[ITEM_MAGIC    ].key = GGAF_PROPERTY(MY_KEY_TURBO  );
    paVBProperties[ITEM_VAM      ].key = GGAF_PROPERTY(MY_KEY_POWERUP);
    paVBProperties[ITEM_PAUSE    ].key = GGAF_PROPERTY(MY_KEY_PAUSE  );
    paVBProperties[ITEM_KEY_UP   ].key = GGAF_PROPERTY(MY_KEY_UP     );
    paVBProperties[ITEM_KEY_DOWN ].key = GGAF_PROPERTY(MY_KEY_DOWN   );
    paVBProperties[ITEM_KEY_LEFT ].key = GGAF_PROPERTY(MY_KEY_LEFT   );
    paVBProperties[ITEM_KEY_LIGHT].key = GGAF_PROPERTY(MY_KEY_RIGHT  );

    paVBProperties[ITEM_MAIN_SHOT].joy = GGAF_PROPERTY(MY_JOY_SHOT1  );
    paVBProperties[ITEM_SUB_SHOT ].joy = GGAF_PROPERTY(MY_JOY_SHOT2  );
    paVBProperties[ITEM_TURBO    ].joy = GGAF_PROPERTY(MY_JOY_OPTION );
    paVBProperties[ITEM_CONTROLL ].joy = GGAF_PROPERTY(MY_JOY_VIEW   );
    paVBProperties[ITEM_MAGIC    ].joy = GGAF_PROPERTY(MY_JOY_TURBO  );
    paVBProperties[ITEM_VAM      ].joy = GGAF_PROPERTY(MY_JOY_POWERUP);
    paVBProperties[ITEM_PAUSE    ].joy = GGAF_PROPERTY(MY_JOY_PAUSE);
    paVBProperties[ITEM_KEY_UP   ].joy = "";
    paVBProperties[ITEM_KEY_DOWN ].joy = "";
    paVBProperties[ITEM_KEY_LEFT ].joy = "";
    paVBProperties[ITEM_KEY_LIGHT].joy = "";

    papDispKey_ = NEW LabelGecchi16Font*[item_index+1];
    papDispJoy_ = NEW LabelGecchi16Font*[item_index+1];

    for (int i = ITEM_MAIN_SHOT; i <= ITEM_KEY_LIGHT; i++) {
        papDispKey_[i] = NEW LabelGecchi16Font("item");
        papDispKey_[i]->update(paVBProperties[i].key.c_str());
        addDispLabel(papDispKey_[i], PX_C(600), PX_C(100+(i*20)), -1);

        papDispJoy_[i] = NEW LabelGecchi16Font("item");
        papDispJoy_[i]->update(paVBProperties[i].joy.c_str());
        addDispLabel(papDispJoy_[i], PX_C(800), PX_C(100+(i*20)), -1);
    }


    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("message");
    pMsg->update("SELECT AND PUSH KEY, JOY BUTTON!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispLabel(pMsg, PX_C(100), PX_C(20), -1);



    //���ʂȃ��j���[�J�[�\���I�[�_�[���\�z
    relateAllItemCancel(ITEM_INDEX_CANCEL_);

    //���j���[�J�[�\����ݒ�
    CursorKeyConfigMenu* pCursor = NEW CursorKeyConfigMenu("CursorKeyConfigMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
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
    StringBoardMenu* pSub = getSubMenu(0);
    if (pSub) {
        if (pSub->isJustDecided()) {
            if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {
                //�����ŃZ�[�u�I
                sinkSubMenu();
                sink();
            } else if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSubMenu();
            } else {
            }
        } else {

        }
    }
}

void MenuBoardKeyConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        sink();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //�m�F���j���[�N��
    }
}
void MenuBoardKeyConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardKeyConfig::~MenuBoardKeyConfig() {
    DELETEARR_IMPOSSIBLE_NULL(papDispKey_);
    DELETEARR_IMPOSSIBLE_NULL(papDispJoy_);
    DELETEARR_IMPOSSIBLE_NULL(paVBProperties);
}
