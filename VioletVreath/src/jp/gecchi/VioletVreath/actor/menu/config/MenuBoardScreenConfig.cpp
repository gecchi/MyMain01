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
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "screen/MenuBoardResolutionSelect.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardScreenConfig::MenuBoardScreenConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01"),
        itm(ITEM_SCREEN_MODE, ITEM_BANPEI),
        cur(SUPCUR_SCREEN_MODE, SUPCUR_BANPEI) {
    _class_name = "MenuBoardScreenConfig";

    //[0]:フルスクリーン時、[1]:ウィンドウ時
    const char* apItemStr[2][ITEM_BANPEI] = {
        {
            "SCREEN MODE(*)",
            "SCREEN NUM(*)",
            "SCREEN RESOLUTION(*)",
            "SCREEN1 RESOLUTION(*)", "SCREEN2 RESOLUTION(*)",
            "SWAP SCREEN(*)",
            "GAME VIEW ASPECT TYPE(*)",
            "GAME VIEW POSITION(*)",
            "GAME VIEW POSITION1(*)", "GAME VIEW POSITION2(*)",

            "OK", "OK & REBOOT", "CANCEL",

            "FULL SCREEN", "WINDOW MODE",
            "SINGLE VIEW", "DUAL VIEW",
            "",
            ""           , "",
            "NO"         , "YES",
            "FIX"        , "STRETCH",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
        },
        {
            "SCREEN MODE(*)",
            "SCREEN NUM(*)",
            "WINDOW SIZE",
            "WINDOW1 SIZE", "WINDOW2 SIZE",
            "SWAP SCREEN(*)",
            "GAME VIEW ASPECT TYPE",
            "GAME VIEW POSITION",
            "GAME VIEW POSITION1", "GAME VIEW POSITION2",

            "OK", "OK & REBOOT", "CANCEL",

            "FULL SCREEN", "WINDOW MODE",
            "SINGLE VIEW", "DUAL VIEW",
            "",
            ""           , "",
            "NO"         , "YES",
            "FIX"        , "STRETCH",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
        }
    };


    if (PROPERTY::DUAL_VIEW) {
        itm.remove(ITEM_VIEW_POSITION);
        itm.remove(ITEM_SCREEN_RESOLUTION);
        itm.remove(ITEM_POS_1, ITEM_POS_9);
        cur.remove(SUPCUR_VIEW_POSITION);
    } else {
        itm.remove(ITEM_SCREEN1_RESOLUTION);
        itm.remove(ITEM_SCREEN2_RESOLUTION);
        itm.remove(ITEM_SWAP_GAME_VIEW);
        itm.remove(ITEM_VIEW_POSITION1);
        itm.remove(ITEM_VIEW_POSITION2);
        itm.remove(ITEM_POS1_1, ITEM_POS1_9);
        itm.remove(ITEM_POS2_1, ITEM_POS2_9);
        cur.remove(SUPCUR_SWAP_GAME_VIEW);
        cur.remove(SUPCUR_VIEW_POSITION1);
        cur.remove(SUPCUR_VIEW_POSITION2);
    }

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

    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("[SCREEN CONFIG]", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(300), PX_C(40));

    //設定項目アイテム(ITEM_SCREEN_MODE ～ ITEM_CANCEL)
    int fullsc = PROPERTY::FULL_SCREEN ? 0 : 1;
    for (int i = itm.n(ITEM_SCREEN_MODE); i <= itm.n(ITEM_CANCEL); i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(apItemStr[fullsc][itm.e(i)], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel);
    }
    relateAllItemToCancel(itm.n(ITEM_CANCEL)); //キャンセルアイテム設定
    coord x1 = PX_C(100);  //設定項目アイテムX座標
    coord y1 = PX_C(100);  //設定項目アイテムY座標
    coord x2 = PX_C(700);  //選択値アイテムX座標
    coord y2 = y1;         //選択値アイテムY座標
    coord lh = PX_C(32);
    positionItem(itm.n(ITEM_SCREEN_MODE)     , x1, y1);  y1 += lh;
    positionItem(itm.n(ITEM_VIEW_NUM)        , x1, y1);  y1 += lh;
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_SCREEN1_RESOLUTION)  , x1, y1);  y1 += lh;
        positionItem(itm.n(ITEM_SCREEN2_RESOLUTION)  , x1, y1);  y1 += lh;
    } else {
        positionItem(itm.n(ITEM_SCREEN_RESOLUTION)  , x1, y1);  y1 += lh;
    }
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_SWAP_GAME_VIEW)  , x1, y1);  y1 += lh;
    }
    positionItem(itm.n(ITEM_VIEW_ASPECT_TYPE), x1, y1);  y1 += lh;
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_VIEW_POSITION1)  , x1, y1);  y1 += lh;
        positionItem(itm.n(ITEM_VIEW_POSITION2)  , x1, y1);  y1 += lh;
    } else {
        positionItem(itm.n(ITEM_VIEW_POSITION)  , x1, y1);  y1 += lh;
    }
    positionItem(itm.n(ITEM_OK)        , PX_C(50) , y1);
    positionItem(itm.n(ITEM_OK_REBOOT) , PX_C(250), y1);
    positionItem(itm.n(ITEM_CANCEL)    , PX_C(450), y1);  y1 += lh;

    //設定項目の選択肢アイテム
    for (int i = itm.n(ITEM_SCREEN_MODE_FULL_SCREEN); i < itm.n(ITEM_BANPEI); i++) {
        std::string name = "item"+XTOS(i);
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01(name.c_str());
        pLabel->update(apItemStr[fullsc][itm.e(i)], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel);
    }

    positionItem(itm.n(ITEM_SCREEN_MODE_FULL_SCREEN) , x2, y2); positionItem(itm.n(ITEM_SCREEN_MODE_WINDOW_MODE) , x2+PX_C(200), y2); y2 += lh;
    positionItem(itm.n(ITEM_VIEW_NUM_SINGLE)         , x2, y2); positionItem(itm.n(ITEM_VIEW_NUM_DUAL)           , x2+PX_C(200), y2); y2 += lh;
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_SCREEN1_RESOLUTION_VALUE), x2, y2); positionItem(itm.n(ITEM_SCREEN2_RESOLUTION_VALUE), x2+PX_C(200), y2); y2 += lh;
    } else {
        positionItem(itm.n(ITEM_SCREEN_RESOLUTION_VALUE), x2, y2); y2 += lh;
    }
    if (PROPERTY::DUAL_VIEW) {
        positionItem(itm.n(ITEM_SWAP_GAME_VIEW_NO), x2, y2); positionItem(itm.n(ITEM_SWAP_GAME_VIEW_YES), x2+PX_C(200), y2); y2 += lh;
    }
    positionItem(itm.n(ITEM_VIEW_ASPECT_TYPE_FIX)    , x2, y2); positionItem(itm.n(ITEM_VIEW_ASPECT_TYPE_STRETCH), x2+PX_C(200), y2); y2 += lh;
    if (PROPERTY::DUAL_VIEW) {
        for (int i = 0; i < 9; i++) { positionItem(itm.n(ITEM_POS1_1) + i , x2+PX_C(i*20), y2); } y2 += lh;
        for (int i = 0; i < 9; i++) { positionItem(itm.n(ITEM_POS2_1) + i , x2+PX_C(i*20), y2); } y2 += lh;
    } else {
        for (int i = 0; i < 9; i++) { positionItem(itm.n(ITEM_POS_1) + i , x2+PX_C(i*20), y2); } y2 += lh;
    }

    //説明メッセージ
    pLabel_Msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_Msg_->update("(*) NEED REBOOT .\n"
                        "PRESS ^ OR V TO SELECT, AND <- OR -> TO SETTING VALUE.",
                        ALIGN_LEFT, VALIGN_MIDDLE);
    addDisp(pLabel_Msg_, PX_C(10), PX_C(500));

    //メインメニューカーソルを設定
    CursorConfig003* pCursor = NEW CursorConfig003("MainCursor");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    //設定値補助カーソル
    for (int i = cur.n(SUPCUR_SCREEN_MODE); i < cur.n(SUPCUR_BANPEI); i++) {
        CursorConfig003* pSupCur = NEW CursorConfig003("SupCur");
        pSupCur->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        addSupCursor(pSupCur);
    }

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
    addSubMenu(NEW MenuBoardConfirm("confirm")); //0番 Yes No 問い合わせメニューをサブメニューに追加
    addSubMenu(NEW MenuBoardResolutionSelect("ResolutionSelect"));
