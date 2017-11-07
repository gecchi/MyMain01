#include "MenuBoardScreenConfig.h"

#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "CursorConfig003.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"


using namespace GgafCore;
using namespace GgafDxCore;
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
            "SCREEN RESOLUTION(*)",
            "SCREEN1 RESOLUTION(*)", "SCREEN2 RESOLUTION(*)",
            "SWAP SCREEN(*)",
            "GAME VIEW ASPECT TYPE",
            "GAME VIEW POSITION",
            "GAME VIEW POSITION1", "GAME VIEW POSITION2",

            "OK", "OK & REBOOT", "CANCEL",

            "FULL SCREEN", "WINDOW MODE",
            "DUAL VIEW"  , "SINGLE VIEW",
            "",
            ""           , "",
            "NO"         , "YES",
            "FIX"        , "STRETCH",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
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
    in_FULL_SCREEN_                = PROPERTY::FULL_SCREEN;
    in_DUAL_VIEW_                  = PROPERTY::DUAL_VIEW;
    in_SWAP_GAME_VIEW_             = PROPERTY::SWAP_GAME_VIEW;
    in_FIXED_GAME_VIEW_ASPECT_     = PROPERTY::FIXED_GAME_VIEW_ASPECT;
    in_DUAL_VIEW_DRAW_POSITION1_   = PROPERTY::DUAL_VIEW_DRAW_POSITION1;
    in_DUAL_VIEW_DRAW_POSITION2_   = PROPERTY::DUAL_VIEW_DRAW_POSITION2;
    in_SINGLE_VIEW_DRAW_POSITION_  = PROPERTY::SINGLE_VIEW_DRAW_POSITION;
    replaceItem();
}

