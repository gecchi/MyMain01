#include "MenuBoardScreenConfig.h"

#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "CursorConfig003.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardScreenConfig::MenuBoardScreenConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardScreenConfig";

    rezo_index_ = 0;
    rezo1_index_= 0;
    rezo2_index_= 0;

    //[0]:�t���X�N���[�����A[1]:�E�B���h�E��
    const char* arrItemStr[ITEM_BANPEI] = {
            "SCREEN MODE(*)",
            "SCREEN NUM(*)",
//            "SCREEN RESOLUTION(*)",
            "SCREEN1 RESOLUTION(*)", "SCREEN2 RESOLUTION(*)",
//            "SWAP SCREEN(*)",
            "GAME VIEW ASPECT TYPE",
//            "GAME VIEW POSITION",
            "GAME VIEW POSITION1", "GAME VIEW POSITION2",

            "OK", "OK & REBOOT", "CANCEL",

            "FULL SCREEN", "WINDOW MODE",
            "DUAL VIEW"  , "SINGLE VIEW",
//            "",
            ""           , "",
//            "NO"         , "YES",
            "FIX"        , "STRETCH",
//            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "1", "2", "3", "4", "5", "6", "7", "8", "9"
    };

    setWidth(PX_C(40*32));
    setHeight(PX_C(12*32));
    //�������b�Z�[�W
    pLabel_msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_msg_->update("(*) NEED REBOOT .\n"
                        "PRESS ^ OR V TO SELECT, AND <- OR -> TO SETTING VALUE.",
                        ALIGN_LEFT, VALIGN_MIDDLE);
    addLabel(pLabel_msg_, PX_C(10), PX_C(500));


    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("[SCREEN CONFIG]", ALIGN_CENTER, VALIGN_MIDDLE);
    addLabel(pLabel_title, PX_C(300), PX_C(40));

    //�ݒ荀�ڃA�C�e��
    for (int i = ITEM_FULL_SCREEN; i <= ITEM_CANCEL; i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(arrItemStr[i], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel);
    }
    relateAllItemToCancel(ITEM_CANCEL); //�L�����Z���A�C�e���ݒ�

    //�ݒ荀�ڂ̐ݒ�l�A�C�e��
    for (int i = VALUE_FULL_SCREEN_TRUE; i < ITEM_BANPEI; i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(arrItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel);
    }


    //�ݒ荀�ڃ��C�����j���[�J�[�\����ݒ�
    CursorConfig003* pCursor = NEW CursorConfig003("MainCursor");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    //�ݒ�l�⏕�J�[�\��
    for (int i = SUBCUR_FULL_SCREEN; i < SUBCUR_BANPEI; i++) {
        CursorConfig003* pSubCur = NEW CursorConfig003("SubCur");
        pSubCur->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        addSubCursor(pSubCur);
    }

    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0�� Yes No �₢���킹���j���[���T�u���j���[�ɒǉ�
    //addSubMenu(NEW MenuBoardResolutionSelect("ResolutionSelect"));
    in_FULL_SCREEN_                = CONFIG::FULL_SCREEN;
    in_NUMBER_OF_SCREENS_USED_                  = CONFIG::NUMBER_OF_SCREENS_USED;
//    in_SWAP_SCREEN_             = CONFIG::SWAP_SCREEN;
    in_SCREEN01_ASPECT_RATIO_FIXED_     = CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01];
    in_SCREEN01_PRESENT_POSITION_   = CONFIG::SCREEN_PRESENT_POSITION[SCREEN01];
    in_SCREEN02_PRESENT_POSITION_   = CONFIG::SCREEN_PRESENT_POSITION[SCREEN02];
//    in_SCREEN01_PRESENT_POSITION_  = CONFIG::SCREEN01_PRESENT_POSITION;
    replaceItem();
}

void MenuBoardScreenConfig::replaceItem() {
    coord x1 = PX_C(100);  //�ݒ荀�ڃA�C�e��X���W
    coord y1 = PX_C(100);  //�ݒ荀�ڃA�C�e��Y���W
    coord lh = PX_C(32);

    //�ݒ荀�ڃA�C�e���z�u
    setPositionItem(ITEM_FULL_SCREEN, x1, y1);  y1 += lh;
    setPositionItem(ITEM_DUAL_SCREEN  , x1, y1);  y1 += lh;
    if (CONFIG::_properties.getBool("FULL_SCREEN")) {
        if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//            getItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION)->activate();
            getItem(ITEM_SCREEN02_FULL_SCREEN_RESOLUTION)->activate();
            setPositionItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION  , x1, y1);  y1 += lh;
            setPositionItem(ITEM_SCREEN02_FULL_SCREEN_RESOLUTION  , x1, y1);  y1 += lh;
        } else {
            getItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION)->activate();
