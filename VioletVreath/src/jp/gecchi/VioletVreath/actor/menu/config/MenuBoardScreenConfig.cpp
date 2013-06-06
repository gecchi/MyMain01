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
    };

    for (int item_index = 0; item_index <= ITEM_VIEW_POSITION; item_index++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100), PX_C(100+(item_index*20)));
    }

    LabelGecchi16Font* pLabel_OK = NEW LabelGecchi16Font("item_Ok");
    pLabel_OK->update(apItemStr[ITEM_OK], ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350));

    LabelGecchi16Font* pLabel_CANCEL = NEW LabelGecchi16Font("item_Cancel");
    pLabel_CANCEL->update(apItemStr[ITEM_CANCEL], ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350));


    pLabel_Msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_Msg_->update("PRESS <- OR -> TO ADJUST THE VOLUME.", ALIGN_LEFT, VALIGN_MIDDLE);
    addDisp(pLabel_Msg_, PX_C(300), PX_C(60));


    //メニューカーソルを設定
    CursorScreenConfigMenu* pCursor = NEW CursorScreenConfigMenu("CursorScreenConfigMenu");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setCursor(pCursor);
    //キャンセルアイテム設定
    relateAllItemCancel(ITEM_CANCEL);

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる



    MenuSelectSub* pSelect_Sub01 = NEW MenuSelectSub("Select_Sub01", "board_bg01");
    LabelGecchi16Font* pLabel_Sub01_01 = NEW LabelGecchi16Font("Sub01_01");
    pLabel_Sub01_01->update("FULL SCREEN", ALIGN_LEFT, VALIGN_MIDDLE);
    pSelect_Sub01->addItem(pLabel_Sub01_01, PX_C(0), PX_C(0));
    LabelGecchi16Font* pLabel_Sub01_02 = NEW LabelGecchi16Font("Sub01_02");
    pLabel_Sub01_02->update("WINDOW MODE", ALIGN_LEFT, VALIGN_MIDDLE);
    pSelect_Sub01->addItem(pLabel_Sub01_02, PX_C(32*14), PX_C(0));

    MenuSelectSub* pSelect_Sub02 = NEW MenuSelectSub("Select_Sub02", "board_bg01");
    LabelGecchi16Font* pLabel_Sub02_01 = NEW LabelGecchi16Font("Sub02_01");
    pLabel_Sub02_01->update("SINGLE VIEW", ALIGN_LEFT, VALIGN_MIDDLE);
    pSelect_Sub02->addItem(pLabel_Sub02_01, PX_C(0), PX_C(0));
    LabelGecchi16Font* pLabel_Sub02_02 = NEW LabelGecchi16Font("Sub02_02");
    pLabel_Sub02_02->update("DUAL VIEW", ALIGN_LEFT, VALIGN_MIDDLE);
    pSelect_Sub02->addItem(pLabel_Sub02_02, PX_C(32*14), PX_C(0));

    MenuSelectSub* pSelect_Sub03 = NEW MenuSelectSub("Select_Sub03", "board_bg01");
    LabelGecchi16Font* pLabel_Sub03_01 = NEW LabelGecchi16Font("Sub03_01");
    pLabel_Sub03_01->update("FIX", ALIGN_LEFT, VALIGN_MIDDLE);
    pSelect_Sub03->addItem(pLabel_Sub03_01, PX_C(0), PX_C(0));
    LabelGecchi16Font* pLabel_Sub03_02 = NEW LabelGecchi16Font("Sub03_02");
    pLabel_Sub03_02->update("STRETCH", ALIGN_LEFT, VALIGN_MIDDLE);
    pSelect_Sub03->addItem(pLabel_Sub03_02, PX_C(32*14), PX_C(0));


    addSubMenu(pSelect_Sub01); SUB_SCREEN_MODE_ = 0;
    addSubMenu(pSelect_Sub02); SUB_VIEW_NUM_ = 1;
    addSubMenu(pSelect_Sub03); SUB_VIEW_ASPECT_TYPE_ = 2;

    riseSubMenu(SUB_SCREEN_MODE_     , PX_C(300), PX_C(100+(0*20)));
    riseSubMenu(SUB_VIEW_NUM_        , PX_C(300), PX_C(100+(1*20)));
    riseSubMenu(SUB_VIEW_ASPECT_TYPE_, PX_C(300), PX_C(100+(2*20)));

    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加
    SUB_CONFIRM_ = 3;


}
bool MenuBoardScreenConfig::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardScreenConfig::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
void MenuBoardScreenConfig::onRise() {
    selectItem(ITEM_SCREEN_MODE); //カーソルの初期選択アイテムを設定
//    pLabel_SeVol_->update(XTOS(GgafDxSound::_se_master_volume).c_str());
//    pLabel_BgmVol_->update(XTOS(GgafDxSound::_bgm_master_volume).c_str());
//    pLabel_MasterVol_->update(XTOS(GgafDxSound::_app_master_volume).c_str());
    MenuBoard::onRise();
}
void MenuBoardScreenConfig::processBehavior() {
    MenuBoard::processBehavior();

    //OK時の確認メニュー判定
    if (getSelectedIndex() == ITEM_OK) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->isJustDecidedOk()) { //確認OK!
            //現プロパティへ書き込み
//            PROPERTY::setValue("SE_VOLUME", GgafDxSound::_se_master_volume);
//            PROPERTY::setValue("BGM_VOLUME", GgafDxSound::_bgm_master_volume);
//            PROPERTY::setValue("MASTER_VOLUME", GgafDxSound::_app_master_volume);
            PROPERTY::save(VV_CONFIG_FILE); //プロパティ保存
            PROPERTY::load(VV_CONFIG_FILE); //プロパティ再反映
            //実行中アプリへも即時反映
//            GgafDxSound::setSeMasterVolume(PROPERTY::SE_VOLUME);
//            GgafDxSound::setBgmMasterVolume(PROPERTY::BGM_VOLUME);
//            GgafDxSound::setAppMasterVolume(PROPERTY::MASTER_VOLUME);

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
        riseSubMenu(SUB_CONFIRM_, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //確認メニュー起動
    } else {

    }
}
void MenuBoardScreenConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardScreenConfig::~MenuBoardScreenConfig() {
}
