#include "stdafx.h"
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
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"


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

    //[0]:フルスクリーン時、[1]:ウィンドウ時
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

    //メニューウィンドウ設定
    update( "%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            ")***************************************+\n"
            "-......................................./");

    //説明メッセージ
    pLabel_Msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_Msg_->update("(*) NEED REBOOT .\n"
                        "PRESS ^ OR V TO SELECT, AND <- OR -> TO SETTING VALUE.",
                        ALIGN_LEFT, VALIGN_MIDDLE);
    addDisp(pLabel_Msg_, PX_C(10), PX_C(500));


    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("[SCREEN CONFIG]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_title, PX_C(300), PX_C(40));

    //設定項目アイテム
    for (int i = ITEM_FULL_SCREEN; i <= ITEM_CANCEL; i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(arrItemStr[i], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel);
    }
    relateAllItemToCancel(ITEM_CANCEL); //キャンセルアイテム設定

    //設定項目の設定値アイテム
    for (int i = VALUE_FULL_SCREEN_TRUE; i < ITEM_BANPEI; i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(arrItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel);
    }


    //設定項目メインメニューカーソルを設定
    CursorConfig003* pCursor = NEW CursorConfig003("MainCursor");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    //設定値補助カーソル
    for (int i = SUPCUR_FULL_SCREEN; i < SUPCUR_BANPEI; i++) {
        CursorConfig003* pSupCur = NEW CursorConfig003("SupCur");
        pSupCur->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        addSupCursor(pSupCur);
    }

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0番 Yes No 問い合わせメニューをサブメニューに追加
    //addSubMenu(NEW MenuBoardResolutionSelect("ResolutionSelect"));
    in_FULL_SCREEN_                = PROPERTY::FULL_SCREEN;
    in_DUAL_VIEW_                  = PROPERTY::DUAL_VIEW;
    in_SWAP_GAME_VIEW_             = PROPERTY::SWAP_GAME_VIEW;
    in_FIXED_GAME_VIEW_ASPECT_     = PROPERTY::FIXED_GAME_VIEW_ASPECT;
    in_DUAL_VIEW_DRAW_POSITION1_   = PROPERTY::DUAL_VIEW_DRAW_POSITION1;
    in_DUAL_VIEW_DRAW_POSITION2_   = PROPERTY::DUAL_VIEW_DRAW_POSITION2;
    in_SINGLE_VIEW_DRAW_POSITION_  = PROPERTY::SINGLE_VIEW_DRAW_POSITION;
    relocateItem();
}

