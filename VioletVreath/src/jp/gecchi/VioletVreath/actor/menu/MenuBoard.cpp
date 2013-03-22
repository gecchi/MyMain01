#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoard::MenuBoard(const char* prm_name, const char* prm_model) :
        StringBoardMenu(prm_name, prm_model) {
    _class_name = "MenuBoard";
    slide_from_offset_X_ = 0;
    slide_from_offset_Y_ = 0;
    target_X_ = _X;
    target_Y_ = _Y;
    _pSeTx->set(SE_ON_RISEN      , "WAVE_MENU_ON_RISEN"      );
    _pSeTx->set(SE_MOVE_CURSOR   , "WAVE_MENU_MOVE_CURSOR"   );
    _pSeTx->set(SE_DECIDED_CANCEL, "WAVE_MENU_DECIDED_CANCEL");
}

void MenuBoard::setTransition(frame prm_menu_fade_frames,
                              coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y) {
    setFadeFrames(prm_menu_fade_frames);
    slide_from_offset_X_ = prm_slide_from_offset_X;
    slide_from_offset_Y_ = prm_slide_from_offset_Y;
}

bool MenuBoard::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVB_UI_EXECUTE �{�^���̏ꍇ��
        //���̃A�C�e�����u����v�������Ƃ���B(������O����)
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != nullptr &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        //���ʂɁu���j���[�A�C�e���F�L�����Z���v�ɃJ�[�\��������ꍇ�ł��AVB_UI_CANCEL �{�^���̏ꍇ�́A
        //�u���j���[�A�C�e���F�L�����Z���v���u����v�������Ƃɂ���B
        //���J�[�\�����u���j���[�A�C�e���F�L�����Z���v�ɂ��邩�ǂ����̔��f�́A
        //relateAllItemCancel() �Œ�`���ꂽ�A�C�e���̃C���f�b�N�X���ǂ����Ŕ��f�B
        _pSeTx->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}
bool MenuBoard::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVB_UI_CANCEL �{�^���̏ꍇ��
        //���̃A�C�e�����u�L�����Z���v�������Ƃ���B(������O����)
        _pSeTx->play(SE_DECIDED_CANCEL);
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
bool MenuBoard::condSelectrExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoard::condSelectCancel() {
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

void MenuBoard::riseSubMenu(int prm_index, coord prm_target_X, coord prm_target_Y) {
    StringBoardMenu::getSubMenu(prm_index)->locate(prm_target_X, prm_target_Y); //���ɂ��void MenuBoard::rise() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
    StringBoardMenu::riseSubMenu(prm_index);
}

void MenuBoard::moveCursor(bool prm_smooth) {
    StringBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //�X���[�Y�ړ�true���Ȃ킿�A������ԁB
        _pSeTx->play(SE_MOVE_CURSOR);
    }
}

void MenuBoard::onMoveCursor(int prm_from, int prm_to) {
}


void MenuBoard::onSelect(int prm_from, int prm_to) {
}

void MenuBoard::initialize() {
}

void MenuBoard::onRise() {
    //�X���C�h�C���g�����W�V����
    locate(target_X_ + slide_from_offset_X_,
           target_Y_ + slide_from_offset_Y_);
    _pKurokoA->setMvAngTwd(target_X_, target_Y_);
    _pKurokoA->slideMvByDT(
                    0,
                    UTIL::getDistance(_X, _Y, target_X_, target_Y_),
                    _fade_frames, 0.2, 0.3
               );
    _pSeTx->play(SE_ON_RISEN);
}

void MenuBoard::processBehavior() {
    if (_pKurokoA->isSlidingMv()) {
        //�X���C�h��
    } else {
        //�X���C�h�I�����A�ړI�̍��W�֕␳
        locate(target_X_, target_Y_);
    }

    _pKurokoA->behave();
    StringBoardMenu::processBehavior();
    //���j���[�I���A�C�e���A�\���A�C�e���A�J�[�\���́A
    //�{�[�h���W����ɂ��Ă��邽�߁A���g�̍��W�m����
    //��� processBehavior() ���R�[�������ق����ǂ��B
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSink() {
    //�X���C�h�A�E�g�g�����W�V����
    _pKurokoA->setMvAngTwd(target_X_ + slide_from_offset_X_,
                           target_Y_ + slide_from_offset_Y_);
    _pKurokoA->slideMvByDT(0,
                       UTIL::getDistance(
                          _X, _Y,
                          target_X_+slide_from_offset_X_, target_Y_+slide_from_offset_Y_
                       ),
                       _fade_frames, 0.2, 0.3
               );
}

MenuBoard::~MenuBoard() {
}
