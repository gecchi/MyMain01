#include "MenuBoardKeyConfig.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "CursorConfig002.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardKeyConfig::MenuBoardKeyConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardKeyConfig";
    setWidth(PX_C(45*32));
    setHeight(PX_C(15*32));
    //メニューアイテム（選択可）設定
    const char* apItemStr[] = {
          "MOVE UP",
          "MOVE DOWN",
          "MOVE LEFT",
          "MOVE RIGHT",
          "VIEW UP",
          "VIEW DOWN",
          "VIEW LEFT",
          "VIEW RIGHT",
          "MAIN SHOT BUTTON",
          "SUB SHOT BUTTON",
          "TURBO BUTTON",
          "CONTROLL BUTTON",
          "MAGIC BUTTON",
          "VIEW BUTTON",
          "PAUSE BUTTON"
    };

    int item_index;
    for (item_index = ITEM_UP; item_index < ITEM_BANPEI; item_index++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(100), PX_C(100+(item_index*18)));
    }

    LabelMenuItemFont01* pLabel_OK = NEW LabelMenuItemFont01("item_Ok");
    pLabel_OK->update("OK & SAVE", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(380));
    ITEM_INDEX_OK_ = item_index;

    LabelMenuItemFont01* pLabel_CANCEL = NEW LabelMenuItemFont01("item_Cancel");
    pLabel_CANCEL->update("CANCEL", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(380));
    ITEM_INDEX_CANCEL_ = item_index + 1;

    paVBConfig = NEW VBProperty[item_index+1];
    for (int i = ITEM_UP; i < ITEM_BANPEI; i++) {
        paVBConfig[i].pKey = NEW LabelFix16Font01("DISP_KEY");
        paVBConfig[i].pKey->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addLabel(paVBConfig[i].pKey, PX_C(600), PX_C(100+(i*18)));
        paVBConfig[i].pJoy = NEW LabelFix16Font01("DISP_JOY");
        paVBConfig[i].pJoy->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addLabel(paVBConfig[i].pJoy, PX_C(800), PX_C(100+(i*18)));
    }

    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("SELECT AND PUSH UI_EXCUTE, THEN, PUSH KEY/JOY ASSIGNMENT!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addLabel(pLabel_title, PX_C(100), PX_C(40));

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
        return VVB->isAutoRepeat(0, VVB_UI_DOWN);
    } else {
        return false;
    }
}
bool MenuBoardKeyConfig::condSelectPrev() {
    if (input_mode_ == 0) {
        return VVB->isAutoRepeat(0, VVB_UI_UP);
    } else {
        return false;
    }
}
void MenuBoardKeyConfig::onRise() {

    selectItem(ITEM_UP); //カーソルの初期選択アイテムを設定
    //リセット
    paVBConfig[ITEM_UP        ].pKey->update(CONFIG::VV_KEY_UP        .c_str());
    paVBConfig[ITEM_DOWN      ].pKey->update(CONFIG::VV_KEY_DOWN      .c_str());
    paVBConfig[ITEM_LEFT      ].pKey->update(CONFIG::VV_KEY_LEFT      .c_str());
    paVBConfig[ITEM_RIGHT     ].pKey->update(CONFIG::VV_KEY_RIGHT     .c_str());
    paVBConfig[ITEM_VIEW_UP   ].pKey->update(CONFIG::VV_KEY_VIEW_UP   .c_str());
    paVBConfig[ITEM_VIEW_DOWN ].pKey->update(CONFIG::VV_KEY_VIEW_DOWN .c_str());
    paVBConfig[ITEM_VIEW_LEFT ].pKey->update(CONFIG::VV_KEY_VIEW_LEFT .c_str());
    paVBConfig[ITEM_VIEW_RIGHT].pKey->update(CONFIG::VV_KEY_VIEW_RIGHT.c_str());
    paVBConfig[ITEM_MAIN_SHOT ].pKey->update(CONFIG::VV_KEY_SHOT1     .c_str());
    paVBConfig[ITEM_SUB_SHOT  ].pKey->update(CONFIG::VV_KEY_SHOT2     .c_str());
    paVBConfig[ITEM_TURBO     ].pKey->update(CONFIG::VV_KEY_TURBO     .c_str());
    paVBConfig[ITEM_CONTROLL  ].pKey->update(CONFIG::VV_KEY_OPTION    .c_str());
    paVBConfig[ITEM_MAGIC     ].pKey->update(CONFIG::VV_KEY_POWERUP   .c_str());
    paVBConfig[ITEM_VIEW      ].pKey->update(CONFIG::VV_KEY_VIEW      .c_str());
    paVBConfig[ITEM_PAUSE     ].pKey->update(CONFIG::VV_KEY_PAUSE     .c_str());

    paVBConfig[ITEM_UP        ].pJoy->update(CONFIG::VV_JOY_UP        .c_str());
    paVBConfig[ITEM_DOWN      ].pJoy->update(CONFIG::VV_JOY_DOWN      .c_str());
    paVBConfig[ITEM_LEFT      ].pJoy->update(CONFIG::VV_JOY_LEFT      .c_str());
    paVBConfig[ITEM_RIGHT     ].pJoy->update(CONFIG::VV_JOY_RIGHT     .c_str());
    paVBConfig[ITEM_VIEW_UP   ].pJoy->update(CONFIG::VV_JOY_VIEW_UP   .c_str());
    paVBConfig[ITEM_VIEW_DOWN ].pJoy->update(CONFIG::VV_JOY_VIEW_DOWN .c_str());
    paVBConfig[ITEM_VIEW_LEFT ].pJoy->update(CONFIG::VV_JOY_VIEW_LEFT .c_str());
    paVBConfig[ITEM_VIEW_RIGHT].pJoy->update(CONFIG::VV_JOY_VIEW_RIGHT.c_str());
    paVBConfig[ITEM_MAIN_SHOT ].pJoy->update(CONFIG::VV_JOY_SHOT1     .c_str());
    paVBConfig[ITEM_SUB_SHOT  ].pJoy->update(CONFIG::VV_JOY_SHOT2     .c_str());
    paVBConfig[ITEM_TURBO     ].pJoy->update(CONFIG::VV_JOY_TURBO     .c_str());
    paVBConfig[ITEM_CONTROLL  ].pJoy->update(CONFIG::VV_JOY_OPTION    .c_str());
    paVBConfig[ITEM_MAGIC     ].pJoy->update(CONFIG::VV_JOY_POWERUP   .c_str());
    paVBConfig[ITEM_VIEW      ].pJoy->update(CONFIG::VV_JOY_VIEW      .c_str());
    paVBConfig[ITEM_PAUSE     ].pJoy->update(CONFIG::VV_JOY_PAUSE     .c_str());

    MenuBoard::onRise();

    input_mode_ = 0;
    input_target_item_ = 0;
}
void MenuBoardKeyConfig::processBehavior() {
//    if (getBehaveingFrame() % 60 == 0) {
//        if (GgafDx::Input::_apJoystickInputDevice[P1_JOY_STICK] == nullptr) {
//            GgafDx::Input::initJoyStick();
//        }
//    }
    MenuBoard::processBehavior();

    //サブメニュー判定
    MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu();
    if (pSubConfirm->hasJustDecidedOk()) {
        //現プロパティをファイルに保存
        CONFIG::_properties.setValue("VV_KEY_UP"        , paVBConfig[ITEM_UP        ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_DOWN"      , paVBConfig[ITEM_DOWN      ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_LEFT"      , paVBConfig[ITEM_LEFT      ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_RIGHT"     , paVBConfig[ITEM_RIGHT     ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_VIEW_UP"   , paVBConfig[ITEM_VIEW_UP   ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_VIEW_DOWN" , paVBConfig[ITEM_VIEW_DOWN ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_VIEW_LEFT" , paVBConfig[ITEM_VIEW_LEFT ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_VIEW_RIGHT", paVBConfig[ITEM_VIEW_RIGHT].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_SHOT1"     , paVBConfig[ITEM_MAIN_SHOT ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_SHOT2"     , paVBConfig[ITEM_SUB_SHOT  ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_TURBO"     , paVBConfig[ITEM_TURBO     ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_OPTION"    , paVBConfig[ITEM_CONTROLL  ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_POWERUP"   , paVBConfig[ITEM_MAGIC     ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_VIEW"      , paVBConfig[ITEM_VIEW      ].pKey->getDrawString());
        CONFIG::_properties.setValue("VV_KEY_PAUSE"     , paVBConfig[ITEM_PAUSE     ].pKey->getDrawString());

        CONFIG::_properties.setValue("VV_JOY_UP"        , paVBConfig[ITEM_UP        ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_DOWN"      , paVBConfig[ITEM_DOWN      ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_LEFT"      , paVBConfig[ITEM_LEFT      ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_RIGHT"     , paVBConfig[ITEM_RIGHT     ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_VIEW_UP"   , paVBConfig[ITEM_VIEW_UP   ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_VIEW_DOWN" , paVBConfig[ITEM_VIEW_DOWN ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_VIEW_LEFT" , paVBConfig[ITEM_VIEW_LEFT ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_VIEW_RIGHT", paVBConfig[ITEM_VIEW_RIGHT].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_SHOT1"     , paVBConfig[ITEM_MAIN_SHOT ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_SHOT2"     , paVBConfig[ITEM_SUB_SHOT  ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_TURBO"     , paVBConfig[ITEM_TURBO     ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_OPTION"    , paVBConfig[ITEM_CONTROLL  ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_POWERUP"   , paVBConfig[ITEM_MAGIC     ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_VIEW"      , paVBConfig[ITEM_VIEW       ].pJoy->getDrawString());
        CONFIG::_properties.setValue("VV_JOY_PAUSE"     , paVBConfig[ITEM_PAUSE     ].pJoy->getDrawString());
        CONFIG::_properties.write(CONFIG::_load_properties_filename);
        CONFIG::loadProperties(CONFIG::_load_properties_filename); //再反映
        //実行中アプリへも反映
        pCARETAKER->initVB();

        sinkCurrentSubMenu(); //確認メニュー閉じる
        sinkMe();        //自身メニュー閉じる
    } else if (pSubConfirm->hasJustDecidedCancel()) {
        sinkCurrentSubMenu();
    } else {

    }

    //input_mode_=2を無駄に経由させることで、現決定ボタンの割り当て時とonDecisionを同時に成立させるの防ぐ
    if (input_mode_ == 2) {
        input_mode_ = 0;
    }

    if (input_mode_ == 1) {
        int index = getSelectedIndex();
        //キャンセルJOYボタンを割り当てるためコメント
//        if (VVB_UI->isPushedDown(0, VVB_UI_CANCEL)) {
//            input_mode_ = 0;
//            paVBConfig[index].pKey->getAlphaFader()->transitionLinearToTop(5);
//            paVBConfig[index].pJoy->getAlphaFader()->transitionLinearToTop(5);
//        } else {
            int DIK_pushed = GgafDx::Input::getFirstPushedDownKey();
            if (DIK_pushed != -1 && 0x00 <= DIK_pushed && DIK_pushed <= 0xD1) {
                paVBConfig[index].pKey->update(VirtualButton::_mapVBK2Str[DIK_pushed].c_str());
                paVBConfig[index].pKey->getAlphaFader()->beat(10, 5, 0, 5, 6.5);
                paVBConfig[index].pJoy->getAlphaFader()->transitionLinearToTop(5);
                input_mode_ = 2;
            }

            vbj VBJ_pushed = VirtualButton::getFirstPushedDownVirtualJoyButton(0);
            if (VBJ_pushed != -1) {
                 paVBConfig[index].pJoy->update(VirtualButton::_mapVBJ2Str[VBJ_pushed].c_str());
                 paVBConfig[index].pJoy->getAlphaFader()->beat(10, 5, 0, 5, 6.5);
                 paVBConfig[index].pKey->getAlphaFader()->transitionLinearToTop(5);
                 input_mode_ = 2;
            }
//        }
    }

}

void MenuBoardKeyConfig::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        input_mode_ = 0;
        sinkMe();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        input_mode_ = 0;
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //確認メニュー起動
    } else if (input_mode_ == 0) {
        input_mode_ = 1;
        input_target_item_ = prm_item_index;
        paVBConfig[prm_item_index].pKey->getAlphaFader()->beat(40, 15, 5, 15, -1);
        paVBConfig[prm_item_index].pJoy->getAlphaFader()->beat(40, 15, 5, 15, -1);
    }
}
void MenuBoardKeyConfig::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {

}

MenuBoardKeyConfig::~MenuBoardKeyConfig() {
    GGAF_DELETEARR(paVBConfig);
}