//            getItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(ITEM_SCREEN02_FULL_SCREEN_RESOLUTION)->inactivate();
            setPositionItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION , x1, y1);  y1 += lh;
        }
    } else {
//        getItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(ITEM_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(ITEM_SCREEN02_FULL_SCREEN_RESOLUTION)->inactivate();
    }
//    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//        getItem(ITEM_SWAP_SCREEN)->activate();
//        setPositionItem(ITEM_SWAP_SCREEN, x1, y1);  y1 += lh;
//    } else {
//        getItem(ITEM_SWAP_SCREEN)->inactivate();
//    }
    setPositionItem(ITEM_SCREEN01_ASPECT_RATIO_FIXED, x1, y1);  y1 += lh;
    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//        getItem(ITEM_SCREEN01_PRESENT_POSITION)->inactivate();
        getItem(ITEM_SCREEN01_PRESENT_POSITION)->activate();
        getItem(ITEM_SCREEN02_PRESENT_POSITION)->activate();
        setPositionItem(ITEM_SCREEN01_PRESENT_POSITION, x1, y1);  y1 += lh;
        setPositionItem(ITEM_SCREEN02_PRESENT_POSITION, x1, y1);  y1 += lh;
    } else {
        getItem(ITEM_SCREEN01_PRESENT_POSITION)->activate();
//        getItem(ITEM_SCREEN01_PRESENT_POSITION)->inactivate();
        getItem(ITEM_SCREEN02_PRESENT_POSITION)->inactivate();
        setPositionItem(ITEM_SCREEN01_PRESENT_POSITION, x1, y1);  y1 += lh;
    }
    setPositionItem(ITEM_OK        , PX_C(50) , PX_C(320));
    setPositionItem(ITEM_OK_REBOOT , PX_C(250), PX_C(320));
    setPositionItem(ITEM_CANCEL    , PX_C(450), PX_C(320));

    //�ݒ荀�ڂ̑I��l�A�C�e���z�u
    coord x2 = PX_C(700);  //�I��l�A�C�e��X���W
    coord y2 = PX_C(100);  //�I��l�A�C�e��Y���W
    setPositionItem(VALUE_FULL_SCREEN_TRUE, x2, y2);  setPositionItem(VALUE_FULL_SCREEN_FALSE, x2+PX_C(200), y2);  y2 += lh;
    setPositionItem(VALUE_DUAL_SCREEN_TRUE  , x2, y2);  setPositionItem(VALUE_DUAL_SCREEN_FALSE  , x2+PX_C(200), y2);  y2 += lh;

    if (CONFIG::_properties.getBool("FULL_SCREEN")) {
        if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//            getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION)->activate();
            getItem(VALUE_SCREEN02_FULL_SCREEN_RESOLUTION)->activate();
            setPositionItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION , x2, y2);  y2 += lh;
            setPositionItem(VALUE_SCREEN02_FULL_SCREEN_RESOLUTION , x2, y2);  y2 += lh;
        } else {
            getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION)->activate();
//            getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(VALUE_SCREEN02_FULL_SCREEN_RESOLUTION)->inactivate();
            setPositionItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION, x2, y2);  y2 += lh;
        }
    } else {
        getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(VALUE_SCREEN02_FULL_SCREEN_RESOLUTION)->inactivate();
    }

//    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//        getItem(VALUE_SWAP_SCREEN_FALSE)->activate();  getItem(VALUE_SWAP_SCREEN_TRUE)->activate();
//        setPositionItem(VALUE_SWAP_SCREEN_FALSE, x2, y2);   setPositionItem(VALUE_SWAP_SCREEN_TRUE, x2+PX_C(200), y2);  y2 += lh;
//    } else {
//        getItem(VALUE_SWAP_SCREEN_FALSE)->inactivate();    getItem(VALUE_SWAP_SCREEN_TRUE)->inactivate();
//    }
    setPositionItem(VALUE_FIXED_SCREEN_TRUE  , x2, y2);  setPositionItem(VALUE_FIXED_SCREEN_FALSE, x2+PX_C(200), y2);  y2 += lh;

    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//        for (int i = 0; i < 9; i++) {
