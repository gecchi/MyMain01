#include "MenuBoardKeyConfig.h"

#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "CursorConfig002.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardKeyConfig::MenuBoardKeyConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardKeyConfig";
    //メニューウィンドウ設定
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
            "-.........................................../");

    //メニューアイテム（選択可）設定
    const char* apItemStr[] = {
          "MOVE UP",
          "MOVE DOWN",
          "MOVE LEFT",
          "MOVE RIGHT",
          "MAIN SHOT BUTTON",
          "SUB SHOT BUTTON",
          "TURBO BUTTON",
          "CONTROLL BUTTON",
          "MAGIC BUTTON",
          "VAM BUTTON",
          "PAUSE BUTTON"
    };

    int item_index;
    for (item_index = ITEM_UP; item_index <= ITEM_PAUSE; item_index++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100), PX_C(100+(item_index*20)));
    }

    LabelMenuItemFont01* pLabel_OK = NEW LabelMenuItemFont01("item_Ok");
    pLabel_OK->update("OK & SAVE", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350));
    ITEM_INDEX_OK_ = item_index;

    LabelMenuItemFont01* pLabel_CANCEL = NEW LabelMenuItemFont01("item_Cancel");
    pLabel_CANCEL->update("CANCEL", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350));
    ITEM_INDEX_CANCEL_ = item_index + 1;

    paVBProperties = NEW VBProperty[item_index+1];
    for (int i = ITEM_UP; i <= ITEM_PAUSE; i++) {
        paVBProperties[i].pKey = NEW LabelFix16Font01("DISP_KEY");
        paVBProperties[i].pKey->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addDisp(paVBProperties[i].pKey, PX_C(600), PX_C(100+(i*20)));
        paVBProperties[i].pJoy = NEW LabelFix16Font01("DISP_JOY");
        paVBProperties[i].pJoy->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addDisp(paVBProperties[i].pJoy, PX_C(800), PX_C(100+(i*20)));
    }

    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("SELECT AND PUSH UI_EXCUTE, THEN, PUSH KEY/JOY ASSIGNMENT!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_title, PX_C(100), PX_C(40));

    //メニューカーソルを設定
    CursorConfig002* pCursor = NEW CursorConfig002("CursorConfig002");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加
    input_mode_ = 0;
    input_target_item_ = 0;
}
bool MenuBoardKeyConfig::condSelectNext() {
    if (input_mode_ == 0) {
        return VB->isAutoRepeat(VB_UI_DOWN);
    } else {
        return false;
    }
}
bool MenuBoardKeyConfig::condSelectPrev() {
    if (input_mode_ == 0) {
        return VB->isAutoRepeat(VB_UI_UP);
    } else {
        return false;
    }
}
void MenuBoardKeyConfig::onRise() {

    selectItem(ITEM_UP); //カーソルの初期選択アイテムを設定
    //リセット
    paVBProperties[ITEM_UP       ].pKey->update(PROPERTY::MY_KEY_UP     .c_str());
    paVBProperties[ITEM_DOWN     ].pKey->update(PROPERTY::MY_KEY_DOWN   .c_str());
    paVBProperties[ITEM_LEFT     ].pKey->update(PROPERTY::MY_KEY_LEFT   .c_str());
    paVBProperties[ITEM_RIGHT    ].pKey->update(PROPERTY::MY_KEY_RIGHT  .c_str());
    paVBProperties[ITEM_MAIN_SHOT].pKey->update(PROPERTY::MY_KEY_SHOT1  .c_str());
    paVBProperties[ITEM_SUB_SHOT ].pKey->update(PROPERTY::MY_KEY_SHOT2  .c_str());
    paVBProperties[ITEM_TURBO    ].pKey->update(PROPERTY::MY_KEY_TURBO  .c_str());
    paVBProperties[ITEM_CONTROLL ].pKey->update(PROPERTY::MY_KEY_OPTION .c_str());
    paVBProperties[ITEM_MAGIC    ].pKey->update(PROPERTY::MY_KEY_POWERUP.c_str());
    paVBProperties[ITEM_VAM      ].pKey->update(PROPERTY::MY_KEY_VIEW   .c_str());
    paVBProperties[ITEM_PAUSE    ].pKey->update(PROPERTY::MY_KEY_PAUSE  .c_str());

    paVBProperties[ITEM_UP       ].pJoy->update(PROPERTY::MY_JOY_UP     .c_str());
    paVBProperties[ITEM_DOWN     ].pJoy->update(PROPERTY::MY_JOY_DOWN   .c_str());
    paVBProperties[ITEM_LEFT     ].pJoy->update(PROPERTY::MY_JOY_LEFT   .c_str());
    paVBProperties[ITEM_RIGHT    ].pJoy->update(PROPERTY::MY_JOY_RIGHT  .c_str());
    paVBProperties[ITEM_MAIN_SHOT].pJoy->update(PROPERTY::MY_JOY_SHOT1  .c_str());
    paVBProperties[ITEM_SUB_SHOT ].pJoy->update(PROPERTY::MY_JOY_SHOT2  .c_str());
    paVBProperties[ITEM_TURBO    ].pJoy->update(PROPERTY::MY_JOY_TURBO  .c_str());
    paVBProperties[ITEM_CONTROLL ].pJoy->update(PROPERTY::MY_JOY_OPTION .c_str());
    paVBProperties[ITEM_MAGIC    ].pJoy->update(PROPERTY::MY_JOY_POWERUP.c_str());
    paVBProperties[ITEM_VAM      ].pJoy->update(PROPERTY::MY_JOY_VIEW   .c_str());
    paVBProperties[ITEM_PAUSE    ].pJoy->update(PROPERTY::MY_JOY_PAUSE  .c_str());

    MenuBoard::onRise();

    input_mode_ = 0;
    input_target_item_ = 0;
}
void MenuBoardKeyConfig::processBehavior() {
    if (getBehaveingFrame() % 60 == 0) {
        if (GgafDxInput::_pJoystickInputDevice == nullptr) {
            GgafDxInput::initJoyStick();
        }
    }
    MenuBoard::processBehavior();

    //サブメニュー判定
    MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
    if (pSubConfirm->isJustDecidedOk()) {
        //現プロパティをファイルに保存
        PROPERTY::setValue("MY_KEY_UP"      , paVBProperties[ITEM_UP       ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_DOWN"    , paVBProperties[ITEM_DOWN     ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_LEFT"    , paVBProperties[ITEM_LEFT     ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_RIGHT"   , paVBProperties[ITEM_RIGHT    ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_SHOT1"   , paVBProperties[ITEM_MAIN_SHOT].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_SHOT2"   , paVBProperties[ITEM_SUB_SHOT ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_TURBO"   , paVBProperties[ITEM_TURBO    ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_OPTION"  , paVBProperties[ITEM_CONTROLL ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_POWERUP" , paVBProperties[ITEM_MAGIC    ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_VIEW"    , paVBProperties[ITEM_VAM      ].pKey->getDrawString());
        PROPERTY::setValue("MY_KEY_PAUSE"   , paVBProperties[ITEM_PAUSE    ].pKey->getDrawString());

        PROPERTY::setValue("MY_JOY_UP"      , paVBProperties[ITEM_UP       ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_DOWN"    , paVBProperties[ITEM_DOWN     ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_LEFT"    , paVBProperties[ITEM_LEFT     ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_RIGHT"   , paVBProperties[ITEM_RIGHT    ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_SHOT1"   , paVBProperties[ITEM_MAIN_SHOT].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_SHOT2"   , paVBProperties[ITEM_SUB_SHOT ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_TURBO"   , paVBProperties[ITEM_TURBO    ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_OPTION"  , paVBProperties[ITEM_CONTROLL ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_POWERUP" , paVBProperties[ITEM_MAGIC    ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_VIEW"    , paVBProperties[ITEM_VAM      ].pJoy->getDrawString());
        PROPERTY::setValue("MY_JOY_PAUSE"   , paVBProperties[ITEM_PAUSE    ].pJoy->getDrawString());
        PROPERTY::save(VV_CONFIG_FILE);
        PROPERTY::load(VV_CONFIG_FILE); //再反映
        //実行中アプリへも反映
        P_GOD->initVB();

        sinkCurrentSubMenu(); //確認メニュー閉じる
        sinkMe();        //自身メニュー閉じる
    } else if (pSubConfirm->isJustDecidedCancel()) {
        sinkCurrentSubMenu();
    } else {

    }

    //input_mode_=2を無駄に経由させることで、現決定ボタンの割り当て時とonDecisionを同時に成立させるの防ぐ
    if (input_mode_ == 2) {
        input_mode_ = 0;
    }

    if (input_mode_ == 1) {
        int index = getSelectedIndex();
        if (VB_UI->isPushedDown(VB_UI_CANCEL)) {
            input_mode_ = 0;
            paVBProperties[index].pKey->_pAFader->transitionLinerToTop(5);
            paVBProperties[index].pJoy->_pAFader->transitionLinerToTop(5);
        } else {
            int DIK_pushed = GgafDxInput::getPushedDownKey();
            if (DIK_pushed != -1 && 0x00 <= DIK_pushed && DIK_pushed <= 0xD1) {
                paVBProperties[index].pKey->update(VirtualButton::_mapDik2Str[DIK_pushed].c_str());
                paVBProperties[index].pKey->_pAFader->beat(10, 5, 0, 5, 6.5);
                paVBProperties[index].pJoy->_pAFader->transitionLinerToTop(5);
                input_mode_ = 2;
            }

            int JOY_pushed = VirtualButton::getPushedDownVirtualJoyButton();
            if (JOY_pushed != -1) {
                 paVBProperties[index].pJoy->update(VirtualButton::_mapJoyBtn2Str[JOY_pushed].c_str());
                 paVBProperties[index].pJoy->_pAFader->beat(10, 5, 0, 5, 6.5);
                 paVBProperties[index].pKey->_pAFader->transitionLinerToTop(5);
                 input_mode_ = 2;
            }
        }

    }

}

void MenuBoardKeyConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        input_mode_ = 0;
        sinkMe();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        input_mode_ = 0;
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //確認メニュー起動
    } else if (input_mode_ == 0) {
        input_mode_ = 1;
        input_target_item_ = prm_item_index;
        paVBProperties[prm_item_index].pKey->_pAFader->beat(30, 15, 0, 15, -1);
        paVBProperties[prm_item_index].pJoy->_pAFader->beat(30, 15, 0, 15, -1);
    }
}
void MenuBoardKeyConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {

}

MenuBoardKeyConfig::~MenuBoardKeyConfig() {
    GGAF_DELETEARR(paVBProperties);
}
