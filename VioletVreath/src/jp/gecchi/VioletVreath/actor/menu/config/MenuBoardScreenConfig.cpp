#include "stdafx.h"
#include "MenuBoardScreenConfig.h"

#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "CursorScreenConfigMenu.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuSelectSub.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardScreenConfig::MenuBoardScreenConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardScreenConfig";
    //メニューウィンドウ設定
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

    //メニューアイテム（選択可）設定
    const char* apItemStr[] = {
          "SCREEN MODE",
          "SCREEN NUM",
          "GAME VIEW ASPECT TYPE",
          "GAME VIEW POSITION",
          "OK & SAVE",
          "CANCEL"

          "FULL SCREEN", "WINDOW MODE",
          "SINGLE VIEW", "DUAL VIEW",
          "FIX",         "STRETCH",
    };

    for (int i = ITEM_SCREEN_MODE; i <= ITEM_VIEW_ASPECT_TYPE_STRETCH; i++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[i], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel);
    }
    //キャンセルアイテム設定
    relateAllItemCancel(ITEM_CANCEL);

    locateItem(ITEM_SCREEN_MODE     , PX_C(100), PX_C(100));
    locateItem(ITEM_VIEW_NUM        , PX_C(100), PX_C(120));
    locateItem(ITEM_VIEW_ASPECT_TYPE, PX_C(100), PX_C(140));
    locateItem(ITEM_VIEW_POSITION   , PX_C(100), PX_C(160));

    locateItem(ITEM_OK              , PX_C(50), PX_C(200));
    locateItem(ITEM_CANCEL          , PX_C(150), PX_C(200));

    locateItem(ITEM_SCREEN_MODE_FULL_SCREEN , PX_C(200), PX_C(100));
    locateItem(ITEM_SCREEN_MODE_WINDOW_MODE , PX_C(300), PX_C(100));

    locateItem(ITEM_VIEW_NUM_SINGLE         , PX_C(200), PX_C(120));
    locateItem(ITEM_VIEW_NUM_DUAL           , PX_C(300), PX_C(120));

    locateItem(ITEM_VIEW_ASPECT_TYPE_FIX    , PX_C(200), PX_C(140));
    locateItem(ITEM_VIEW_ASPECT_TYPE_STRETCH, PX_C(300), PX_C(140));

    pLabel_Msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_Msg_->update("PRESS ^ or v TO SELECT, AND <- OR -> TO SETTING VALUE.", ALIGN_LEFT, VALIGN_MIDDLE);
    addDisp(pLabel_Msg_, PX_C(10), PX_C(300));


    //メインメニューカーソルを設定
    CursorScreenConfigMenu* pCursor = NEW CursorScreenConfigMenu("MainCursor");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加


    for (int i = SUPCUR_SCREEN_MODE; i <= SUPCUR_VIEW_ASPECT; i++) {
        CursorScreenConfigMenu* pSupCur = NEW CursorScreenConfigMenu("SupCur");
        pSupCur->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        addSupCursor(pSupCur);
    }
}
bool MenuBoardScreenConfig::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardScreenConfig::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
void MenuBoardScreenConfig::onRise() {
    selectItem(ITEM_SCREEN_MODE); //カーソルの初期選択アイテムを設定
    if (PROPERTY::FULL_SCREEN) {
        selectItemBySupCursor(SUPCUR_SCREEN_MODE, ITEM_SCREEN_MODE_FULL_SCREEN);
    } else {
        selectItemBySupCursor(SUPCUR_SCREEN_MODE, ITEM_SCREEN_MODE_WINDOW_MODE);
    }
    if (PROPERTY::DUAL_VIEW) {
        selectItemBySupCursor(SUPCUR_VIEW_NUM, ITEM_VIEW_NUM_DUAL);
    } else {
        selectItemBySupCursor(SUPCUR_VIEW_NUM, ITEM_VIEW_NUM_SINGLE);
    }
    if (PROPERTY::FIXED_GAME_VIEW_ASPECT) {
        selectItemBySupCursor(SUPCUR_VIEW_ASPECT, ITEM_VIEW_ASPECT_TYPE_FIX);
    } else {
        selectItemBySupCursor(SUPCUR_VIEW_ASPECT, ITEM_VIEW_ASPECT_TYPE_STRETCH);
    }
    MenuBoard::onRise();
}
void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    //OK時の確認メニュー判定
    if (getSelectedIndex() == ITEM_OK) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) { //確認OK!
            //現プロパティへ書き込み
            if (getSelectedIndexOnSupCursor(SUPCUR_SCREEN_MODE) == ITEM_SCREEN_MODE_FULL_SCREEN) {
                PROPERTY::FULL_SCREEN = true;
            } else {
                PROPERTY::FULL_SCREEN = false;
            }
            if (getSelectedIndexOnSupCursor(SUPCUR_VIEW_NUM) == ITEM_VIEW_NUM_DUAL) {
                PROPERTY::DUAL_VIEW = true;
            } else {
                PROPERTY::DUAL_VIEW = false;
            }
            if (getSelectedIndexOnSupCursor(SUPCUR_VIEW_ASPECT) == ITEM_VIEW_ASPECT_TYPE_FIX) {
                PROPERTY::FIXED_GAME_VIEW_ASPECT = true;
            } else {
                PROPERTY::FIXED_GAME_VIEW_ASPECT = false;
            }
            PROPERTY::save(VV_CONFIG_FILE); //プロパティ保存
            PROPERTY::load(VV_CONFIG_FILE); //プロパティ再反映
            //実行中アプリへも即時反映 TODO:

            sinkSubMenu();
            sink();
        } else if (pSubConfirm->isJustDecidedCancel()) { //確認でキャンセル
            sinkSubMenu();
        } else {

        }
    }

    //キー入力、ボタン入力、反映
    VirtualButton* pVB = VB;
    int index = getSelectedIndex();
    if (index == ITEM_SCREEN_MODE) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
//            GgafDxSound::addSeMasterVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
//            GgafDxSound::addSeMasterVolume(-1);
        }
//        pLabel_SeVol_->update(XTOS(GgafDxSound::_se_master_volume).c_str());
    } else if (index == ITEM_VIEW_NUM) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
//            GgafDxSound::addBgmMasterVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
//            GgafDxSound::addBgmMasterVolume(-1);
        }
//        pLabel_BgmVol_->update(XTOS(GgafDxSound::_bgm_master_volume).c_str());
    } else if (index == ITEM_VIEW_ASPECT_TYPE) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
//            GgafDxSound::addAppMasterVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
//            GgafDxSound::addAppMasterVolume(-1);
        }
//        pLabel_MasterVol_->update(XTOS(GgafDxSound::_app_master_volume).c_str());
    } else if (index == ITEM_VIEW_POSITION) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
//            GgafDxSound::addAppMasterVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
//            GgafDxSound::addAppMasterVolume(-1);
        }
//        pLabel_MasterVol_->update(XTOS(GgafDxSound::_app_master_volume).c_str());
    }
}

void MenuBoardScreenConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_CANCEL) {
        //音量を元に戻す
//        GgafDxSound::setSeMasterVolume(PROPERTY::SE_VOLUME);
//        GgafDxSound::setBgmMasterVolume(PROPERTY::BGM_VOLUME);
//        GgafDxSound::setAppMasterVolume(PROPERTY::MASTER_VOLUME);
        sink();
    } else if (prm_item_index == ITEM_OK) {
//        riseSubMenu(SUB_CONFIRM_, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //確認メニュー起動
    } else {

    }
}
void MenuBoardScreenConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