//            getItem(VALUE_POS_1 + i)->inactivate();
//        }
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS1_1 + i)->activate();
            setPositionItem(VALUE_POS1_1 + i, x2+PX_C(i*20), y2);
        }   y2 += lh;
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS2_1 + i)->activate();
            setPositionItem(VALUE_POS2_1 + i , x2+PX_C(i*20), y2);
        }   y2 += lh;
    } else {
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS1_1 + i)->inactivate();
        }
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS2_1 + i)->inactivate();
        }
//        for (int i = 0; i < 9; i++) {
//            getItem(VALUE_POS_1 + i)->activate();
//            setPositionItem(VALUE_POS_1 + i , x2+PX_C(i*20), y2);
//        }   y2 += lh;
    }

    //�ݒ荀�ڂ̑I���T�u�J�[�\���z�u
    if (CONFIG::_properties.getBool("FULL_SCREEN")) {
        selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_TRUE, false);
    } else {
        selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_FALSE, false);
    }

    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
        selectItemBySubCursor(SUBCUR_DUAL_SCREEN, VALUE_DUAL_SCREEN_TRUE, false);
    } else {
        selectItemBySubCursor(SUBCUR_DUAL_SCREEN, VALUE_DUAL_SCREEN_FALSE, false);
    }

    if (CONFIG::_properties.getBool("FULL_SCREEN")) {
        if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//            getSubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
            getSubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION)->activate();
            getSubCursor(SUBCUR_SCREEN02_FULL_SCREEN_RESOLUTION)->activate();
            selectItemBySubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION, VALUE_SCREEN01_FULL_SCREEN_RESOLUTION, false);
            selectItemBySubCursor(SUBCUR_SCREEN02_FULL_SCREEN_RESOLUTION, VALUE_SCREEN02_FULL_SCREEN_RESOLUTION, false);
        } else {
            getSubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION)->activate();
//            getSubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
            getSubCursor(SUBCUR_SCREEN02_FULL_SCREEN_RESOLUTION)->inactivate();
            selectItemBySubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION, VALUE_SCREEN01_FULL_SCREEN_RESOLUTION, false);
        }
    } else {
//        getSubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
        getSubCursor(SUBCUR_SCREEN01_FULL_SCREEN_RESOLUTION)->inactivate();
        getSubCursor(SUBCUR_SCREEN02_FULL_SCREEN_RESOLUTION)->inactivate();
    }

//    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//        getSubCursor(SUBCUR_SWAP_SCREEN)->activate();
//        if (CONFIG::_properties.getBool("SWAP_SCREEN")) {
//            selectItemBySubCursor(SUBCUR_SWAP_SCREEN, VALUE_SWAP_SCREEN_TRUE, false);
//        } else {
//            selectItemBySubCursor(SUBCUR_SWAP_SCREEN, VALUE_SWAP_SCREEN_FALSE, false);
//        }
//    } else {
//        getSubCursor(SUBCUR_SWAP_SCREEN)->inactivate();
//    }
    if (CONFIG::_properties.getBool("SCREEN01_ASPECT_RATIO_FIXED")) {
        selectItemBySubCursor(SUBCUR_SCREEN01_ASPECT_RATIO_FIXED, VALUE_FIXED_SCREEN_TRUE, false);
    } else {
        selectItemBySubCursor(SUBCUR_SCREEN01_ASPECT_RATIO_FIXED, VALUE_FIXED_SCREEN_FALSE, false);
    }
    if (CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
//        getSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION)->inactivate();
        getSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION)->activate();
        getSubCursor(SUBCUR_SCREEN02_PRESENT_POSITION)->activate();
        int pos1 = CONFIG::_properties.getInt("SCREEN01_PRESENT_POSITION");
        selectItemBySubCursor(SUBCUR_SCREEN01_PRESENT_POSITION, VALUE_POS1_1+(pos1-1), false);
        int pos2 = CONFIG::_properties.getInt("SCREEN02_PRESENT_POSITION");
        selectItemBySubCursor(SUBCUR_SCREEN02_PRESENT_POSITION, VALUE_POS2_1+(pos2-1), false);
    } else {
        getSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION)->activate();
//        getSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION)->inactivate();
        getSubCursor(SUBCUR_SCREEN02_PRESENT_POSITION)->inactivate();
//        int pos = CONFIG::_properties.getInt("SCREEN01_PRESENT_POSITION");
//        selectItemBySubCursor(SUBCUR_SCREEN01_PRESENT_POSITION, VALUE_POS_1+(pos-1), false);
    }