void MenuBoardScreenConfig::relocateItem() {
    coord x1 = PX_C(100);  //設定項目アイテムX座標
    coord y1 = PX_C(100);  //設定項目アイテムY座標
    coord lh = PX_C(32);

    //設定項目アイテム配置
    positionItem(ITEM_FULL_SCREEN, x1, y1);  y1 += lh;
    positionItem(ITEM_DUAL_VIEW  , x1, y1);  y1 += lh;
    if (PROPERTY::getBool("FULL_SCREEN")) {
        if (PROPERTY::getBool("DUAL_VIEW")) {
            getItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->activate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->activate();
            positionItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION  , x1, y1);  y1 += lh;
            positionItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION  , x1, y1);  y1 += lh;
        } else {
            getItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->activate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
            getItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
            positionItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION , x1, y1);  y1 += lh;
        }
    } else {
        getItem(ITEM_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(ITEM_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
        getItem(ITEM_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
    }
    if (PROPERTY::getBool("DUAL_VIEW")) {
        getItem(ITEM_SWAP_GAME_VIEW)->activate();
        positionItem(ITEM_SWAP_GAME_VIEW, x1, y1);  y1 += lh;
    } else {
        getItem(ITEM_SWAP_GAME_VIEW)->inactivate();
    }
    positionItem(ITEM_FIXED_GAME_VIEW_ASPECT, x1, y1);  y1 += lh;
    if (PROPERTY::getBool("DUAL_VIEW")) {
        getItem(ITEM_SINGLE_VIEW_DRAW_POSITION)->inactivate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION1)->activate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION2)->activate();
        positionItem(ITEM_DUAL_VIEW_DRAW_POSITION1, x1, y1);  y1 += lh;
        positionItem(ITEM_DUAL_VIEW_DRAW_POSITION2, x1, y1);  y1 += lh;
    } else {
        getItem(ITEM_SINGLE_VIEW_DRAW_POSITION)->activate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION1)->inactivate();
        getItem(ITEM_DUAL_VIEW_DRAW_POSITION2)->inactivate();
        positionItem(ITEM_SINGLE_VIEW_DRAW_POSITION, x1, y1);  y1 += lh;
    }
    positionItem(ITEM_OK        , PX_C(50) , PX_C(320));
    positionItem(ITEM_OK_REBOOT , PX_C(250), PX_C(320));
    positionItem(ITEM_CANCEL    , PX_C(450), PX_C(320));

    //設定項目の選択値アイテム配置
    coord x2 = PX_C(700);  //選択値アイテムX座標
    coord y2 = PX_C(100);  //選択値アイテムY座標
    positionItem(VALUE_FULL_SCREEN_TRUE, x2, y2);  positionItem(VALUE_FULL_SCREEN_FALSE, x2+PX_C(200), y2);  y2 += lh;
    positionItem(VALUE_DUAL_VIEW_TRUE  , x2, y2);  positionItem(VALUE_DUAL_VIEW_FALSE  , x2+PX_C(200), y2);  y2 += lh;

    if (PROPERTY::getBool("FULL_SCREEN")) {
        if (PROPERTY::getBool("DUAL_VIEW")) {
            getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->activate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->activate();
            positionItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION , x2, y2);  y2 += lh;
            positionItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION , x2, y2);  y2 += lh;
        } else {
            getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->activate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
            getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
            positionItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION, x2, y2);  y2 += lh;
        }
    } else {
        getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
        getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
        getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        getItem(VALUE_SWAP_GAME_VIEW_FALSE)->activate();  getItem(VALUE_SWAP_GAME_VIEW_TRUE)->activate();
        positionItem(VALUE_SWAP_GAME_VIEW_FALSE, x2, y2);   positionItem(VALUE_SWAP_GAME_VIEW_TRUE, x2+PX_C(200), y2);  y2 += lh;
    } else {
        getItem(VALUE_SWAP_GAME_VIEW_FALSE)->inactivate();    getItem(VALUE_SWAP_GAME_VIEW_TRUE)->inactivate();
    }
    positionItem(VALUE_FIXED_GAME_VIEW_TRUE  , x2, y2);  positionItem(VALUE_FIXED_GAME_VIEW_FALSE, x2+PX_C(200), y2);  y2 += lh;

    if (PROPERTY::getBool("DUAL_VIEW")) {
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS_1 + i)->inactivate();
        }
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS1_1 + i)->activate();
            positionItem(VALUE_POS1_1 + i, x2+PX_C(i*20), y2);
        }   y2 += lh;
        for (int i = 0; i < 9; i++) {
            getItem(VALUE_POS2_1 + i)->activate();
            positionItem(VALUE_POS2_1 + i , x2+PX_C(i*20), y2);
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
            positionItem(VALUE_POS_1 + i , x2+PX_C(i*20), y2);
        }   y2 += lh;
    }

    //設定項目の選択サブカーソル配置
    if (PROPERTY::getBool("FULL_SCREEN")) {
        selectItemBySupCursor(SUPCUR_FULL_SCREEN, VALUE_FULL_SCREEN_TRUE, false);
    } else {
        selectItemBySupCursor(SUPCUR_FULL_SCREEN, VALUE_FULL_SCREEN_FALSE, false);
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        selectItemBySupCursor(SUPCUR_DUAL_VIEW, VALUE_DUAL_VIEW_TRUE, false);
    } else {
        selectItemBySupCursor(SUPCUR_DUAL_VIEW, VALUE_DUAL_VIEW_FALSE, false);
    }

    if (PROPERTY::getBool("FULL_SCREEN")) {
        if (PROPERTY::getBool("DUAL_VIEW")) {
            getSupCursor(SUPCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
            getSupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->activate();
            getSupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->activate();
            selectItemBySupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION, VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION, false);
            selectItemBySupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION, VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION, false);
        } else {
            getSupCursor(SUPCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->activate();
            getSupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
            getSupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
            selectItemBySupCursor(SUPCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION, VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION, false);
        }
    } else {
        getSupCursor(SUPCUR_SINGLE_VIEW_FULL_SCREEN_RESOLUTION)->inactivate();
        getSupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN1_RESOLUTION)->inactivate();
        getSupCursor(SUPCUR_DUAL_VIEW_FULL_SCREEN2_RESOLUTION)->inactivate();
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        getSupCursor(SUPCUR_SWAP_GAME_VIEW)->activate();
        if (PROPERTY::getBool("SWAP_GAME_VIEW")) {
            selectItemBySupCursor(SUPCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_TRUE, false);
        } else {
            selectItemBySupCursor(SUPCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_FALSE, false);
        }
    } else {
        getSupCursor(SUPCUR_SWAP_GAME_VIEW)->inactivate();
    }
    if (PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT")) {
        selectItemBySupCursor(SUPCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_TRUE, false);
    } else {
        selectItemBySupCursor(SUPCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_FALSE, false);
    }
    if (PROPERTY::getBool("DUAL_VIEW")) {
        getSupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION)->inactivate();
        getSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1)->activate();
        getSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2)->activate();
        int pos1 = PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION1");
        selectItemBySupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1, VALUE_POS1_1+(pos1-1), false);
        int pos2 = PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION2");
        selectItemBySupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2, VALUE_POS2_1+(pos2-1), false);
    } else {
        getSupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION)->activate();
        getSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1)->inactivate();
        getSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2)->inactivate();
        int pos = PROPERTY::getInt("SINGLE_VIEW_DRAW_POSITION");
        selectItemBySupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION, VALUE_POS_1+(pos-1), false);
    }

    StringBoardActor* pLabelRezo  = (StringBoardActor*) getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION);
    std::string rezo = XTOS(PROPERTY::getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH")) + "X" + XTOS(PROPERTY::getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT"));
    pLabelRezo->update(rezo.c_str());

    StringBoardActor* pLabelRezo1 = (StringBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION);
    std::string rezo1 = XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH")) + "X" + XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT"));
    pLabelRezo1->update(rezo1.c_str());

    StringBoardActor* pLabelRezo2 = (StringBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION);
    std::string rezo2 = XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH")) + "X" + XTOS(PROPERTY::getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT"));
    pLabelRezo2->update(rezo2.c_str());
}

