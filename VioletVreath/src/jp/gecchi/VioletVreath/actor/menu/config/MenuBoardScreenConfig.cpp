#include "stdafx.h"
#include "MenuBoardScreenConfig.h"

#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "CursorConfig003.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardScreenConfig::MenuBoardScreenConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01"),  itm(ITEM_SCREEN_MODE, ITEM_BANPEI), cur(SUPCUR_SCREEN_MODE, SUPCUR_BANPEI) {
    _class_name = "MenuBoardScreenConfig";

    const char* apItemStr[] = {
          "SCREEN MODE (*)",
          "SCREEN NUM (*)",
          "SWAP SCREEN (*)",
          "GAME VIEW ASPECT TYPE",
          "GAME VIEW POSITION",
          "GAME VIEW POSITION1", "GAME VIEW POSITION2",
          "OK & SAVE",
          "CANCEL",

          "FULL SCREEN", "WINDOW MODE",
          "SINGLE VIEW", "DUAL VIEW",
          "NO"         , "YES",
          "FIX"        , "STRETCH",
          "1", "2", "3", "4", "5", "6", "7", "8", "9",
          "1", "2", "3", "4", "5", "6", "7", "8", "9",
          "1", "2", "3", "4", "5", "6", "7", "8", "9",

    };

    if (PROPERTY::DUAL_VIEW) {
        itm.remove(ITEM_VIEW_POSITION);
        itm.remove(ITEM_POS_1, ITEM_POS_9);
        cur.remove(SUPCUR_VIEW_POSITION);
    } else {
        itm.remove(ITEM_SWAP_GAME_VIEW);
        itm.remove(ITEM_VIEW_POSITION1);
        itm.remove(ITEM_VIEW_POSITION2);
        itm.remove(ITEM_POS1_1, ITEM_POS1_9);
        itm.remove(ITEM_POS2_1, ITEM_POS2_9);
        cur.remove(SUPCUR_SWAP_GAME_VIEW);
        cur.remove(SUPCUR_VIEW_POSITION1);
        cur.remove(SUPCUR_VIEW_POSITION2);
    }


    //���j���[�E�B���h�E�ݒ�
    update( "%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            "-.............................../");
    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("[SCREEN CONFIG]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(300), PX_C(40));

    //�ݒ荀�ڃA�C�e��(ITEM_SCREEN_MODE �` ITEM_CANCEL)
    for (int i = itm.n(ITEM_SCREEN_MODE); i <= itm.n(ITEM_CANCEL); i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(apItemStr[itm.e(i)], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel);
    }
    relateAllItemToCancel(itm.n(ITEM_CANCEL)); //�L�����Z���A�C�e���ݒ�
    coord y = PX_C(100);
    coord lh = PX_C(32);
    positionItem(itm.n(ITEM_SCREEN_MODE)     , PX_C(100), y);  y += lh;
    positionItem(itm.n(ITEM_VIEW_NUM)        , PX_C(100), y);  y += lh;
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_SWAP_GAME_VIEW)  , PX_C(100), y);  y += lh;
    }
    positionItem(itm.n(ITEM_VIEW_ASPECT_TYPE), PX_C(100), y);  y += lh;
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_VIEW_POSITION1)  , PX_C(100), y);  y += lh;
        positionItem(itm.n(ITEM_VIEW_POSITION2)  , PX_C(100), y);  y += lh;
    } else {
        positionItem(itm.n(ITEM_VIEW_POSITION)  , PX_C(100), y);  y += lh;
    }
    positionItem(itm.n(ITEM_OK)              , PX_C(50) , y);
    positionItem(itm.n(ITEM_CANCEL)          , PX_C(300), y);  y += lh;

    //�ݒ荀�ڂ̑I�����A�C�e��
    for (int i = itm.n(ITEM_SCREEN_MODE_FULL_SCREEN); i < itm.n(ITEM_BANPEI); i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(apItemStr[itm.e(i)], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel);
    }
    y = PX_C(100);
    positionItem(itm.n(ITEM_SCREEN_MODE_FULL_SCREEN) , PX_C(400), y); positionItem(itm.n(ITEM_SCREEN_MODE_WINDOW_MODE) , PX_C(600), y); y += lh;
    positionItem(itm.n(ITEM_VIEW_NUM_SINGLE)         , PX_C(400), y); positionItem(itm.n(ITEM_VIEW_NUM_DUAL)           , PX_C(600), y); y += lh;
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_SWAP_GAME_VIEW_NO), PX_C(400), y); positionItem(itm.n(ITEM_SWAP_GAME_VIEW_YES), PX_C(600), y); y += lh;
    }
    positionItem(itm.n(ITEM_VIEW_ASPECT_TYPE_FIX)    , PX_C(400), y); positionItem(itm.n(ITEM_VIEW_ASPECT_TYPE_STRETCH), PX_C(600), y); y += lh;
    if (PROPERTY::DUAL_VIEW) {
        for (int i = 0; i < 9; i++) { positionItem(itm.n(ITEM_POS1_1) + i , PX_C(400 + i*20), y); } y += lh;
        for (int i = 0; i < 9; i++) { positionItem(itm.n(ITEM_POS2_1) + i , PX_C(400 + i*20), y); } y += lh;
    } else {
        for (int i = 0; i < 9; i++) { positionItem(itm.n(ITEM_POS_1) + i , PX_C(400 + i*20), y); } y += lh;
    }

    //�������b�Z�[�W
    pLabel_Msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_Msg_->update("(*) NEED REBOOT .\n"
                        "PRESS ^ OR V TO SELECT, AND <- OR -> TO SETTING VALUE.",
                        ALIGN_LEFT, VALIGN_MIDDLE);
    addDisp(pLabel_Msg_, PX_C(10), PX_C(500));

    //���C�����j���[�J�[�\����ݒ�
    CursorConfig003* pCursor = NEW CursorConfig003("MainCursor");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    //�ݒ�l�⏕�J�[�\��
    for (int i = cur.n(SUPCUR_SCREEN_MODE); i < cur.n(SUPCUR_BANPEI); i++) {
        CursorConfig003* pSupCur = NEW CursorConfig003("SupCur");
        pSupCur->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        addSupCursor(pSupCur);
    }

    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0�� Yes No �₢���킹���j���[���T�u���j���[�ɒǉ�
}

bool MenuBoardScreenConfig::condSelectNext() {
    if (getSelectedIndex() == itm.n(ITEM_CANCEL)) { //CANCEL�����֐i�߂Ȃ�����
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
    selectItem(itm.n(ITEM_SCREEN_MODE)); //�⏕�J�[�\���̏����I���A�C�e����ݒ�
    if (PROPERTY::FULL_SCREEN) {
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN_MODE), itm.n(ITEM_SCREEN_MODE_FULL_SCREEN));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN_MODE), itm.n(ITEM_SCREEN_MODE_WINDOW_MODE));
    }
    if (PROPERTY::DUAL_VIEW) {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_NUM), itm.n(ITEM_VIEW_NUM_DUAL));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_NUM), itm.n(ITEM_VIEW_NUM_SINGLE));
    }
    if (PROPERTY::DUAL_VIEW) {
        if (PROPERTY::SWAP_GAME_VIEW) {
            selectItemBySupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW), itm.n(ITEM_SWAP_GAME_VIEW_YES));
        } else {
            selectItemBySupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW), itm.n(ITEM_SWAP_GAME_VIEW_NO));
        }
    }
    if (PROPERTY::FIXED_GAME_VIEW_ASPECT) {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_ASPECT), itm.n(ITEM_VIEW_ASPECT_TYPE_FIX));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_ASPECT), itm.n(ITEM_VIEW_ASPECT_TYPE_STRETCH));
    }
    if (PROPERTY::DUAL_VIEW) {
        int pos1 = PROPERTY::DUAL_VIEW_DRAW_POSITION1;
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION1), itm.n(ITEM_POS1_1) + (pos1-1));
        int pos2 = PROPERTY::DUAL_VIEW_DRAW_POSITION2;
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION2), itm.n(ITEM_POS2_1) + (pos2-1));
    } else {
        int pos = PROPERTY::SINGLE_VIEW_DRAW_POSITION;
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION), itm.n(ITEM_POS_1) + (pos-1));
    }

    MenuBoard::onRise();
}

