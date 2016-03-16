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
        //relateAllItemToCancel() �Œ�`���ꂽ�A�C�e���̃C���f�b�N�X���ǂ����Ŕ��f�B
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
    FixFontBoardMenu::getSubMenu(prm_index)->position(prm_target_x, prm_target_y); //���ɂ��void MenuSelectSub::riseMe() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
    FixFontBoardMenu::riseSubMenu(prm_index);
}

void MenuSelectSub::moveCursor(bool prm_smooth) {
    FixFontBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //�X���[�Y�ړ�true���Ȃ킿�A������ԁB
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