////////////////////////////////////////
    StringBoardActor* pSelectRezo = (StringBoardActor*)getItem(itm.n(ITEM_SCREEN_RESOLUTION));
    pSelectRezo->update("1000x1000");
//////////////////////////
    in_FULL_SCREEN_                = PROPERTY::FULL_SCREEN;
    in_DUAL_VIEW_                  = PROPERTY::DUAL_VIEW;
    in_SWAP_GAME_VIEW_             = PROPERTY::SWAP_GAME_VIEW;
    in_FIXED_GAME_VIEW_ASPECT_     = PROPERTY::FIXED_GAME_VIEW_ASPECT;
    in_DUAL_VIEW_DRAW_POSITION1_   = PROPERTY::DUAL_VIEW_DRAW_POSITION1;
    in_DUAL_VIEW_DRAW_POSITION2_   = PROPERTY::DUAL_VIEW_DRAW_POSITION2;
    in_SINGLE_VIEW_DRAW_POSITION_  = PROPERTY::SINGLE_VIEW_DRAW_POSITION;
}

bool MenuBoardScreenConfig::condSelectNext() {
    if (getSelectedIndex() == itm.n(ITEM_CANCEL)) { //CANCELから先へ進めなくする
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

    selectItem(itm.n(ITEM_SCREEN_MODE)); //補助カーソルの初期選択アイテムを設定
    if (PROPERTY::getBool("FULL_SCREEN")) {
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN_MODE), itm.n(ITEM_SCREEN_MODE_FULL_SCREEN));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN_MODE), itm.n(ITEM_SCREEN_MODE_WINDOW_MODE));
    }
    if (PROPERTY::getBool("DUAL_VIEW")) {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_NUM), itm.n(ITEM_VIEW_NUM_DUAL));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_NUM), itm.n(ITEM_VIEW_NUM_SINGLE));
    }

    if (PROPERTY::getBool("DUAL_VIEW")) {
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN1_RESOLUTION), itm.n(ITEM_SCREEN1_RESOLUTION_VALUE));
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN2_RESOLUTION), itm.n(ITEM_SCREEN2_RESOLUTION_VALUE));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_SCREEN_RESOLUTION), itm.n(ITEM_SCREEN_RESOLUTION_VALUE));
    }

    if (PROPERTY::DUAL_VIEW) {
        if (PROPERTY::getBool("SWAP_GAME_VIEW")) {
            selectItemBySupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW), itm.n(ITEM_SWAP_GAME_VIEW_YES));
        } else {
            selectItemBySupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW), itm.n(ITEM_SWAP_GAME_VIEW_NO));
        }
    }
    if (PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT")) {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_ASPECT), itm.n(ITEM_VIEW_ASPECT_TYPE_FIX));
    } else {
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_ASPECT), itm.n(ITEM_VIEW_ASPECT_TYPE_STRETCH));
    }
    if (PROPERTY::DUAL_VIEW) {
        int pos1 = PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION1");
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION1), itm.n(ITEM_POS1_1) + (pos1-1));
        int pos2 = PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION2");
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION2), itm.n(ITEM_POS2_1) + (pos2-1));
    } else {
        int pos = PROPERTY::getInt("SINGLE_VIEW_DRAW_POSITION");
        selectItemBySupCursor(cur.n(SUPCUR_VIEW_POSITION), itm.n(ITEM_POS_1) + (pos-1));
    }

    MenuBoard::onRise();
}