void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    //�L�[���́A�{�^�����́A���f
    VirtualButton* pVB = VB;
    int selected_index = getSelectedIndex();

    //OK���̊m�F���j���[����
    if (selected_index == itm.n(ITEM_OK)) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) { //SAVE�m�FOK!
            //���v���p�e�B�֏�������
            if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_SCREEN_MODE)) == itm.n(ITEM_SCREEN_MODE_FULL_SCREEN)) {
                PROPERTY::setValue("FULL_SCREEN", true);
            } else {
                PROPERTY::setValue("FULL_SCREEN", false);
            }
            if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_NUM)) == itm.n(ITEM_VIEW_NUM_DUAL)) {
                PROPERTY::setValue("DUAL_VIEW", true);
            } else {
                PROPERTY::setValue("DUAL_VIEW", false);
            }
            if (PROPERTY::DUAL_VIEW) {
                if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW)) == itm.n(ITEM_SWAP_GAME_VIEW_NO)) {
                    PROPERTY::setValue("SWAP_GAME_VIEW", false);
                } else {
                    PROPERTY::setValue("SWAP_GAME_VIEW", true);
                }
            }
            if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_ASPECT)) == itm.n(ITEM_VIEW_ASPECT_TYPE_FIX)) {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", true);
            } else {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", false);
            }
            if (PROPERTY::DUAL_VIEW) {
                int pos1 = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION1))+1 - itm.n(ITEM_POS1_1);
                PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", pos1);
                int pos2 = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION2))+1 - itm.n(ITEM_POS2_1);
                PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION2", pos2);
            } else {
                int pos = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION))+1 - itm.n(ITEM_POS_1);
                PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", pos);
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

            sinkCurrentSubMenu();
            sinkMe();
        } else if (pSubConfirm->isJustDecidedCancel()) { //�m�F�ŃL�����Z��
            sinkCurrentSubMenu();
        } else {

        }
    }
    //�e�ݒ荀�ڂ́������̏���
    if (selected_index == itm.n(ITEM_SCREEN_MODE)) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(cur.n(SUPCUR_SCREEN_MODE), itm.n(ITEM_SCREEN_MODE_FULL_SCREEN));
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(cur.n(SUPCUR_SCREEN_MODE), itm.n(ITEM_SCREEN_MODE_WINDOW_MODE));
        }
    } else if (selected_index == itm.n(ITEM_VIEW_NUM)) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(cur.n(SUPCUR_VIEW_NUM), itm.n(ITEM_VIEW_NUM_SINGLE));
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(cur.n(SUPCUR_VIEW_NUM), itm.n(ITEM_VIEW_NUM_DUAL));
        }
    } else if (selected_index == itm.n(ITEM_VIEW_ASPECT_TYPE)) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(cur.n(SUPCUR_VIEW_ASPECT), itm.n(ITEM_VIEW_ASPECT_TYPE_FIX));
            GgafDxCore::GgafDxGod::chengeViewAspect(true);
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(cur.n(SUPCUR_VIEW_ASPECT), itm.n(ITEM_VIEW_ASPECT_TYPE_STRETCH));
            GgafDxCore::GgafDxGod::chengeViewAspect(false);
        }
    }
    if (PROPERTY::DUAL_VIEW) {
        if (selected_index == itm.n(ITEM_SWAP_GAME_VIEW)) {
            if (pVB->isPushedDown(VB_UI_LEFT)) {
                selectItemBySupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW), itm.n(ITEM_SWAP_GAME_VIEW_NO));
            } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
                selectItemBySupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW), itm.n(ITEM_SWAP_GAME_VIEW_YES));
            }
        }
    }
    if (PROPERTY::DUAL_VIEW) {
        //2��ʎ�
        if (selected_index == itm.n(ITEM_VIEW_POSITION1)) {
            if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
                int i = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION1));
                if (i == itm.n(ITEM_POS1_9)) {
                    i = itm.n(ITEM_POS1_1);
                } else {
                    i++;
                }
                selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION1), i);
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - itm.n(ITEM_POS1_1));
            } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
                int i = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION1));
                if (i == itm.n(ITEM_POS1_1)) {
                    i = itm.n(ITEM_POS1_9);
                } else {
                    i--;
                }
                selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION1), i);
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - itm.n(ITEM_POS1_1));
            }
        } else if (selected_index == itm.n(ITEM_VIEW_POSITION2)) {
            if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
                int i = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION2));
                if (i == itm.n(ITEM_POS2_9)) {
                    i = itm.n(ITEM_POS2_1);
                } else {
                    i++;
                }
                selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION2), i);
                GgafDxCore::GgafDxGod::chengeViewPos2(i+1 - itm.n(ITEM_POS2_1));
            } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
                int i = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION2));
                if (i == itm.n(ITEM_POS2_1)) {
                    i = itm.n(ITEM_POS2_9);
                } else {
                    i--;
                }
                selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION2), i);
                GgafDxCore::GgafDxGod::chengeViewPos2(i+1 - itm.n(ITEM_POS2_1));
            }
        }
    } else {
        //�P��ʎ�
        if (selected_index == itm.n(ITEM_VIEW_POSITION)) {
            if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
                int i = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION));
                if (i == itm.n(ITEM_POS_9)) {
                    i = itm.n(ITEM_POS_1);
                } else {
                    i++;
                }
                selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION), i);
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - itm.n(ITEM_POS_1));
            } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
                int i = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION));
                if (i == itm.n(ITEM_POS_1)) {
                    i = itm.n(ITEM_POS_9);
                } else {
                    i--;
                }
                selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION), i);
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - itm.n(ITEM_POS_1));
            }
        }
    }
}

void MenuBoardScreenConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == itm.n(ITEM_CANCEL)) {
        //���ɖ߂�
        PROPERTY::load(VV_CONFIG_FILE); //�����v���p�e�B�ǂݍ���
        GgafDxCore::GgafDxGod::chengeViewAspect(PROPERTY::FIXED_GAME_VIEW_ASPECT);
        if (PROPERTY::DUAL_VIEW) {
            GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::DUAL_VIEW_DRAW_POSITION1);
            GgafDxCore::GgafDxGod::chengeViewPos2(PROPERTY::DUAL_VIEW_DRAW_POSITION2);
        } else {
            GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::SINGLE_VIEW_DRAW_POSITION);
        }
        sinkMe();
    } else if (prm_item_index == itm.n(ITEM_OK)) { //�ۑ���OK
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE�m�F���j���[�N��
    } else {

    }
}
void MenuBoardScreenConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
