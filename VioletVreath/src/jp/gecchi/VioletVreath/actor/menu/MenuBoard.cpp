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
        getSeTx()->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoard::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVB_UI_CANCEL �{�^���̏ꍇ��
        //���̃A�C�e�����u�L�����Z���v�������Ƃ���B(������O����)
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
    StringBoardMenu::getSubMenu(prm_index)->position(prm_target_x, prm_target_y); //���ɂ��void MenuBoard::riseMe() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
    StringBoardMenu::riseSubMenu(prm_index);
}

void MenuBoard::moveCursor(bool prm_smooth) {
    StringBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //�X���[�Y�ړ�true���Ȃ킿�A������ԁB
        getSeTx()->play(SE_MOVE_CURSOR);
    }
}

void MenuBoard::onMoveCursor(int prm_from, int prm_to) {
}

void MenuBoard::onSelect(int prm_from, int prm_to) {
}

void MenuBoard::initialize() {
    //�C���f�b�N�X�쐬
    _lstItems.indexedValue();
    _lstDispActors.indexedValue();
}

void MenuBoard::onRise() {
    //�X���C�h�C���g�����W�V����
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
        //�X���C�h�I�����A�ړI�̍��W�֕␳
        position(target_x_, target_y_);
    }
    pKuroko->behave();
    StringBoardMenu::processBehavior();
    //���j���[�I���A�C�e���A�\���A�C�e���A�J�[�\���́A
    //�{�[�h���W����ɂ��Ă��邽�߁A���g�̍��W�m����
    //��� processBehavior() ���R�[�������ق����ǂ��B
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSink() {
    //�X���C�h�A�E�g�g�����W�V����
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