//    FontBoardActor* pLabelRezo  = (FontBoardActor*) getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION);
//    std::string rezo = XTOS(CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_WIDTH")) + "X" + XTOS(CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_HEIGHT"));
//    pLabelRezo->update(rezo.c_str());

    FontBoardActor* pLabelRezo1 = (FontBoardActor*) getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION);
    std::string rezo1 = XTOS(CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_WIDTH")) + "X" + XTOS(CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_HEIGHT"));
    pLabelRezo1->update(rezo1.c_str());

    FontBoardActor* pLabelRezo2 = (FontBoardActor*) getItem(VALUE_SCREEN02_FULL_SCREEN_RESOLUTION);
    std::string rezo2 = XTOS(CONFIG::_properties.getInt("SCREEN02_FULL_SCREEN_WIDTH")) + "X" + XTOS(CONFIG::_properties.getInt("SCREEN02_FULL_SCREEN_HEIGHT"));
    pLabelRezo2->update(rezo2.c_str());
}

bool MenuBoardScreenConfig::condSelectNext() {
    if (getSelectedIndex() == ITEM_CANCEL) { //CANCEL�����֐i�߂Ȃ�����
        return false;
    } else {
        return VVB->isAutoRepeat(0, VV_VB_UI_DOWN);
    }
}

bool MenuBoardScreenConfig::condSelectPrev() {
    if (getSelectedIndex() == 0) { //�擪�A�C�e��
        return false;
    } else {
        return VVB->isAutoRepeat(0, VV_VB_UI_UP);
    }
}

bool MenuBoardScreenConfig::condSelectExNext() {
    return false;
}

bool MenuBoardScreenConfig::condSelectExPrev() {
    return false;
}

void MenuBoardScreenConfig::onRise() {
    in_FULL_SCREEN_                = CONFIG::FULL_SCREEN;
    in_NUMBER_OF_SCREENS_USED_    = CONFIG::NUMBER_OF_SCREENS_USED;
//    in_SWAP_SCREEN_             = CONFIG::SWAP_SCREEN;
    in_SCREEN01_ASPECT_RATIO_FIXED_     = CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01];
    in_SCREEN01_PRESENT_POSITION_   = CONFIG::SCREEN_PRESENT_POSITION[SCREEN01];
    in_SCREEN02_PRESENT_POSITION_   = CONFIG::SCREEN_PRESENT_POSITION[SCREEN02];
//    in_SCREEN01_PRESENT_POSITION_  = CONFIG::SCREEN01_PRESENT_POSITION;
    int num_adapter = pCARETAKER->_num_adapter;
    GgafDx::Caretaker::AdapterRezos* paAdapterRezos = pCARETAKER->_paAdapterRezos;
    if (num_adapter >= 1) {
        rezo_num_ = paAdapterRezos[0].rezo_num;
        GgafDx::Caretaker::RezoInfo* paRezos = paAdapterRezos[0].paRezoInfo;
        rezo_index_ = pCARETAKER->checkAppropriateDisplaySize(
                            paRezos, rezo_num_,
                            (UINT)CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_WIDTH"),
                            (UINT)CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_HEIGHT")
                      );
        rezo1_num_ = rezo_num_;
        rezo1_index_ = pCARETAKER->checkAppropriateDisplaySize(
                            paRezos, rezo1_num_,
                            (UINT)CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_WIDTH"),
                            (UINT)CONFIG::_properties.getInt("SCREEN01_FULL_SCREEN_HEIGHT")
                       );
    }
    if (num_adapter >= 2) {
        rezo2_num_ = paAdapterRezos[1].rezo_num;
        GgafDx::Caretaker::RezoInfo* paRezos = paAdapterRezos[1].paRezoInfo;
        rezo2_index_ = pCARETAKER->checkAppropriateDisplaySize(
                            paRezos, rezo2_num_,
                            (UINT)CONFIG::_properties.getInt("SCREEN02_FULL_SCREEN_WIDTH"),
                            (UINT)CONFIG::_properties.getInt("SCREEN02_FULL_SCREEN_HEIGHT")
                       );
    }
    selectItem(ITEM_FULL_SCREEN); //�����I���A�C�e����ݒ�

    replaceItem();
    MenuBoard::onRise();
}

