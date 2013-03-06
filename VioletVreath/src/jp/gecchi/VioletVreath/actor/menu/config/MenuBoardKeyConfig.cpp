#include "stdafx.h"
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
    char* apItemStr[] = {
          "MAIN SHOT KEY & BUTTON",
          "SUB SHOT  KEY & BUTTON",
          "TURBO     KEY & BUTTON",
          "CONTROLL  KEY & BUTTON",
          "MAGIC     KEY & BUTTON",
          "VAM       KEY & BUTTON",
          "PAUSE     KEY & BUTTON",
    };

    int item_index;
    for (item_index = ITEM_MAIN_SHOT; item_index <= ITEM_PAUSE; item_index++) {
        LabelFix16Font01* pLabel = NEW LabelFix16Font01("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+(item_index*20)));
    }

    LabelGecchi16Font* pLabel_OK = NEW LabelGecchi16Font("item_Ok");
    pLabel_OK->update("OK & SAVE", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350));
    ITEM_INDEX_OK_ = item_index;

    LabelGecchi16Font* pLabel_CANCEL = NEW LabelGecchi16Font("item_Cancel");
    pLabel_CANCEL->update("CANCEL", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350));
    ITEM_INDEX_CANCEL_ = item_index + 1;

    paVBProperties = NEW VBProperty[item_index+1];
    for (int i = ITEM_MAIN_SHOT; i <= ITEM_PAUSE; i++) {
        paVBProperties[i].pKey = NEW LabelFix16Font01("DISP_KEY");
        paVBProperties[i].pKey->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addDisp(paVBProperties[i].pKey, PX_C(600), PX_C(100+(i*20)));
        paVBProperties[i].pJoy = NEW LabelFix16Font01("DISP_JOY");
        paVBProperties[i].pJoy->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
        addDisp(paVBProperties[i].pJoy, PX_C(800), PX_C(100+(i*20)));
    }

    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("SELECT AND PUSH KEY, JOY BUTTON!!", ALIGN_CENTER, VALIGN_MIDDLE);
    addDisp(pLabel_Title, PX_C(300), PX_C(40));

    //メニューカーソルを設定
    CursorKeyConfigMenu* pCursor = NEW CursorKeyConfigMenu("CursorKeyConfigMenu");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setCursor(pCursor);

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加
}
bool MenuBoardKeyConfig::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardKeyConfig::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
void MenuBoardKeyConfig::onRise() {

    selectItem(ITEM_MAIN_SHOT); //カーソルの初期選択アイテムを設定
    //リセット
    paVBProperties[ITEM_MAIN_SHOT].pKey->update(PROPERTY::MY_KEY_SHOT1  .c_str());
    paVBProperties[ITEM_SUB_SHOT ].pKey->update(PROPERTY::MY_KEY_SHOT2  .c_str());
    paVBProperties[ITEM_TURBO    ].pKey->update(PROPERTY::MY_KEY_TURBO  .c_str());
    paVBProperties[ITEM_CONTROLL ].pKey->update(PROPERTY::MY_KEY_OPTION .c_str());
    paVBProperties[ITEM_MAGIC    ].pKey->update(PROPERTY::MY_KEY_POWERUP.c_str());
    paVBProperties[ITEM_VAM      ].pKey->update(PROPERTY::MY_KEY_VIEW   .c_str());
    paVBProperties[ITEM_PAUSE    ].pKey->update(PROPERTY::MY_KEY_PAUSE  .c_str());

    paVBProperties[ITEM_MAIN_SHOT].pJoy->update(PROPERTY::MY_JOY_SHOT1  .c_str());
    paVBProperties[ITEM_SUB_SHOT ].pJoy->update(PROPERTY::MY_JOY_SHOT2  .c_str());
    paVBProperties[ITEM_TURBO    ].pJoy->update(PROPERTY::MY_JOY_TURBO  .c_str());
    paVBProperties[ITEM_CONTROLL ].pJoy->update(PROPERTY::MY_JOY_OPTION .c_str());
    paVBProperties[ITEM_MAGIC    ].pJoy->update(PROPERTY::MY_JOY_POWERUP.c_str());
    paVBProperties[ITEM_VAM      ].pJoy->update(PROPERTY::MY_JOY_VIEW   .c_str());
    paVBProperties[ITEM_PAUSE    ].pJoy->update(PROPERTY::MY_JOY_PAUSE  .c_str());

    MenuBoard::onRise();
}
void MenuBoardKeyConfig::processBehavior() {
    MenuBoard::processBehavior();

    //サブメニュー判定
    MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
    if (pSubConfirm->isJustDecidedOk()) {
        //現プロパティをファイルに保存
        PROPERTY::setValue("MY_KEY_SHOT1"   , paVBProperties[ITEM_MAIN_SHOT].pKey->_draw_string);
        PROPERTY::setValue("MY_KEY_SHOT2"   , paVBProperties[ITEM_SUB_SHOT ].pKey->_draw_string);
        PROPERTY::setValue("MY_KEY_TURBO"   , paVBProperties[ITEM_TURBO    ].pKey->_draw_string);
        PROPERTY::setValue("MY_KEY_OPTION"  , paVBProperties[ITEM_CONTROLL ].pKey->_draw_string);
        PROPERTY::setValue("MY_KEY_POWERUP" , paVBProperties[ITEM_MAGIC    ].pKey->_draw_string);
        PROPERTY::setValue("MY_KEY_VIEW"    , paVBProperties[ITEM_VAM      ].pKey->_draw_string);
        PROPERTY::setValue("MY_KEY_PAUSE"   , paVBProperties[ITEM_PAUSE    ].pKey->_draw_string);

        PROPERTY::setValue("MY_JOY_SHOT1"   , paVBProperties[ITEM_MAIN_SHOT].pJoy->_draw_string);
        PROPERTY::setValue("MY_JOY_SHOT2"   , paVBProperties[ITEM_SUB_SHOT ].pJoy->_draw_string);
        PROPERTY::setValue("MY_JOY_TURBO"   , paVBProperties[ITEM_TURBO    ].pJoy->_draw_string);
        PROPERTY::setValue("MY_JOY_OPTION"  , paVBProperties[ITEM_CONTROLL ].pJoy->_draw_string);
        PROPERTY::setValue("MY_JOY_POWERUP" , paVBProperties[ITEM_MAGIC    ].pJoy->_draw_string);
        PROPERTY::setValue("MY_JOY_VIEW"    , paVBProperties[ITEM_VAM      ].pJoy->_draw_string);
        PROPERTY::setValue("MY_JOY_PAUSE"   , paVBProperties[ITEM_PAUSE    ].pJoy->_draw_string);
        PROPERTY::save(VV_CONFIG_FILE);
        PROPERTY::load(VV_CONFIG_FILE); //再反映
        //実行中アプリへも反映
        P_GOD->initVB();

        sinkSubMenu(); //確認メニュー閉じる
        sink();        //自身メニュー閉じる
    } else if (pSubConfirm->isJustDecidedCancel()) {
        sinkSubMenu();
    } else {

    }

    //キー入力、ボタン入力、反映
    int index = getSelectedIndex();
    if ( ITEM_MAIN_SHOT <= index && index <= ITEM_PAUSE ) {
        int DIK_pushed = GgafDxInput::getPushedDownKey();
        if (0x00 <= DIK_pushed && DIK_pushed <= 0xD1) {
            if (VirtualButton::_tagKeymap.UI_UP    == DIK_pushed ||
                VirtualButton::_tagKeymap.UI_DOWN  == DIK_pushed ||
                VirtualButton::_tagKeymap.UI_LEFT  == DIK_pushed ||
                VirtualButton::_tagKeymap.UI_RIGHT == DIK_pushed  )
            {
                //UIのメニュー移動は無視
            } else {
                paVBProperties[index].pKey->update(VirtualButton::_mapDik2Str[DIK_pushed].c_str());
                paVBProperties[index].pKey->effectFlush(10);
            }
        }

        int JOY_pushed = GgafDxInput::getPushedDownJoyRgbButton();
        if (0 <= JOY_pushed && JOY_pushed <= 12) {
            paVBProperties[index].pJoy->update(VirtualButton::_mapJoyBtn2Str[JOY_pushed].c_str());
            paVBProperties[index].pJoy->effectFlush(10);
        }
    }

}

void MenuBoardKeyConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        sink();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //確認メニュー起動
    } else {

    }
}
void MenuBoardKeyConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardKeyConfig::~MenuBoardKeyConfig() {
    DELETEARR_IMPOSSIBLE_NULL(paVBProperties);
}