void MenuBoardScreenConfig::replaceItem() {
    coord x1 = PX_C(100);  //�ݒ荀�ڃA�C�e��X���W
    coord y1 = PX_C(100);  //�ݒ荀�ڃA�C�e��Y���W
    coord lh = PX_C(32);

    //�ݒ荀�ڃA�C�e���z�u
    setPositionItem(ITEM_FULL_SCREEN, x1, y1);  y1 += lh;
    setPositionItem(ITEM_DUAL_VIEW  , x1, y1);  y1 += lh;
    if (PROPERTY::getBool("FULL_SCREEN")) {
        if (PROPERTY::getBool("DUAL_VIEW")) {
            getItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->activate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->activate();
            setPositionItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION  , x1, y1);  y1 += lh;
            setPositionItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION  , x1, y1);  y1 += lh;
        } else {
            getItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->activate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
            setPositionItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION , x1, y1);  y1 += lh;
        }
    } else {
        getItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
        getItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
    }
    if (PROPERTY::getBool("DUAL_VIEW")) {
        getItem(ITEM_SWAP_GAME_VIEW)->activate();
        setPositionItem(ITEM_SWAP_GAME_VIEW, x1, y1);  y1 += lh;
    } else {
        getItem(ITEM_SWAP_GAME_VIEW)->inactivate();
    }
    setPositionItem(ITEM_FIXED_GAME_VIEW_ASPECT, x1, y1);  y1 += lh;
    if (PROPERTY::getBool("DUAL_VIEW")) {
        getItem(ITEM_SINGLE_VIEW_DRAW_POSITION)->inactivate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION1)->activate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION2)->activate();
        setPositionItem(ITEM_DUAL_VIEW_DRAW_POSITION1, x1, y1);  y1 += lh;
        setPositionItem(ITEM_DUAL_VIEW_DRAW_POSITION2, x1, y1);  y1 += lh;
    } else {
        getItem(ITEM_SINGLE_VIEW_DRAW_POSITION)->activate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION1)->inactivate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION2)->inactivate();
        setPositionItem(ITEM_SINGLE_VIEW_DRAW_POSITION, x1, y1);  y1 += lh;
    }
    setPositionItem(ITEM_OK        , PX_C(50) , PX_C(320));
    setPositionItem(ITEM_OK_REBOOT , PX_C(250), PX_C(320));
    setPositionItem(ITEM_CANCEL    , PX_C(450), PX_C(320));

    //�ݒ荀�ڂ̑I��l�A�C�e���z�u
    coord x2 = PX_C(700);  //�I��l�A�C�e��X���W
    coord y2 = PX_C(100);  //�I��l�A�C�e��Y���W
    setPositionItem(VALUE_FULL_SCREEN_TRUE, x2, y2);  setPositionItem(VALUE_FULL_SCREEN_FALSE, x2+PX_C(200), y2);  y2 += lh;
    setPositionItem(VALUE_DUAL_VIEW_TRUE  , x2, y2);  setPositionItem(VALUE_DUAL_VIEW_FALSE  , x2+PX_C(200), y2);  y2 += lh;

    if (PROPERTY::getBool("FULL_SCREEN")) {
        if (PROPERTY::getBool("DUAL_VIEW")) {
            getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->activate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->activate();
            setPositionItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION , x2, y2);  y2 += lh;
            setPositionItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION , x2, y2);  y2 += lh;
        } else {
            getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->activate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
            setPositionItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION, x2, y2);  y2 += lh;
        }
    } else {
        getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
        getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        getItem(VALUE_SWAP_GAME_VIEW_FALSE)->activate();  getItem(VALUE_SWAP_GAME_VIEW_TRUE)->activate();
        setPositionItem(VALUE_SWAP_GAME_VIEW_FALSE, x2, y2);   setPositionItem(VALUE_SWAP_GAME_VIEW_TRUE, x2+PX_C(200), y2);  y2 += lh;
    } else {
        getItem(VALUE_SWAP_GAME_VIEW_FALSE)->inactivate();    getItem(VALUE_SWAP_GAME_VIEW_TRUE)->inactivate();
    }
    setPositionItem(VALUE_FIXED_GAME_VIEW_TRUE  , x2, y2);  setPositionItem(VALUE_FIXED_GAME_VIEW_FALSE, x2+PX_C(200), y2);  y2 += lh;

    if (PROPERTY::getBool("DUAL_VIEW")) {
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS_1 + i)->inactivate();
        }
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
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS_1 + i)->activate();
            setPositionItem(VALUE_POS_1 + i , x2+PX_C(i*20), y2);
        }   y2 += lh;
    }

    //�ݒ荀�ڂ̑I���T�u�J�[�\���z�u
    if (PROPERTY::getBool("FULL_SCREEN")) {
        selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_TRUE, false);
    } else {
        selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_FALSE, false);
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        selectItemBySubCursor(SUBCUR_DUAL_VIEW, VALUE_DUAL_VIEW_TRUE, false);
    } else {
        selectItemBySubCursor(SUBCUR_DUAL_VIEW, VALUE_DUAL_VIEW_FALSE, false);
    }

    if (PROPERTY::getBool("FULL_SCREEN")) {
        if (PROPERTY::getBool("DUAL_VIEW")) {
            getSubCursor(SUBCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
            getSubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->activate();
            getSubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->activate();
            selectItemBySubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION, VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION, false);
            selectItemBySubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION, VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION, false);
        } else {
            getSubCursor(SUBCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->activate();
            getSubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
            getSubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
            selectItemBySubCursor(SUBCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION, VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION, false);
        }
    } else {
        getSubCursor(SUBCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
        getSubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
        getSubCursor(SUBCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        getSubCursor(SUBCUR_SWAP_GAME_VIEW)->activate();
        if (PROPERTY::getBool("SWAP_GAME_VIEW")) {
            selectItemBySubCursor(SUBCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_TRUE, false);
        } else {
            selectItemBySubCursor(SUBCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_FALSE, false);
        }
    } else {
        getSubCursor(SUBCUR_SWAP_GAME_VIEW)->inactivate();
    }
    if (PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT")) {
        selectItemBySubCursor(SUBCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_TRUE, false);
    } else {
        selectItemBySubCursor(SUBCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_FALSE, false);
    }
    if (PROPERTY::getBool("DUAL_VIEW")) {
        getSubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION)->inactivate();
        getSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1)->activate();
        getSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2)->activate();
        int pos1 = PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION1");
        selectItemBySubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1, VALUE_POS1_1+(pos1-1), false);
        int pos2 = PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION2");
        selectItemBySubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2, VALUE_POS2_1+(pos2-1), false);
    } else {
        getSubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION)->activate();
        getSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1)->inactivate();
        getSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2)->inactivate();
        int pos = PROPERTY::getInt("SINGLE_VIEW_DRAW_POSITION");
        selectItemBySubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION, VALUE_POS_1+(pos-1), false);
    }

    FontBoardActor* pLabelRezo  = (FontBoardActor*) getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION);
    std::string rezo = XTOS(PROPERTY::getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH")) + "X" + XTOS(PROPERTY::getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT"));
    pLabelRezo->update(rezo.c_str());

    FontBoardActor* pLabelRezo1 = (FontBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION);
    std::string rezo1 = XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH")) + "X" + XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT"));
    pLabelRezo1->update(rezo1.c_str());

    FontBoardActor* pLabelRezo2 = (FontBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION);
    std::string rezo2 = XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH")) + "X" + XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT"));
    pLabelRezo2->update(rezo2.c_str());
}

