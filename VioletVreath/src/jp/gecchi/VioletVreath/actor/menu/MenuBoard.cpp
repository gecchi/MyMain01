#include "MenuBoard.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/actor/menu/MousePointer.h"

using namespace GgafLib;
using namespace VioletVreath;

MenuBoard::MenuBoard(const char* prm_name, const char* prm_model) :
        DefaultFramedBoardMenu(prm_name, prm_model) {
    _class_name = "MenuBoard";
    slide_from_offset_x_ = 0;
    slide_from_offset_y_ = 0;
    target_x_ = _x;
    target_y_ = _y;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_ON_RISEN      , "SE_MENU_ON_RISEN");
    pSeTx->set(SE_MOVE_CURSOR   , "SE_MENU_MOVE_CURSOR");
    pSeTx->set(SE_DECIDED       , "SE_MENU_DECIDED");
    pSeTx->set(SE_CANCEL        , "SE_MENU_CANCEL");
    pSeTx->set(SE_WRONG         , "SE_MENU_WRONG");

    pMousePointer_ = pMOUSEPOINTER;

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
        getSeTransmitter()->play(SE_DECIDED);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != nullptr &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        //���ʂɁu���j���[�A�C�e���F�L�����Z���v�ɃJ�[�\��������ꍇ�ł��AVB_UI_CANCEL �{�^���̏ꍇ�́A
        //�u���j���[�A�C�e���F�L�����Z���v���u����v�������Ƃɂ���B
        //���J�[�\�����u���j���[�A�C�e���F�L�����Z���v�ɂ��邩�ǂ����̔��f�́A
        //relateAllItemToCancel() �Œ�`���ꂽ�A�C�e���̃C���f�b�N�X���ǂ����Ŕ��f�B
        getSeTransmitter()->play(SE_CANCEL);
        return true;
    } else if (pMousePointer_ && pMousePointer_->isReleasedUpButton(0)) {
        getSeTransmitter()->play(SE_DECIDED);
        return true;
    } else {
        return false;
    }
}

bool MenuBoard::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVB_UI_CANCEL �{�^���̏ꍇ��
        //���̃A�C�e�����u�L�����Z���v�������Ƃ���B(������O����)
        getSeTransmitter()->play(SE_CANCEL);
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
    return hasJustCancelled();
}
GgafDx::FigureActor* MenuBoard::condSelectItem() {
    if (pMousePointer_) {
        GgafCore::Actor*  pSelectedActor = pMousePointer_->getSelectedActor();
        if (pSelectedActor) {
            if (pSelectedActor->instanceOf(Obj_GgafDx_FigureActor)) {
                return (GgafDx::FigureActor*)pSelectedActor;
            }
        }
    }
    return nullptr;
}
void MenuBoard::riseMe() {
    target_x_ = _x;
    target_y_ = _y;
    DefaultFramedBoardMenu::riseMe();
}

void MenuBoard::rise(coord prm_target_x, coord prm_target_y) {
    target_x_ = prm_target_x;
    target_y_ = prm_target_y;
    DefaultFramedBoardMenu::riseMe();
}

//void MenuBoard::riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y) {
//    DefaultFramedBoardMenu::getSubMenu(prm_index)->setPosition(prm_target_x, prm_target_y); //���ɂ��void MenuBoard::riseMe() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
//    DefaultFramedBoardMenu::riseSubMenu(prm_index);
//}
//void MenuBoard::riseSubMenu(coord prm_target_x, coord prm_target_y) {
//    riseSubMenu(0, prm_target_x, prm_target_y);
//}

void MenuBoard::moveCursor(bool prm_smooth) {
    DefaultFramedBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //�X���[�Y�ړ�true���Ȃ킿�A������ԁB
        getSeTransmitter()->play(SE_MOVE_CURSOR);
    }
}

void MenuBoard::onMoveCursor(int prm_from_index, int prm_selected_index) {
}

void MenuBoard::onSelect(int prm_from_index, int prm_selected_index) {
}

void MenuBoard::initialize() {
    //�C���f�b�N�X�쐬
    _lstItems.createIndex();
    _lstLabelActors.createIndex();
    _lstSubMenu.createIndex();
    _lstSubCursor.createIndex();
}

void MenuBoard::onRise() {
    //�X���C�h�C���g�����W�V����
    setPosition(target_x_ + slide_from_offset_x_,
                target_y_ + slide_from_offset_y_);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setMvAngTwd(target_x_, target_y_);
    pVecVehicle->asstMv()->slideByDt(UTIL::getDistance(_x, _y, target_x_, target_y_), _fade_frames,
                                 0.2, 0.3, 0, true);
    getSeTransmitter()->play(SE_ON_RISEN);
}

void MenuBoard::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    if (pVecVehicle->asstMv()->hasJustFinishedSliding()) {
        //�X���C�h�I�����A�ړI�̍��W�֕␳
        setPosition(target_x_, target_y_);
    }
    pVecVehicle->behave();
    DefaultFramedBoardMenu::processBehavior();
    //���j���[�I���A�C�e���A�\���A�C�e���A�J�[�\���́A
    //�{�[�h���W����ɂ��Ă��邽�߁A���g�̍��W�m����
    //��� processBehavior() ���R�[�������ق����ǂ��B
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSink() {
    //�X���C�h�A�E�g�g�����W�V����
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setMvAngTwd(target_x_ + slide_from_offset_x_,
                         target_y_ + slide_from_offset_y_);
    pVecVehicle->asstMv()->slideByDt(
                           UTIL::getDistance(
                                  _x, _y,
                                  target_x_+slide_from_offset_x_,
                                  target_y_+slide_from_offset_y_
                           ),
                           _fade_frames,
                           0.2, 0.3, 0, true
                       );
}

void MenuBoard::addItem(GgafDx::FigureActor* prm_pItem,
                        coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    if (prm_pItem->instanceOf(Obj_FontBoardActor)) {
        FontBoardActor* pItem = (FontBoardActor*)prm_pItem;
        pItem->getWorldCollisionChecker()->createCollisionArea(1);
        pItem->getWorldCollisionChecker()->setColliAABox(0, 0.95, 1.0); //��95%�A�c100%
        pItem->setHitAble(true);
        pItem->setDefaultKind(KIND_2DFIX_MENU_ITEM);
    }
    DefaultFramedBoardMenu::addItem(prm_pItem, prm_x_local, prm_y_local, prm_z_local);
}

MenuBoard::~MenuBoard() {
}
