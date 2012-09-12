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

    _pSeTxer->set(SE_MENU_OPEN     , "click07"); //���[�^�[�ړ�
    _pSeTxer->set(SE_MOVE_CURSOR   , "click07"); //���[�^�[�ړ�
    _pSeTxer->set(SE_DECIDED_NOMAL , "click07"); //���[�^�[�ړ�
    _pSeTxer->set(SE_DECIDED_CANCEL, "click07"); //���[�^�[�ړ�
    _pSeTxer->set(SE_MENU_CLOSE    , "click07"); //���[�^�[�ړ�
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
    StringBoardMenu::rise();
}

void MenuBoard::rise(coord prm_target_X, coord prm_target_Y) {
    target_X_ = prm_target_X;
    target_Y_ = prm_target_Y;
    StringBoardMenu::rise();
}

void MenuBoard::riseSub(MenuBoard* prm_pSubMenu,
                        coord prm_target_X, coord prm_target_Y) {
    prm_pSubMenu->locate(prm_target_X, prm_target_Y); //���ɂ��void MenuBoard::rise() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
    StringBoardMenu::riseSub(prm_pSubMenu);
}

bool MenuBoard::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        _pSeTxer->play(SE_DECIDED_NOMAL);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != NULL &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
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
    //�X���C�h�C���g�����W�V����
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
    StringBoardMenu::processBehavior();
    if (_pKurokoA->isRunnigSmoothMvSequence()) {
        //�X���C�h��
    } else {
        //�X���C�h�I�����A�ړI�̍��W�֕␳
        locate(target_X_, target_Y_);
    }
    _pKurokoA->behave();
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSunk() {
    //�X���C�h�A�E�g�g�����W�V����
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