bool MenuBoardScreenConfig::condSelectNext() {
    if (getSelectedIndex() == ITEM_CANCEL) { //CANCEL�����֐i�߂Ȃ�����
        return false;
    } else {
        return VB->isAutoRepeat(VB_UI_DOWN);
    }
}

bool MenuBoardScreenConfig::condSelectPrev() {
    if (getSelectedIndex() == 0) { //�擪�A�C�e��
        return false;
    } else {
        return VB->isAutoRepeat(VB_UI_UP);
    }
}

bool MenuBoardScreenConfig::condSelectExNext() {
    return false;
}

bool MenuBoardScreenConfig::condSelectExPrev() {
    return false;
}

void MenuBoardScreenConfig::onRise() {
    in_FULL_SCREEN_                = PROPERTY::FULL_SCREEN;
    in_DUAL_VIEW_                  = PROPERTY::DUAL_VIEW;
    in_SWAP_GAME_VIEW_             = PROPERTY::SWAP_GAME_VIEW;
    in_FIXED_GAME_VIEW_ASPECT_     = PROPERTY::FIXED_GAME_VIEW_ASPECT;
    in_DUAL_VIEW_DRAW_POSITION1_   = PROPERTY::DUAL_VIEW_DRAW_POSITION1;
    in_DUAL_VIEW_DRAW_POSITION2_   = PROPERTY::DUAL_VIEW_DRAW_POSITION2;
    in_SINGLE_VIEW_DRAW_POSITION_  = PROPERTY::SINGLE_VIEW_DRAW_POSITION;
    int num_adapter = pGOD->_num_adapter;
    GgafDxGod::AdapterRezos* paAdapterRezos = pGOD->_paAdapterRezos;
    if (num_adapter >= 1) {
        rezo_num_ = paAdapterRezos[0].rezo_num;
        GgafDxGod::RezoInfo* paRezos = paAdapterRezos[0].paRezoInfo;
        rezo_index_ = GgafDxGod::checkAppropriateDisplaySize(
                            paRezos, rezo_num_,
                            (UINT)PROPERTY::getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH"),
                            (UINT)PROPERTY::getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT")
                      );
        rezo1_num_ = rezo_num_;
        rezo1_index_ = GgafDxGod::checkAppropriateDisplaySize(
                            paRezos, rezo1_num_,
                            (UINT)PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH"),
                            (UINT)PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT")
                       );
    }
    if (num_adapter >= 2) {
        rezo2_num_ = paAdapterRezos[1].rezo_num;
        GgafDxGod::RezoInfo* paRezos = paAdapterRezos[1].paRezoInfo;
        rezo2_index_ = GgafDxGod::checkAppropriateDisplaySize(
                            paRezos, rezo2_num_,
                            (UINT)PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH"),
                            (UINT)PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT")
                       );
    }
    selectItem(ITEM_FULL_SCREEN); //�����I���A�C�e����ݒ�

    replaceItem();
    MenuBoard::onRise();
}

