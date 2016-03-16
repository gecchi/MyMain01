#include "MenuSelectSub.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuSelectSub::MenuSelectSub(const char* prm_name, const char* prm_model) :
        FixFontBoardMenu(prm_name, prm_model) {
    _class_name = "MenuSelectSub";
    target_x_ = _x;
    target_y_ = _y;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_MOVE_CURSOR   , "WAVE_MENU_MOVE_CURSOR"   );
    setFadeFrames(0);
    activateImmed(); //選択メニューなので、初期状態は活動状態をデフォルトとする
}

bool MenuSelectSub::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        //「メニューアイテム：任意」で、VB_UI_EXECUTE ボタンの場合は
        //そのアイテムを「決定」した事とする。(当たり前だが)
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != nullptr &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        //特別に「メニューアイテム：キャンセル」にカーソルがある場合でかつ、VB_UI_CANCEL ボタンの場合は、
        //「メニューアイテム：キャンセル」を「決定」したことにする。
        //現カーソルが「メニューアイテム：キャンセル」にあるかどうかの判断は、
        //relateAllItemToCancel() で定義されたアイテムのインデックスかどうかで判断。
        return true;
    } else {
        return false;
    }
}
bool MenuSelectSub::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //「メニューアイテム：任意」で、VB_UI_CANCEL ボタンの場合は
        //そのアイテムを「キャンセル」した事とする。(当たり前だが)
        return true;
    } else {
        return false;
    }
}
bool MenuSelectSub::condSelectNext() {
    return false;
}
bool MenuSelectSub::condSelectPrev() {
    return false;
}
bool MenuSelectSub::condSelectExNext() {
    return false;
}
bool MenuSelectSub::condSelectExPrev() {
    return false;
}
bool MenuSelectSub::condSelectCancel() {
    return hasJustCancelled();
}

void MenuSelectSub::riseMe() {
    target_x_ = _x;
    target_y_ = _y;
    FixFontBoardMenu::riseMe();
}

void MenuSelectSub::rise(coord prm_target_x, coord prm_target_y) {
    target_x_ = prm_target_x;
    target_y_ = prm_target_y;
    FixFontBoardMenu::riseMe();
}

void MenuSelectSub::riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y) {
    FixFontBoardMenu::getSubMenu(prm_index)->position(prm_target_x, prm_target_y); //←によりvoid MenuSelectSub::riseMe() に来た時にターゲット設定される
    FixFontBoardMenu::riseSubMenu(prm_index);
}

void MenuSelectSub::moveCursor(bool prm_smooth) {
    FixFontBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //スムーズ移動trueすなわち、活動状態。
        getSeTx()->play(SE_MOVE_CURSOR);
    }
}

void MenuSelectSub::onMoveCursor(int prm_from, int prm_to) {
}


void MenuSelectSub::onSelect(int prm_from, int prm_to) {
}

void MenuSelectSub::initialize() {
}

void MenuSelectSub::onRise() {
}

void MenuSelectSub::processBehavior() {
    position(target_x_, target_y_);
    getKuroko()->behave();
    FixFontBoardMenu::processBehavior();
    //メニュー選択アイテム、表示アイテム、カーソルは、
    //ボード座標を基にしているため、自身の座標確定後に
    //上位 processBehavior() をコールしたほうが良い。
}

void MenuSelectSub::processJudgement() {
}

void MenuSelectSub::onSink() {
}

MenuSelectSub::~MenuSelectSub() {
}
