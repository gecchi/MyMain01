#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoard::MenuBoard(const char* prm_name, const char* prm_model) :
        DefaultBoardMenu(prm_name, prm_model) {
    _class_name = "MenuBoard";
    menu_fade_frames_ = 0;
    slide_from_offset_X_ = 0;
    slide_from_offset_Y_ = 0;
    target_X_ = _X;
    target_Y_ = _Y;

    _pSeTransmitter->useSe(SE_MENU_CLOSE + 1);
    _pSeTransmitter->set(SE_MENU_OPEN     , "click07"); //メーター移動
    _pSeTransmitter->set(SE_MOVE_CURSOR   , "click07"); //メーター移動
    _pSeTransmitter->set(SE_DECIDED_NOMAL , "click07"); //メーター移動
    _pSeTransmitter->set(SE_DECIDED_CANCEL, "click07"); //メーター移動
    _pSeTransmitter->set(SE_MENU_CLOSE    , "click07"); //メーター移動
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
    return VB->isPushedDown(VB_UI_CANCEL);
}

void MenuBoard::rise() {
    target_X_ = _X;
    target_Y_ = _Y;
    DefaultBoardMenu::rise();
}

void MenuBoard::rise(coord prm_target_X, coord prm_target_Y) {
    target_X_ = prm_target_X;
    target_Y_ = prm_target_Y;
    DefaultBoardMenu::rise();
}

void MenuBoard::riseSub(MenuBoard* prm_pSubMenu,
                        coord prm_target_X, coord prm_target_Y) {
    prm_pSubMenu->locate(prm_target_X, prm_target_Y); //←によりvoid MenuBoard::rise() に来た時にターゲット設定される
    DefaultBoardMenu::riseSub(prm_pSubMenu);
}

bool MenuBoard::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        _pSeTransmitter->playImmed(SE_DECIDED_NOMAL);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != NULL &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        _pSeTransmitter->playImmed(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}
void MenuBoard::moveCursor() {
    DefaultBoardMenu::moveCursor();
    _pSeTransmitter->playImmed(SE_MOVE_CURSOR);
}

void MenuBoard::initialize() {
}

void MenuBoard::onRisen() {
    //スライドイントランジション
    locate(target_X_ + slide_from_offset_X_,
           target_Y_ + slide_from_offset_Y_);
    _pKurokoA->setMvAng(target_X_, target_Y_);
    _pKurokoA->execSmoothMvVeloSequence(
                    0,
                    GgafDxCore::GgafDxUtil::getDistance(
                        _X,
                        _Y,
                        target_X_,
                        target_Y_
                     ),
                     menu_fade_frames_, 0.1, 0.3
               );
    _pSeTransmitter->playImmed(SE_MENU_OPEN);
}

void MenuBoard::processBehavior() {
    DefaultBoardMenu::processBehavior();
    if (_pKurokoA->isMoveingSmooth()) {
        //スライド中
    } else {
        //スライド終了時、目的の座標へ補正
        locate(target_X_, target_Y_);
    }
    _pKurokoA->behave();
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSunk() {
    //スライドアウトトランジション
    _pKurokoA->setMvAng(target_X_ + slide_from_offset_X_,
                        target_Y_ + slide_from_offset_Y_);
    _pKurokoA->execSmoothMvVeloSequence(
                    0,
                    GgafDxCore::GgafDxUtil::getDistance(
                        _X,
                        _Y,
                        target_X_ + slide_from_offset_X_,
                        target_Y_ + slide_from_offset_Y_
                    ),
                    60, 0.2, 0.3
               );
    _pSeTransmitter->playImmed(SE_MENU_CLOSE);
}

MenuBoard::~MenuBoard() {
}
