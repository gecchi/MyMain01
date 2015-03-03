#include "MenuBoard.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoard::MenuBoard(const char* prm_name, const char* prm_model) :
        StringBoardMenu(prm_name, prm_model) {
    _class_name = "MenuBoard";
    slide_from_offset_x_ = 0;
    slide_from_offset_y_ = 0;
    target_x_ = _x;
    target_y_ = _y;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_ON_RISEN      , "WAVE_MENU_ON_RISEN");
    pSeTx->set(SE_MOVE_CURSOR   , "WAVE_MENU_MOVE_CURSOR");
    pSeTx->set(SE_DECIDED_OK    , "WAVE_MENU_DECIDED_OK");
    pSeTx->set(SE_DECIDED_CANCEL, "WAVE_MENU_DECIDED_CANCEL");
    pSeTx->set(SE_WRONG         , "WAVE_MENU_SE_WRONG");
}

void MenuBoard::setTransition(frame prm_menu_fade_frames,
                              coord prm_slide_from_offset_x, coord prm_slide_from_offset_y) {
    setFadeFrames(prm_menu_fade_frames);
    slide_from_offset_x_ = prm_slide_from_offset_x;
    slide_from_offset_y_ = prm_slide_from_offset_y;
}

bool MenuBoard::condDecision() {
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
        getSeTx()->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoard::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //「メニューアイテム：任意」で、VB_UI_CANCEL ボタンの場合は
        //そのアイテムを「キャンセル」した事とする。(当たり前だが)
        getSeTx()->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoard::condSelectNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}

bool MenuBoard::condSelectPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}

bool MenuBoard::condSelectExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}

bool MenuBoard::condSelectExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}

bool MenuBoard::condSelectCancel() {
    return isJustCancelled();
}

void MenuBoard::riseMe() {
    target_x_ = _x;
    target_y_ = _y;
    StringBoardMenu::riseMe();
}

void MenuBoard::rise(coord prm_target_x, coord prm_target_y) {
    target_x_ = prm_target_x;
    target_y_ = prm_target_y;
    StringBoardMenu::riseMe();
}

void MenuBoard::riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y) {
    StringBoardMenu::getSubMenu(prm_index)->position(prm_target_x, prm_target_y); //←によりvoid MenuBoard::riseMe() に来た時にターゲット設定される
    StringBoardMenu::riseSubMenu(prm_index);
}

void MenuBoard::moveCursor(bool prm_smooth) {
    StringBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //スムーズ移動trueすなわち、活動状態。
        getSeTx()->play(SE_MOVE_CURSOR);
    }
}

void MenuBoard::onMoveCursor(int prm_from, int prm_to) {
}

void MenuBoard::onSelect(int prm_from, int prm_to) {
}

void MenuBoard::initialize() {
    //インデックス作成
    _lstItems.indexedValue();
    _lstDispActors.indexedValue();
}

void MenuBoard::onRise() {
    //スライドイントランジション
    position(target_x_ + slide_from_offset_x_,
             target_y_ + slide_from_offset_y_);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvAngTwd(target_x_, target_y_);
    pKuroko->asstA()->slideMvByDt(UTIL::getDistance(_x, _y, target_x_, target_y_), _fade_frames,
                                  0.2, 0.3, 0, true);
    getSeTx()->play(SE_ON_RISEN);
}

void MenuBoard::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    if (pKuroko->asstA()->isJustFinishSlidingMv()) {
        //スライド終了時、目的の座標へ補正
        position(target_x_, target_y_);
    }
    pKuroko->behave();
    StringBoardMenu::processBehavior();
    //メニュー選択アイテム、表示アイテム、カーソルは、
    //ボード座標を基にしているため、自身の座標確定後に
    //上位 processBehavior() をコールしたほうが良い。
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSink() {
    //スライドアウトトランジション
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvAngTwd(target_x_ + slide_from_offset_x_,
                         target_y_ + slide_from_offset_y_);
    pKuroko->asstA()->slideMvByDt(
                           UTIL::getDistance(
                                  _x, _y,
                                  target_x_+slide_from_offset_x_,
                                  target_y_+slide_from_offset_y_
                           ),
                           _fade_frames,
                           0.2, 0.3, 0, true);
}

MenuBoard::~MenuBoard() {
}