void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    World* pWorld = pCARETAKER->getSpacetime()->getWorld();
    //�L�[���́A�{�^�����́A���f
    VirtualButton* pVVB = VVB;
    int selected_index = getSelectedIndex();

    //OK���̊m�F���j���[����
    if (selected_index == ITEM_OK || selected_index == ITEM_OK_REBOOT) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu();
        if (pSubConfirm->hasJustDecidedOk()) { //SAVE�m�FOK!
            //���v���p�e�B�֏�������
            if (getSelectedIndexOnSubCursor(SUBCUR_FULL_SCREEN) == ITEM_FULL_SCREEN) {
                CONFIG::_properties.setValue("FULL_SCREEN", true);
            } else {
                CONFIG::_properties.setValue("FULL_SCREEN", false);
            }
            if (CONFIG::FULL_SCREEN != CONFIG::_properties.getBool("FULL_SCREEN")) {
                pWorld->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSubCursor(SUBCUR_DUAL_SCREEN) == ITEM_DUAL_SCREEN) {
                CONFIG::_properties.setValue("NUMBER_OF_SCREENS_USED", 2);
            } else {
                CONFIG::_properties.setValue("NUMBER_OF_SCREENS_USED", 1);
            }
            if (CONFIG::NUMBER_OF_SCREENS_USED  != CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED")) {
                pWorld->need_reboot_ = 1;
            }

//            if (CONFIG::NUMBER_OF_SCREENS_USED > 1) {
//                if (getSelectedIndexOnSubCursor(SUBCUR_DUAL_SCREEN) == ITEM_DUAL_SCREEN) {
//                    CONFIG::_properties.setValue("SWAP_SCREEN", false);
//                } else {
//                    CONFIG::_properties.setValue("SWAP_SCREEN", true);
//                }
//            }
//            if (CONFIG::SWAP_SCREEN != CONFIG::_properties.getBool("SWAP_SCREEN")) {
//                pWorld->need_reboot_ = 1;
//            }

            if (getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_ASPECT_RATIO_FIXED) == ITEM_SCREEN01_ASPECT_RATIO_FIXED) {
                CONFIG::_properties.setValue("SCREEN01_ASPECT_RATIO_FIXED", true);
            } else {
                CONFIG::_properties.setValue("SCREEN01_ASPECT_RATIO_FIXED", false);
            }
            //_TRACE_("CONFIG::FULL_SCREEN="<<CONFIG::FULL_SCREEN<<" CONFIG::SCREEN01_ASPECT_RATIO_FIXED="<<CONFIG::SCREEN01_ASPECT_RATIO_FIXED<<" CONFIG::_properties.getBool(\"SCREEN01_ASPECT_RATIO_FIXED\")="<<CONFIG::_properties.getBool("SCREEN01_ASPECT_RATIO_FIXED"));
            if (CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01] != CONFIG::_properties.getBool("SCREEN01_ASPECT_RATIO_FIXED")) {
                pWorld->need_reboot_ = 1;
            }

//            int pos = getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION)+1 - VALUE_POS_1;
//            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", pos);
//            if (CONFIG::SCREEN01_PRESENT_POSITION != CONFIG::_properties.getInt("SCREEN01_PRESENT_POSITION")) {
//                pWorld->need_reboot_ = 1;
//            }

            int pos1 = getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION)+1 - VALUE_POS1_1;
            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", pos1);
            int pos2 = getSelectedIndexOnSubCursor(SUBCUR_SCREEN02_PRESENT_POSITION)+1 - VALUE_POS2_1;
            CONFIG::_properties.setValue("SCREEN02_PRESENT_POSITION", pos2);
            if (CONFIG::SCREEN_PRESENT_POSITION[SCREEN01] != CONFIG::_properties.getInt("SCREEN01_PRESENT_POSITION")) {
                pWorld->need_reboot_ = 1;
            }
            if (CONFIG::SCREEN_PRESENT_POSITION[SCREEN02] != CONFIG::_properties.getInt("SCREEN02_PRESENT_POSITION")) {
                pWorld->need_reboot_ = 1;
            }

            //FULL_SCREEN�ADUAL_SCREEN�́A�A�v�����s���ɕύX�ł��Ȃ��B ���ݒl��ێ�
            bool tmp_FULL_SCREEN = CONFIG::FULL_SCREEN;
            bool tmp_NUMBER_OF_SCREENS_USED = CONFIG::NUMBER_OF_SCREENS_USED;//TODO�F�Ƃ肠�����R���p�C����ʂ����߂ɕύX�����ł�
//            bool tmp_SWAP_SCREEN = CONFIG::SWAP_SCREEN;
            CONFIG::_properties.write(CONFIG::_load_properties_filename); //�v���p�e�B�ۑ�
            CONFIG::loadProperties(CONFIG::_load_properties_filename); //�v���p�e�B�Ĕ��f
            //�v�ċN���v���p�e�B�́A���Q�[���ɎQ�Ƃ���Ă͍���ɂŁA�����ɖ߂��BMap�ɏ�������ł�̂ōċN����ɔ��f�����
            CONFIG::FULL_SCREEN = tmp_FULL_SCREEN;
            CONFIG::NUMBER_OF_SCREENS_USED = tmp_NUMBER_OF_SCREENS_USED;
