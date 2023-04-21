#include "MenuBoardConfig.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "MenuBoardKeyConfig.h"
#include "MenuBoardSoundConfig.h"
#include "MenuBoardScreenConfig.h"
#include "CursorConfig001.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardConfig::MenuBoardConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardConfig";
    setWidth(PX_C(13*32));
    setHeight(PX_C(11*32));

    //メニューアイテム（選択可）設定
    const char* apItemStr[] = {
          "KEY CONFIG",
          "SOUND CONFIG",
          "SCREEN CONFIG",
          "<- BACK"
    };
    for (int i = ITEM_KEY_CONFIG; i <= ITEM_BACK; i++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+((i%4)*30)));
    }
    //表示ラベル設定
    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("[CONFIG MENU]", ALIGN_CENTER, VALIGN_MIDDLE);
    addLabel(pLabel_title, PX_C(100), PX_C(40));
    //キャンセルアイテム設定
    relateAllItemToCancel(ITEM_BACK);

    //メニューカーソルを設定
    CursorConfig001* pCursor = NEW CursorConfig001("CursorConfig001");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    selectItem(ITEM_BACK); //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), +PX_C(100)); //トランジション（表示非表示時の挙動）

    addSubMenu(NEW MenuBoardKeyConfig("key_config"));       //0番
    addSubMenu(NEW MenuBoardSoundConfig("sound_config"));   //1番
    addSubMenu(NEW MenuBoardScreenConfig("screen_config")); //2番
}

void MenuBoardConfig::onActive() {
    _TRACE_(FUNC_NAME<<"!");
}

bool MenuBoardConfig::condSelectNext() {
    return VVB->isAutoRepeat(0, VV_VB_UI_DOWN);
}

bool MenuBoardConfig::condSelectPrev() {
    return VVB->isAutoRepeat(0, VV_VB_UI_UP);
}

void MenuBoardConfig::onRise() {
    selectItem(ITEM_KEY_CONFIG); //カーソルの初期選択アイテムを設定
    MenuBoard::onRise();
}

void MenuBoardConfig::onRiseDone() {
    _TRACE_(FUNC_NAME<<"!");
}

void MenuBoardConfig::processBehavior() {
    MenuBoard::processBehavior();
}

void MenuBoardConfig::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BACK) {
        sinkMe();
    } else if (prm_item_index == ITEM_KEY_CONFIG) {
        riseSubMenu(ITEM_KEY_CONFIG, PX_C(50), PX_C(10)); //key configメニュー起動
    } else if (prm_item_index == ITEM_SOUND_CONFIG) {
        riseSubMenu(ITEM_SOUND_CONFIG, PX_C(50), PX_C(10)); //sound configメニュー起動
    } else if (prm_item_index == ITEM_SCREEN_CONFIG) {
        riseSubMenu(ITEM_SCREEN_CONFIG, PX_C(50), PX_C(10)); //screen configメニュー起動
    }
}

void MenuBoardConfig::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}

void MenuBoardConfig::onSinkDone() {
    _TRACE_(FUNC_NAME<<"!");
}

MenuBoardConfig::~MenuBoardConfig() {
}
