#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoard::MenuBoard(const char* prm_name, const char* prm_model) :
        StringBoardMenu(prm_name, prm_model) {
    _class_name = "MenuBoard";
    menu_fade_frames_ = 0;
    slide_from_offset_X_ = 0;
    slide_from_offset_Y_ = 0;
    target_X_ = _X;
    target_Y_ = _Y;

    _pSeTxer->set(SE_MENU_OPEN     , "click07"); //メーター移動
    _pSeTxer->set(SE_MOVE_CURSOR   , "click07"); //メーター移動
    _pSeTxer->set(SE_DECIDED_NOMAL , "click07"); //メーター移動
    _pSeTxer->set(SE_DECIDED_CANCEL, "click07"); //メーター移動
    _pSeTxer->set(SE_MENU_CLOSE    , "click07"); //メーター移動
}

void MenuBoard::setTransition(frame prm_menu_fade_frames,
                              coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y) {
    setFadeFrames(prm_menu_fade_frames);
    menu_fade_frames_ = prm_menu_fade_frames;
    slide_from_offset_X_ = prm_slide_from_offset_X;
    slide_from_offset_Y_ = prm_slide_from_offset_Y;
}

bool MenuBoard::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoard::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoard::condMoveCursorExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoard::condMoveCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoard::condMoveCursorCancel() {
    return isJustCancelled();
}

void MenuBoard::rise() {
    target_X_ = _X;
    target_Y_ = _Y;
    StringBoardMenu::rise();
}

void MenuBoard::rise(coord prm_target_X, coord prm_target_Y) {
    target_X_ = prm_target_X;
    target_Y_ = prm_target_Y;
    StringBoardMenu::rise();
}

void MenuBoard::riseSub(MenuBoard* prm_pSubMenu,
                        coord prm_target_X, coord prm_target_Y) {
    prm_pSubMenu->locate(prm_target_X, prm_target_Y); //←によりvoid MenuBoard::rise() に来た時にターゲット設定される
    StringBoardMenu::riseSub(prm_pSubMenu);
}

bool MenuBoard::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        //「メニューアイテム：任意」で、VB_UI_EXECUTE ボタンの場合は
        //そのアイテムを「決定」した事とする。(当たり前だが)
        _pSeTxer->play(SE_DECIDED_NOMAL);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != NULL &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        //特別に「メニューアイテム：キャンセル」にカーソルがある場合でかつ、VB_UI_CANCEL ボタンの場合は、
        //「メニューアイテム：キャンセル」を「決定」したことにする。
        //現カーソルが「メニューアイテム：キャンセル」にあるかどうかの定義は、
        //relationItemCancel() で定義されたアイテムのインデックスかどうかで判断。
        _pSeTxer->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoard::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //「メニューアイテム：任意」で、VB_UI_CANCEL ボタンの場合は
        //そのアイテムを「キャンセル」した事とする。(当たり前だが)
        _pSeTxer->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

void MenuBoard::moveCursor() {
    StringBoardMenu::moveCursor();
    _pSeTxer->play(SE_MOVE_CURSOR);
}

void MenuBoard::initialize() {
}

void MenuBoard::onRisen() {
    //スライドイントランジション
    locate(target_X_ + slide_from_offset_X_,
           target_Y_ + slide_from_offset_Y_);
    _pKurokoA->setMvAng(target_X_, target_Y_);
    _pKurokoA->execSmoothMvSequence(
                    0,
                    UTIL::getDistance(
                        _X,
                        _Y,
                        target_X_,
                        target_Y_
                    ),
                    menu_fade_frames_, 0.1, 0.3
               );
    _pSeTxer->play(SE_MENU_OPEN);
}

void MenuBoard::processBehavior() {
    if (_pKurokoA->isRunnigSmoothMvSequence()) {
        //スライド中
    } else {
        //スライド終了時、目的の座標へ補正
        locate(target_X_, target_Y_);
    }
    _pKurokoA->behave();
    StringBoardMenu::processBehavior();
    //メニュー選択アイテム、表示アイテム、カーソルは、
    //ボード座標を基にしているため、自身の座標確定後に
    //上位 processBehavior() をコールしたほうが良い。
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSunk() {
    //スライドアウトトランジション
    _pKurokoA->setMvAng(target_X_ + slide_from_offset_X_,
                        target_Y_ + slide_from_offset_Y_);
    _pKurokoA->execSmoothMvSequence(
                    0,
                    UTIL::getDistance(
                        _X,
                        _Y,
                        target_X_ + slide_from_offset_X_,
                        target_Y_ + slide_from_offset_Y_
                    ),
                    60, 0.2, 0.3
               );
    _pSeTxer->play(SE_MENU_CLOSE);
}

MenuBoard::~MenuBoard() {
}