//            CONFIG::SWAP_SCREEN = tmp_SWAP_SCREEN;

            //���s���A�v���֑������f�ł�����͔̂��f
            pCARETAKER->chengeViewAspect1(CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01]);
            if (CONFIG::NUMBER_OF_SCREENS_USED > 1) {
                pCARETAKER->chengePrimaryScreenPresentPos(CONFIG::SCREEN_PRESENT_POSITION[SCREEN01]);
                pCARETAKER->chengeSecondaryScreenPresentPos(CONFIG::SCREEN_PRESENT_POSITION[SCREEN02]);
            } else {
                pCARETAKER->chengePrimaryScreenPresentPos(CONFIG::SCREEN_PRESENT_POSITION[SCREEN01]);
            }

            if (selected_index == ITEM_OK_REBOOT) { //����Ƀ��u�[�g
                Caretaker::reboot(); //�ċN���I
            } else {
                sinkCurrentSubMenu();
                sinkMe();
            }
        } else if (pSubConfirm->hasJustDecidedCancel()) { //�m�F�ŃL�����Z��
            sinkCurrentSubMenu();
        } else {

        }
    }
    //�e�ݒ荀�ڂ́������̏���
    if (selected_index == ITEM_FULL_SCREEN) {
        if (pVVB->isPushedDown(0, VV_VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_TRUE);
            CONFIG::_properties.setValue("FULL_SCREEN", true);
            replaceItem();
        } else if (pVVB->isPushedDown(0, VV_VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_FALSE);
            CONFIG::_properties.setValue("FULL_SCREEN", false);
            replaceItem();
        }
    } else if (selected_index == ITEM_DUAL_SCREEN) {
        if (pVVB->isPushedDown(0, VV_VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_DUAL_SCREEN, VALUE_DUAL_SCREEN_TRUE);
            CONFIG::_properties.setValue("NUMBER_OF_SCREENS_USED", 2);
            replaceItem();
        } else if (pVVB->isPushedDown(0, VV_VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_DUAL_SCREEN, VALUE_DUAL_SCREEN_FALSE);
            CONFIG::_properties.setValue("NUMBER_OF_SCREENS_USED", 1);
            replaceItem();
        }
//    } else if (selected_index == ITEM_SWAP_SCREEN) {
//        if (pVVB->isPushedDown(0, VV_VB_UI_LEFT)) {
//            selectItemBySubCursor(SUBCUR_SWAP_SCREEN, VALUE_SWAP_SCREEN_FALSE);
//            CONFIG::_properties.setValue("SWAP_SCREEN", false);
//        } else if (pVVB->isPushedDown(0, VV_VB_UI_RIGHT)) {
//            selectItemBySubCursor(SUBCUR_SWAP_SCREEN, VALUE_SWAP_SCREEN_TRUE);
//            CONFIG::_properties.setValue("SWAP_SCREEN", true);
//        }
    } else if (selected_index == ITEM_SCREEN01_ASPECT_RATIO_FIXED) {
        if (pVVB->isPushedDown(0, VV_VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_SCREEN01_ASPECT_RATIO_FIXED, VALUE_FIXED_SCREEN_TRUE);
            CONFIG::_properties.setValue("SCREEN01_ASPECT_RATIO_FIXED", true);
            if (!pWorld->need_reboot_) {
                pCARETAKER->chengeViewAspect1(true);
            }
        } else if (pVVB->isPushedDown(0, VV_VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_SCREEN01_ASPECT_RATIO_FIXED, VALUE_FIXED_SCREEN_FALSE);
            CONFIG::_properties.setValue("SCREEN01_ASPECT_RATIO_FIXED", false);
            if (!pWorld->need_reboot_) {
                pCARETAKER->chengeViewAspect1(false);
            }
        }
//    } else if (selected_index == ITEM_SCREEN01_PRESENT_POSITION) {
//        if (pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT)) {
//            int i = getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION);
//            if (i == VALUE_POS_9) {
//                i = VALUE_POS_1;
//            } else {
//                i++;
//            }
//            selectItemBySubCursor(SUBCUR_SCREEN01_PRESENT_POSITION, i);
//            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", i+1 - VALUE_POS_1);
//            if (!pWorld->need_reboot_) {
//                pCARETAKER->chengePrimaryScreenPresentPos(i+1 - VALUE_POS_1);
//            }
//        } else if (pVVB->isAutoRepeat(0, VV_VB_UI_LEFT)) {
//            int i = getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION);
//            if (i == VALUE_POS_1) {
//                i = VALUE_POS_9;
//            } else {
//                i--;
//            }
//            selectItemBySubCursor(SUBCUR_SCREEN01_PRESENT_POSITION, i);
//            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", i+1 - VALUE_POS_1);
//            if (!pCARETAKER->getSpacetime()->getWorld()->need_reboot_) {
//                pCARETAKER->chengePrimaryScreenPresentPos(i+1 - VALUE_POS_1);
//            }
//        }
    } else if (selected_index == ITEM_SCREEN01_PRESENT_POSITION) {
        if (pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION);
            if (i == VALUE_POS1_9) {
                i = VALUE_POS1_1;
            } else {
                i++;
            }
            selectItemBySubCursor(SUBCUR_SCREEN01_PRESENT_POSITION, i);
            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", i+1 - VALUE_POS1_1);
            pCARETAKER->chengePrimaryScreenPresentPos(i+1 - VALUE_POS1_1);
        } else if (pVVB->isAutoRepeat(0, VV_VB_UI_LEFT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_SCREEN01_PRESENT_POSITION);
            if (i == VALUE_POS1_1) {
                i = VALUE_POS1_9;
            } else {
                i--;
            }
            selectItemBySubCursor(SUBCUR_SCREEN01_PRESENT_POSITION, i);
            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", i+1 - VALUE_POS1_1);
            pCARETAKER->chengePrimaryScreenPresentPos(i+1 - VALUE_POS1_1);
        }
    } else if (selected_index == ITEM_SCREEN02_PRESENT_POSITION) {
        if (pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_SCREEN02_PRESENT_POSITION);
            if (i == VALUE_POS2_9) {
                i = VALUE_POS2_1;
            } else {
                i++;
            }
            selectItemBySubCursor(SUBCUR_SCREEN02_PRESENT_POSITION, i);
            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", i+1 - VALUE_POS2_1);
            pCARETAKER->chengeSecondaryScreenPresentPos(i+1 - VALUE_POS2_1);
        } else if (pVVB->isAutoRepeat(0, VV_VB_UI_LEFT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_SCREEN02_PRESENT_POSITION);
            if (i == VALUE_POS2_1) {
                i = VALUE_POS2_9;
            } else {
                i--;
            }
            selectItemBySubCursor(SUBCUR_SCREEN02_PRESENT_POSITION, i);
            CONFIG::_properties.setValue("SCREEN01_PRESENT_POSITION", i+1 - VALUE_POS2_1);
            pCARETAKER->chengeSecondaryScreenPresentPos(i+1 - VALUE_POS2_1);
        }