bool MenuBoardScreenConfig::condSelectNext() {
    if (getSelectedIndex() == ITEM_CANCEL) { //CANCELから先へ進めなくする
        return false;
    } else {
        return VB->isAutoRepeat(VB_UI_DOWN);
    }
}

bool MenuBoardScreenConfig::condSelectPrev() {
    if (getSelectedIndex() == 0) { //先頭アイテム
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
    int num_adapter = P_GOD->_num_adapter;
    GgafDxGod::AdapterRezos* paAdapterRezos = P_GOD->_paAdapterRezos;
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
    selectItem(ITEM_FULL_SCREEN); //初期選択アイテムを設定

    relocateItem();
    MenuBoard::onRise();
}

void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    //キー入力、ボタン入力、反映
    VirtualButton* pVB = VB;
    int selected_index = getSelectedIndex();

    //OK時の確認メニュー判定
    if (selected_index == ITEM_OK || selected_index == ITEM_OK_REBOOT) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) { //SAVE確認OK!
            //現プロパティへ書き込み
            if (getSelectedIndexOnSupCursor(SUPCUR_FULL_SCREEN) == ITEM_FULL_SCREEN) {
                PROPERTY::setValue("FULL_SCREEN", true);
            } else {
                PROPERTY::setValue("FULL_SCREEN", false);
            }
            if (PROPERTY::FULL_SCREEN != PROPERTY::getBool("FULL_SCREEN")) {
                P_WORLD->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW) == ITEM_DUAL_VIEW) {
                PROPERTY::setValue("DUAL_VIEW", true);
            } else {
                PROPERTY::setValue("DUAL_VIEW", false);
            }
            if (PROPERTY::DUAL_VIEW != PROPERTY::getBool("DUAL_VIEW")) {
                P_WORLD->need_reboot_ = 1;
            }

            if (PROPERTY::DUAL_VIEW) {
                if (getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW) == ITEM_DUAL_VIEW) {
                    PROPERTY::setValue("SWAP_GAME_VIEW", false);
                } else {
                    PROPERTY::setValue("SWAP_GAME_VIEW", true);
                }
            }
            if (PROPERTY::SWAP_GAME_VIEW != PROPERTY::getBool("SWAP_GAME_VIEW")) {
                P_WORLD->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSupCursor(SUPCUR_FIXED_GAME_VIEW_ASPECT) == ITEM_FIXED_GAME_VIEW_ASPECT) {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", true);
            } else {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", false);
            }
            //_TRACE_("PROPERTY::FULL_SCREEN="<<PROPERTY::FULL_SCREEN<<" PROPERTY::FIXED_GAME_VIEW_ASPECT="<<PROPERTY::FIXED_GAME_VIEW_ASPECT<<" PROPERTY::getBool(\"FIXED_GAME_VIEW_ASPECT\")="<<PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT"));
            if (PROPERTY::FIXED_GAME_VIEW_ASPECT != PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT")) {
                P_WORLD->need_reboot_ = 1;
            }

            int pos = getSelectedIndexOnSupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION)+1 - VALUE_POS_1;
            PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", pos);
            if (PROPERTY::SINGLE_VIEW_DRAW_POSITION != PROPERTY::getInt("SINGLE_VIEW_DRAW_POSITION")) {
                P_WORLD->need_reboot_ = 1;
            }

            int pos1 = getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1)+1 - VALUE_POS1_1;
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", pos1);
            int pos2 = getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2)+1 - VALUE_POS2_1;
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION2", pos2);
            if (PROPERTY::DUAL_VIEW_DRAW_POSITION1 != PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION1")) {
                P_WORLD->need_reboot_ = 1;
            }
            if (PROPERTY::DUAL_VIEW_DRAW_POSITION2 != PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION2")) {
                P_WORLD->need_reboot_ = 1;
            }

            //FULL_SCREEN、DUAL_VIEWは、アプリ実行中に変更できない。 現在値を保持
            bool tmp_FULL_SCREEN = PROPERTY::FULL_SCREEN;
            bool tmp_DUAL_VIEW   = PROPERTY::DUAL_VIEW;
            bool tmp_SWAP_GAME_VIEW = PROPERTY::SWAP_GAME_VIEW;
            PROPERTY::save(VV_CONFIG_FILE); //プロパティ保存
            PROPERTY::load(VV_CONFIG_FILE); //プロパティ再反映
            //要再起動プロパティは、現ゲームに参照されては困るにで、直ぐに戻す。Mapに書き込んでるので再起動後に反映される
            PROPERTY::FULL_SCREEN = tmp_FULL_SCREEN;
            PROPERTY::DUAL_VIEW = tmp_DUAL_VIEW;
            PROPERTY::SWAP_GAME_VIEW = tmp_SWAP_GAME_VIEW;

            //実行中アプリへ即時反映できるものは反映
            GgafDxCore::GgafDxGod::chengeViewAspect(PROPERTY::FIXED_GAME_VIEW_ASPECT);
            if (PROPERTY::DUAL_VIEW) {
                GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::DUAL_VIEW_DRAW_POSITION1);
                GgafDxCore::GgafDxGod::chengeViewPos2(PROPERTY::DUAL_VIEW_DRAW_POSITION2);
            } else {
                GgafDxCore::GgafDxGod::chengeViewPos1(PROPERTY::SINGLE_VIEW_DRAW_POSITION);
            }

            if (selected_index == ITEM_OK_REBOOT) { //さらにリブート
                God::reboot(); //再起動！
            } else {
                sinkCurrentSubMenu();
                sinkMe();
            }
        } else if (pSubConfirm->isJustDecidedCancel()) { //確認でキャンセル
            sinkCurrentSubMenu();
        } else {

        }
    }
    //各設定項目の←→時の処理
    if (selected_index == ITEM_FULL_SCREEN) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(SUPCUR_FULL_SCREEN, VALUE_FULL_SCREEN_TRUE);
            PROPERTY::setValue("FULL_SCREEN", true);
            relocateItem();
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(SUPCUR_FULL_SCREEN, VALUE_FULL_SCREEN_FALSE);
            PROPERTY::setValue("FULL_SCREEN", false);
            relocateItem();
        }
    } else if (selected_index == ITEM_DUAL_VIEW) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(SUPCUR_DUAL_VIEW, VALUE_DUAL_VIEW_TRUE);
            PROPERTY::setValue("DUAL_VIEW", true);
            relocateItem();
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(SUPCUR_DUAL_VIEW, VALUE_DUAL_VIEW_FALSE);
            PROPERTY::setValue("DUAL_VIEW", false);
            relocateItem();
        }
    } else if (selected_index == ITEM_SWAP_GAME_VIEW) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(SUPCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_FALSE);
            PROPERTY::setValue("SWAP_GAME_VIEW", false);
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(SUPCUR_SWAP_GAME_VIEW, VALUE_SWAP_GAME_VIEW_TRUE);
            PROPERTY::setValue("SWAP_GAME_VIEW", true);
        }
    } else if (selected_index == ITEM_FIXED_GAME_VIEW_ASPECT) {
        if (pVB->isPushedDown(VB_UI_LEFT)) {
            selectItemBySupCursor(SUPCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_TRUE);
            PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", true);
            if (!P_WORLD->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewAspect(true);
            }
        } else if (pVB->isPushedDown(VB_UI_RIGHT)) {
            selectItemBySupCursor(SUPCUR_FIXED_GAME_VIEW_ASPECT, VALUE_FIXED_GAME_VIEW_FALSE);
            PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", false);
            if (!P_WORLD->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewAspect(false);
            }
        }
    } else if (selected_index == ITEM_SINGLE_VIEW_DRAW_POSITION) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION);
            if (i == VALUE_POS_9) {
                i = VALUE_POS_1;
            } else {
                i++;
            }
            selectItemBySupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION, i);
            PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", i+1 - VALUE_POS_1);
            if (!P_WORLD->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS_1);
            }
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            int i = getSelectedIndexOnSupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION);
            if (i == VALUE_POS_1) {
                i = VALUE_POS_9;
            } else {
                i--;
            }
            selectItemBySupCursor(SUPCUR_SINGLE_VIEW_DRAW_POSITION, i);
            PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", i+1 - VALUE_POS_1);
            if (!P_WORLD->need_reboot_) {
                GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS_1);
            }
        }
    } else if (selected_index == ITEM_DUAL_VIEW_DRAW_POSITION1) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1);
            if (i == VALUE_POS1_9) {
                i = VALUE_POS1_1;
            } else {
                i++;
            }
            selectItemBySupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS1_1);
            GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS1_1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            int i = getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1);
            if (i == VALUE_POS1_1) {
                i = VALUE_POS1_9;
            } else {
                i--;
            }
            selectItemBySupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION1, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS1_1);
            GgafDxCore::GgafDxGod::chengeViewPos1(i+1 - VALUE_POS1_1);
        }
    } else if (selected_index == ITEM_DUAL_VIEW_DRAW_POSITION2) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            int i = getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2);
            if (i == VALUE_POS2_9) {
                i = VALUE_POS2_1;
            } else {
                i++;
            }
            selectItemBySupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2, i);
            PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", i+1 - VALUE_POS2_1);
            GgafDxCore::GgafDxGod::chengeViewPos2(i+1 - VALUE_POS2_1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            int i = getSelectedIndexOnSupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2);
            if (i == VALUE_POS2_1) {
                i = VALUE_POS2_9;
            } else {
                i--;
            }
            selectItemBySupCursor(SUPCUR_DUAL_VIEW_DRAW_POSITION2, i);
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
                GgafDxGod::AdapterRezos* paAdapterRezos = P_GOD->_paAdapterRezos;
                StringBoardActor* pLabelRezo  = (StringBoardActor*) getItem(VALUE_SINGLE_VIEW_FULL_SCREEN_RESOLUTION);
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
                GgafDxGod::AdapterRezos* paAdapterRezos = P_GOD->_paAdapterRezos;
                StringBoardActor* pLabelRezo1  = (StringBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN1_RESOLUTION);
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
                GgafDxGod::AdapterRezos* paAdapterRezos = P_GOD->_paAdapterRezos;
                StringBoardActor* pLabelRezo2 = (StringBoardActor*) getItem(VALUE_DUAL_VIEW_FULL_SCREEN2_RESOLUTION);
                pLabelRezo2->update(paAdapterRezos[1].paRezoInfo[rezo2_index_].item_str.c_str());
                PROPERTY::setValue("DUAL_VIEW_FULL_SCREEN2_WIDTH" , paAdapterRezos[1].paRezoInfo[rezo2_index_].width);
                PROPERTY::setValue("DUAL_VIEW_FULL_SCREEN2_HEIGHT", paAdapterRezos[1].paRezoInfo[rezo2_index_].height);
            }
        } else {
            //1画面なので、設定出来ない。
            if (is_right || is_left) {
                getSeTx()->play(SE_WRONG);
            }
        }
    }
}

void MenuBoardScreenConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
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
    } else if (prm_item_index == ITEM_OK) { //保存のOK
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE確認メニュー起動
    } else if (prm_item_index == ITEM_OK_REBOOT) { //OKで再起動
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE確認メニュー起動
    } else {

    }
}

void MenuBoardScreenConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