void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    World* pWorld = pGOD->getSpacetime()->getWorld();
    //�L�[���́A�{�^�����́A���f
    VirtualButton* pVB = VB;
    int selected_index = getSelectedIndex();

    //OK���̊m�F���j���[����
    if (selected_index == ITEM_OK || selected_index == ITEM_OK_REBOOT) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu();
        if (pSubConfirm->hasJustDecidedOk()) { //SAVE�m�FOK!
            //���v���p�e�B�֏�������
            if (getSelectedIndexOnSubCursor(SUBCUR_FULL_SCREEN) == ITEM_FULL_SCREEN) {
                PROPERTY::setValue("FULL_SCREEN", true);
            } else {
                PROPERTY::setValue("FULL_SCREEN", false);
            }
            if (PROPERTY::FULL_SCREEN != PROPERTY::getBool("FULL_SCREEN")) {
                pWorld->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW) == ITEM_DUAL_VIEW) {
                PROPERTY::setValue("DUAL_VIEW", true);
            } else {
                PROPERTY::setValue("DUAL_VIEW", false);
            }
            if (PROPERTY::DUAL_VIEW != PROPERTY::getBool("DUAL_VIEW")) {
                pWorld->need_reboot_ = 1;
            }

            if (PROPERTY::DUAL_VIEW) {
                if (getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW) == ITEM_DUAL_VIEW) {
                    PROPERTY::setValue("SWAP_GAME_VIEW", false);
                } else {
                    PROPERTY::setValue("SWAP_GAME_VIEW", true);
                }
            }
            if (PROPERTY::SWAP_GAME_VIEW != PROPERTY::getBool("SWAP_GAME_VIEW")) {
                pWorld->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSubCursor(SUBCUR_FIXED_GAME_VIEW_ASPECT) == ITEM_FIXED_GAME_VIEW_ASPECT) {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", true);
            } else {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", false);
            }
            //_TRACE_("PROPERTY::FULL_SCREEN="<<PROPERTY::FULL_SCREEN<<" PROPERTY::FIXED_GAME_VIEW_ASPECT="<<PROPERTY::FIXED_GAME_VIEW_ASPECT<<" PROPERTY::getBool(\"FIXED_GAME_VIEW_ASPECT\")="<<PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT"));
            if (PROPERTY::FIXED_GAME_VIEW_ASPECT != PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT")) {
                pWorld->need_reboot_ = 1;
            }

            int pos = getSelectedIndexOnSubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION)+1 - VALUE_POS_1;
            PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", pos);
            if (PROPERTY::SINGLE_VIEW_DRAW_POSITION != PROPERTY::getInt("SINGLE_VIEW_DRAW_POSITION")) {
                pWorld->need_reboot_ = 1;
            }

            int pos1 = getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1)+1 - VALUE_POS1_1;
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", pos1);
            int pos2 = getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2)+1 - VALUE_POS2_1;
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION2", pos2);
            if (PROPERTY::DUAL_VIEW_DRAW_POSITION1 != PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION1")) {
                pWorld->need_reboot_ = 1;
            }
            if (PROPERTY::DUAL_VIEW_DRAW_POSITION2 != PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION2")) {
                pWorld->need_reboot_ = 1;
            }

            //FULL_SCREEN�ADUAL_VIEW�́A�A�v�����s���ɕύX�ł��Ȃ��B ���ݒl��ێ�
            bool tmp_FULL_SCREEN = PROPERTY::FULL_SCREEN;
            bool tmp_DUAL_VIEW   = PROPERTY::DUAL_VIEW;
            bool tmp_SWAP_GAME_VIEW = PROPERTY::SWAP_GAME_VIEW;
            PROPERTY::save(VV_CONFIG_FILE); //�v���p�e�B�ۑ�
            PROPERTY::load(VV_CONFIG_FILE); //�v���p�e�B�Ĕ��f
            //�v�ċN���v���p�e�B�́A���Q�[���ɎQ�Ƃ���Ă͍���ɂŁA�����ɖ߂��BMap�ɏ�������ł�̂ōċN����ɔ��f�����
            PROPERTY::FULL_SCREEN = tmp_FULL_SCREEN;
            PROPERTY::DUAL_VIEW = tmp_DUAL_VIEW;
            PROPERTY::SWAP_GAME_VIEW = tmp_SWAP_GAME_VIEW;

            //���s���A�v���֑������f�ł�����͔̂��f
            GgafDxCore::GgafDxGod::chengeViewAspect(PROPERTY::FIXED_GAME_VIEW_ASPECT);
            if (PROPERTY::DUAL_VIEW) {
                GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::DUAL_VIEW_DRAW_POSITION1);
                GgafDxCore::GgafDxGod::chengeViewPos2(PROPERTY::DUAL_VIEW_DRAW_POSITION2);
            } else {
                GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::SINGLE_VIEW_DRAW_POSITION);
            }

            if (selected_index == ITEM_OK_REBOOT) { //����Ƀ��u�[�g
                God::reboot(); //�ċN���I
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
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_TRUE);
            PROPERTY::setValue("FULL_SCREEN", true);
            replaceItem();
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_FULL_SCREEN, VALUE_FULL_SCREEN_FALSE);
            PROPERTY::setValue("FULL_SCREEN", false);
            replaceItem();
        }
    } else if (selected_index == ITEM_DUAL_VIEW) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_DUAL_VIEW, VALUE_DUAL_VIEW_TRUE);
            PROPERTY::setValue("DUAL_VIEW", true);
            replaceItem();
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_DUAL_VIEW, VALUE_DUAL_VIEW_FALSE);
            PROPERTY::setValue("DUAL_VIEW", false);
            replaceItem();
        }
    } else if (selected_index == ITEM_SWAP_GAME_VIEW) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_FALSE);
            PROPERTY::setValue("SWAP_GAME_VIEW", false);
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_TRUE);
            PROPERTY::setValue("SWAP_GAME_VIEW", true);
        }
    } else if (selected_index == ITEM_FIXED_GAME_VIEW_ASPECT) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySubCursor(SUBCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_TRUE);
            PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", true);
            if (!pWorld->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewAspect(true);
            }
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySubCursor(SUBCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_FALSE);
            PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", false);
            if (!pWorld->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewAspect(false);
            }
        }
    } else if (selected_index == ITEM_SINGLE_VIEW_DRAW_POSITION) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION);
            if (i == VALUE_POS_9) {
                i = VALUE_POS_1;
            } else {
                i++;
            }
            selectItemBySubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION, i);
            PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", i+1 - VALUE_POS_1);
            if (!pWorld->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS_1);
            }
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION);
            if (i == VALUE_POS_1) {
                i = VALUE_POS_9;
            } else {
                i--;
            }
            selectItemBySubCursor(SUBCUR_SINGLE_VIEW_DRAW_POSITION, i);
            PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", i+1 - VALUE_POS_1);
            if (!pGOD->getSpacetime()->getWorld()->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS_1);
            }
        }
    } else if (selected_index == ITEM_DUAL_VIEW_DRAW_POSITION1) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1);
            if (i == VALUE_POS1_9) {
                i = VALUE_POS1_1;
            } else {
                i++;
            }
            selectItemBySubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS1_1);
            GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS1_1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1);
            if (i == VALUE_POS1_1) {
                i = VALUE_POS1_9;
            } else {
                i--;
            }
            selectItemBySubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION1, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS1_1);
            GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS1_1);
        }
    } else if (selected_index == ITEM_DUAL_VIEW_DRAW_POSITION2) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2);
            if (i == VALUE_POS2_9) {
                i = VALUE_POS2_1;
            } else {
                i++;
            }
            selectItemBySubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS2_1);
            GgafDxCore::GgafDxGod::chengeViewPos2(i+1 - VALUE_POS2_1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            int i = getSelectedIndexOnSubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2);
            if (i == VALUE_POS2_1) {
                i = VALUE_POS2_9;
            } else {
                i--;
            }
            selectItemBySubCursor(SUBCUR_DUAL_VIEW_DRAW_POSITION2, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS2_1);
            GgafDxCore::GgafDxGod::chengeViewPos2(i+1 - VALUE_POS2_1);
        }
    } else if (selected_index == ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION) {
        bool is_right = pVB->isAutoRepeat(VB_UI_RIGHT);
        bool is_left = pVB->isAutoRepeat(VB_UI_LEFT);
        if (is_right || is_left) {
            if (is_right) {
                if (rezo_index_ >= rezo_num_-1) {
                    rezo_index_ = 0;
                } else {
                    rezo_index_++;
                }
            } else if (is_left) {
                if (rezo_index_ <= 0) {
                    rezo_index_ = rezo_num_-1;
                } else {
                    rezo_index_--;
                }
            }
            if (rezo_num_ > 0) {
                GgafDxGod::AdapterRezos* paAdapterRezos = pGOD->_paAdapterRezos;
                FontBoardActor* pLabelRezo  = (FontBoardActor*) getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION);
                pLabelRezo->update(paAdapterRezos[0].paRezoInfo[rezo_index_].item_str.c_str());
                PROPERTY::setValue("SINGLE_VIEW_FULL_SCREEN_WIDTH" , paAdapterRezos[0].paRezoInfo[rezo_index_].width);
                PROPERTY::setValue("SINGLE_VIEW_FULL_SCREEN_HEIGHT", paAdapterRezos[0].paRezoInfo[rezo_index_].height);
            }
        }
    } else if (selected_index == ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION) {
        bool is_right = pVB->isAutoRepeat(VB_UI_RIGHT);
        bool is_left = pVB->isAutoRepeat(VB_UI_LEFT);
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
                GgafDxGod::AdapterRezos* paAdapterRezos = pGOD->_paAdapterRezos;
                FontBoardActor* pLabelRezo1  = (FontBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION);
                pLabelRezo1->update(paAdapterRezos[0].paRezoInfo[rezo1_index_].item_str.c_str());
                PROPERTY::setValue("DUAL_VIEW_FULL_SCREEN1_WIDTH" , paAdapterRezos[0].paRezoInfo[rezo1_index_].width);
                PROPERTY::setValue("DUAL_VIEW_FULL_SCREEN1_HEIGHT", paAdapterRezos[0].paRezoInfo[rezo1_index_].height);
            }
        }
    } else if (selected_index == ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION) {
        bool is_right = pVB->isAutoRepeat(VB_UI_RIGHT);
        bool is_left = pVB->isAutoRepeat(VB_UI_LEFT);
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
                GgafDxGod::AdapterRezos* paAdapterRezos = pGOD->_paAdapterRezos;
                FontBoardActor* pLabelRezo2 = (FontBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION);
                pLabelRezo2->update(paAdapterRezos[1].paRezoInfo[rezo2_index_].item_str.c_str());
                PROPERTY::setValue("DUAL_VIEW_FULL_SCREEN2_WIDTH" , paAdapterRezos[1].paRezoInfo[rezo2_index_].width);
                PROPERTY::setValue("DUAL_VIEW_FULL_SCREEN2_HEIGHT", paAdapterRezos[1].paRezoInfo[rezo2_index_].height);
            }
        } else {
            //1��ʂȂ̂ŁA�ݒ�o���Ȃ��B
            if (is_right || is_left) {
                getSeTransmitter()->play(SE_WRONG);
            }
        }
    }
}