//    } else if (selected_index == ITEM_SCREEN01_FULL_SCREEN_RESOLUTION) {
//        bool is_right = pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT);
//        bool is_left = pVVB->isAutoRepeat(0, VV_VB_UI_LEFT);
//        if (is_right || is_left) {
//            if (is_right) {
//                if (rezo_index_ >= rezo_num_-1) {
//                    rezo_index_ = 0;
//                } else {
//                    rezo_index_++;
//                }
//            } else if (is_left) {
//                if (rezo_index_ <= 0) {
//                    rezo_index_ = rezo_num_-1;
//                } else {
//                    rezo_index_--;
//                }
//            }
//            if (rezo_num_ > 0) {
//                GgafDx::Caretaker::AdapterRezos* paAdapterRezos = pCARETAKER->_paAdapterRezos;
//                FontBoardActor* pLabelRezo  = (FontBoardActor*) getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION);
//                pLabelRezo->update(paAdapterRezos[0].paRezoInfo[rezo_index_].item_str.c_str());
//                CONFIG::_properties.setValue("SCREEN01_FULL_SCREEN_WIDTH" , paAdapterRezos[0].paRezoInfo[rezo_index_].width);
//                CONFIG::_properties.setValue("SCREEN01_FULL_SCREEN_HEIGHT", paAdapterRezos[0].paRezoInfo[rezo_index_].height);
//            }
//        }
    } else if (selected_index == ITEM_SCREEN01_FULL_SCREEN_RESOLUTION) {
        bool is_right = pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT);
        bool is_left = pVVB->isAutoRepeat(0, VV_VB_UI_LEFT);
        if (is_right || is_left) {
            if (is_right) {
                if (rezo1_index_ >= rezo1_num_-1) {
                    rezo1_index_ = 0;
                } else {
                    rezo1_index_++;
                }
            } else if (is_left) {
                if (rezo1_index_ <= 0) {
                    rezo1_index_ = rezo1_num_-1;
                } else {
                    rezo1_index_--;
                }
            }
            if (rezo1_num_ > 0) {
                GgafDx::Caretaker::AdapterRezos* paAdapterRezos = pCARETAKER->_paAdapterRezos;
                FontBoardActor* pLabelRezo1  = (FontBoardActor*) getItem(VALUE_SCREEN01_FULL_SCREEN_RESOLUTION);
                pLabelRezo1->update(paAdapterRezos[0].paRezoInfo[rezo1_index_].item_str.c_str());
                CONFIG::_properties.setValue("SCREEN01_FULL_SCREEN_WIDTH" , paAdapterRezos[0].paRezoInfo[rezo1_index_].width);
                CONFIG::_properties.setValue("SCREEN01_FULL_SCREEN_HEIGHT", paAdapterRezos[0].paRezoInfo[rezo1_index_].height);
            }
        }
    } else if (selected_index == ITEM_SCREEN02_FULL_SCREEN_RESOLUTION) {
        bool is_right = pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT);
        bool is_left = pVVB->isAutoRepeat(0, VV_VB_UI_LEFT);
        if (rezo2_num_ > 0) {
            if (is_right || is_left) {
                if (is_right) {
                    if (rezo2_index_ >= rezo2_num_-1) {
                        rezo2_index_ = 0;
                    } else {
                        rezo2_index_++;
                    }
                } else if (is_left) {
                    if (rezo2_index_ <= 0) {
                        rezo2_index_ = rezo2_num_-1;
                    } else {
                        rezo2_index_--;
                    }
                }
                GgafDx::Caretaker::AdapterRezos* paAdapterRezos = pCARETAKER->_paAdapterRezos;
                FontBoardActor* pLabelRezo2 = (FontBoardActor*) getItem(VALUE_SCREEN02_FULL_SCREEN_RESOLUTION);
                pLabelRezo2->update(paAdapterRezos[1].paRezoInfo[rezo2_index_].item_str.c_str());
                CONFIG::_properties.setValue("SCREEN02_FULL_SCREEN_WIDTH" , paAdapterRezos[1].paRezoInfo[rezo2_index_].width);
                CONFIG::_properties.setValue("SCREEN02_FULL_SCREEN_HEIGHT", paAdapterRezos[1].paRezoInfo[rezo2_index_].height);
            }
        } else {
            //1��ʂȂ̂ŁA�ݒ�o���Ȃ��B
            if (is_right || is_left) {
                getSeTransmitter()->play(SE_WRONG);
            }
        }
    }
}

