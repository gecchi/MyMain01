#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MenuBoard::MenuBoard(const char* prm_name, const char* prm_model) :
        DefaultBoardSetMenu(prm_name, prm_model) {
    _class_name = "MenuBoard";
    _slide_from_offset_X = 0;
    _slide_from_offset_Y = 0;
    _target_X = _X;
    _target_Y = _Y;

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "click07_2"); //メーター移動
    _pSeTransmitter->set(1, "SwingA@11"); //レベルダウン実行
}

void MenuBoard::setTargetLocate(coord prm_target_X, coord prm_target_Y,
                                coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y) {
    _target_X = prm_target_X;
    _target_Y = prm_target_Y;
    _slide_from_offset_X = prm_slide_from_offset_X;
    _slide_from_offset_Y = prm_slide_from_offset_Y;
    locate(_target_X + _slide_from_offset_X,
           _target_Y + _slide_from_offset_Y);
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

bool MenuBoard::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != NULL &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        //キャンセルアイテム上でキャンセルボタンプッシュでもOK
        return true;
    } else {
        return false;
    }
}
void MenuBoard::moveCursor() {
    DefaultBoardSetMenu::moveCursor();
    _pSeTransmitter->playImmed(0);
}

void MenuBoard::initialize() {
}

void MenuBoard::onRisen() {
    //ロールダウントランジション
    locate(_target_X + _slide_from_offset_X,
           _target_Y + _slide_from_offset_Y);
    _pKurokoA->setMvAng(_target_X, _target_Y);
    _pKurokoA->execSmoothMvVeloSequence(
                    0,
                    GgafDxCore::GgafDxUtil::getDistance(
                        _X,
                        _Y,
                        _target_X,
                        _target_Y
                     ),
                     60, 0.2, 0.3
               );
}

void MenuBoard::processBehavior() {
    DefaultBoardSetMenu::processBehavior();
    if (_pKurokoA->isMoveingSmooth()) {
    } else {
        locate(_target_X, _target_Y);
    }
    _pKurokoA->behave();
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSunk() {
    //ロールアップトランジション
    _pKurokoA->setMvAng(_target_X + _slide_from_offset_X,
                        _target_Y + _slide_from_offset_Y);
    _pKurokoA->execSmoothMvVeloSequence(
                    0,
                    GgafDxCore::GgafDxUtil::getDistance(
                        _X,
                        _Y,
                        _target_X + _slide_from_offset_X,
                        _target_Y + _slide_from_offset_Y
                    ),
                    60, 0.2, 0.3
               );
}

MenuBoard::~MenuBoard() {
}