void MenuBoardScreenConfig::onDecision(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_CANCEL) {
        PROPERTY::FULL_SCREEN               = in_FULL_SCREEN_              ;
        PROPERTY::DUAL_VIEW                 = in_DUAL_VIEW_                ;
        PROPERTY::SWAP_GAME_VIEW            = in_SWAP_GAME_VIEW_           ;
        PROPERTY::FIXED_GAME_VIEW_ASPECT    = in_FIXED_GAME_VIEW_ASPECT_   ;
        PROPERTY::DUAL_VIEW_DRAW_POSITION1  = in_DUAL_VIEW_DRAW_POSITION1_ ;
        PROPERTY::DUAL_VIEW_DRAW_POSITION2  = in_DUAL_VIEW_DRAW_POSITION2_ ;
        PROPERTY::SINGLE_VIEW_DRAW_POSITION = in_SINGLE_VIEW_DRAW_POSITION_;
        GgafDxCore::GgafDxGod::chengeViewAspect(PROPERTY::FIXED_GAME_VIEW_ASPECT);
        if (PROPERTY::DUAL_VIEW) {
            GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::DUAL_VIEW_DRAW_POSITION1);
            GgafDxCore::GgafDxGod::chengeViewPos2(PROPERTY::DUAL_VIEW_DRAW_POSITION2);
        } else {
            GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::SINGLE_VIEW_DRAW_POSITION);
        }
        sinkMe();
    } else if (prm_item_index == ITEM_OK) { //�ۑ���OK
        riseSubMenu(getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE�m�F���j���[�N��
    } else if (prm_item_index == ITEM_OK_REBOOT) { //OK�ōċN��
        riseSubMenu(getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE�m�F���j���[�N��
    } else {

    }
}

void MenuBoardScreenConfig::onCancel(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