void MenuBoardScreenConfig::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_CANCEL) {
        CONFIG::FULL_SCREEN               = in_FULL_SCREEN_              ;
        CONFIG::NUMBER_OF_SCREENS_USED                 = in_NUMBER_OF_SCREENS_USED_                ;
//        CONFIG::SWAP_SCREEN            = in_SWAP_SCREEN_           ;
        CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01]    = in_SCREEN01_ASPECT_RATIO_FIXED_   ;
        CONFIG::SCREEN_PRESENT_POSITION[SCREEN01]  = in_SCREEN01_PRESENT_POSITION_ ;
        CONFIG::SCREEN_PRESENT_POSITION[SCREEN02]  = in_SCREEN02_PRESENT_POSITION_ ;
        CONFIG::SCREEN_PRESENT_POSITION[SCREEN01] = in_SCREEN01_PRESENT_POSITION_;
        pCARETAKER->chengeViewAspect1(CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01]);
        if (CONFIG::NUMBER_OF_SCREENS_USED > 1) {
            pCARETAKER->chengePrimaryScreenPresentPos(CONFIG::SCREEN_PRESENT_POSITION[SCREEN01]);
            pCARETAKER->chengeSecondaryScreenPresentPos(CONFIG::SCREEN_PRESENT_POSITION[SCREEN02]);
        } else {
            pCARETAKER->chengePrimaryScreenPresentPos(CONFIG::SCREEN_PRESENT_POSITION[SCREEN01]);
        }
        sinkMe();
    } else if (prm_item_index == ITEM_OK) { //�ۑ���OK
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE�m�F���j���[�N��
    } else if (prm_item_index == ITEM_OK_REBOOT) { //OK�ōċN��
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE�m�F���j���[�N��
    } else {

    }
}

void MenuBoardScreenConfig::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
