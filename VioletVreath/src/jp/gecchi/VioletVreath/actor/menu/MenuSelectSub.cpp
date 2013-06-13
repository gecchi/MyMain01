#include "stdafx.h"
#include "MenuSelectSub.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuSelectSub::MenuSelectSub(const char* prm_name, const char* prm_model) :
        StringBoardMenu(prm_name, prm_model) {
    _class_name = "MenuSelectSub";
    target_X_ = _X;
    target_Y_ = _Y;
    _pSeTx->set(SE_MOVE_CURSOR   , "WAVE_MENU_MOVE_CURSOR"   );
    setFadeFrames(0);
    activateImmed(); //�I�����j���[�Ȃ̂ŁA������Ԃ͊�����Ԃ��f�t�H���g�Ƃ���
}

bool MenuSelectSub::condDecision() {
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
        return true;
    } else {
        return false;
    }
}
bool MenuSelectSub::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVB_UI_CANCEL �{�^���̏ꍇ��
        //���̃A�C�e�����u�L�����Z���v�������Ƃ���B(������O����)
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
bool MenuSelectSub::condSelectrExPrev() {
    return false;
}
bool MenuSelectSub::condSelectCancel() {
    return isJustCancelled();
}

void MenuSelectSub::riseMe() {
    target_X_ = _X;
    target_Y_ = _Y;
    StringBoardMenu::riseMe();
}

void MenuSelectSub::rise(coord prm_target_X, coord prm_target_Y) {
    target_X_ = prm_target_X;
    target_Y_ = prm_target_Y;
    StringBoardMenu::riseMe();
}

void MenuSelectSub::riseSubMenu(int prm_index, coord prm_target_X, coord prm_target_Y) {
    StringBoardMenu::getSubMenu(prm_index)->locate(prm_target_X, prm_target_Y); //���ɂ��void MenuSelectSub::riseMe() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
    StringBoardMenu::riseSubMenu(prm_index);
}

void MenuSelectSub::moveCursor(bool prm_smooth) {
    StringBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //�X���[�Y�ړ�true���Ȃ킿�A������ԁB
        _pSeTx->play(SE_MOVE_CURSOR);
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
    locate(target_X_, target_Y_);
    _pKurokoA->behave();
    StringBoardMenu::processBehavior();
    //���j���[�I���A�C�e���A�\���A�C�e���A�J�[�\���́A
    //�{�[�h���W����ɂ��Ă��邽�߁A���g�̍��W�m����
    //��� processBehavior() ���R�[�������ق����ǂ��B
}

void MenuSelectSub::processJudgement() {
}

void MenuSelectSub::onSink() {
}

MenuSelectSub::~MenuSelectSub() {
}