void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    //キー入力、ボタン入力、反映
    VirtualButton* pVB = VB;
    int selected_index = getSelectedIndex();

    //OK時の確認メニュー判定
    if (selected_index == itm.n(ITEM_OK) || selected_index == itm.n(ITEM_OK_REBOOT)) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) { //SAVE確認OK!
            //現プロパティへ書き込み
            if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_SCREEN_MODE)) == itm.n(ITEM_SCREEN_MODE_FULL_SCREEN)) {
                PROPERTY::setValue("FULL_SCREEN", true);
            } else {
                PROPERTY::setValue("FULL_SCREEN", false);
            }
            if (PROPERTY::FULL_SCREEN != PROPERTY::getBool("FULL_SCREEN")) {
                P_WORLD->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_NUM)) == itm.n(ITEM_VIEW_NUM_DUAL)) {
                PROPERTY::setValue("DUAL_VIEW", true);
            } else {
                PROPERTY::setValue("DUAL_VIEW", false);
            }
            if (PROPERTY::DUAL_VIEW != PROPERTY::getBool("DUAL_VIEW")) {
                P_WORLD->need_reboot_ = 1;
            }

            if (PROPERTY::DUAL_VIEW) {
                if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_SWAP_GAME_VIEW)) == itm.n(ITEM_SWAP_GAME_VIEW_NO)) {
                    PROPERTY::setValue("SWAP_GAME_VIEW", false);
                } else {
                    PROPERTY::setValue("SWAP_GAME_VIEW", true);
                }
            }
            if (PROPERTY::SWAP_GAME_VIEW != PROPERTY::getBool("SWAP_GAME_VIEW")) {
                P_WORLD->need_reboot_ = 1;
            }

            if (getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_ASPECT)) == itm.n(ITEM_VIEW_ASPECT_TYPE_FIX)) {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", true);
            } else {
                PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", false);
            }
            //_TRACE_("PROPERTY::FULL_SCREEN="<<PROPERTY::FULL_SCREEN<<" PROPERTY::FIXED_GAME_VIEW_ASPECT="<<PROPERTY::FIXED_GAME_VIEW_ASPECT<<" PROPERTY::getBool(\"FIXED_GAME_VIEW_ASPECT\")="<<PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT"));
            if (PROPERTY::FIXED_GAME_VIEW_ASPECT != PROPERTY::getBool("FIXED_GAME_VIEW_ASPECT")) {
                P_WORLD->need_reboot_ = 1;
            }


            if (PROPERTY::DUAL_VIEW) {
                int pos1 = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION1))+1 - itm.n(ITEM_POS1_1);
                PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", pos1);
                int pos2 = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION2))+1 - itm.n(ITEM_POS2_1);
                PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION2", pos2);
                if (PROPERTY::DUAL_VIEW_DRAW_POSITION1 != PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION1")) {
                    P_WORLD->need_reboot_ = 1;
                }
                if (PROPERTY::DUAL_VIEW_DRAW_POSITION2 != PROPERTY::getInt("DUAL_VIEW_DRAW_POSITION2")) {
                    P_WORLD->need_reboot_ = 1;
                }

            } else {
                int pos = getSelectedIndexOnSupCursor(cur.n(SUPCUR_VIEW_POSITION))+1 - itm.n(ITEM_POS_1);
                PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", pos);
                if (PROPERTY::SINGLE_VIEW_DRAW_POSITION != PROPERTY::getInt("SINGLE_VIEW_DRAW_POSITION")) {
                    P_WORLD->need_reboot_ = 1;
                }
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

            if (selected_index == itm.n(ITEM_OK_REBOOT)) { //さらにリブート
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
        //2画面時
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
        //１画面時
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
    } else if (prm_item_index == itm.n(ITEM_OK)) { //保存のOK
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE確認メニュー起動
    } else if (prm_item_index == itm.n(ITEM_OK_REBOOT)) { //OKで再起動
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //SAVE確認メニュー起動
    } else {

    }
}
void MenuBoardScreenConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
