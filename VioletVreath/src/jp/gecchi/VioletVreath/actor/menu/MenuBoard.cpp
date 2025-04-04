#include "MenuBoard.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
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
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_ON_RISEN      , "SE_MENU_ON_RISEN");
    pSeXmtr->set(SE_MOVE_CURSOR   , "SE_MENU_MOVE_CURSOR");
    pSeXmtr->set(SE_DECIDED       , "SE_MENU_DECIDED");
    pSeXmtr->set(SE_CANCEL        , "SE_MENU_CANCEL");
    pSeXmtr->set(SE_WRONG         , "SE_MENU_WRONG");

    pMousePointer_ = pMOUSEPOINTER;

}

void MenuBoard::setTransition(frame prm_menu_fade_frames,
                              coord prm_slide_from_offset_x, coord prm_slide_from_offset_y) {
    setFadeFrames(prm_menu_fade_frames);
    slide_from_offset_x_ = prm_slide_from_offset_x;
    slide_from_offset_y_ = prm_slide_from_offset_y;
}

bool MenuBoard::condDecision() {
    if (VVB->isPushedDown(0, VV_VB_UI_EXECUTE)) {
        //「メニューアイテム：任意」で、VV_VB_UI_EXECUTE ボタンの場合は
        //そのアイテムを「決定」した事とする。(当たり前だが)
        getSeXmtr()->play(SE_DECIDED);
        return true;
    } else if (VVB->isPushedDown(0, VV_VB_UI_CANCEL) &&
               _lstItems.getRelation(ITEM_RELATION_TO_CANCEL) != nullptr &&
               _lstItems.getCurrent() == _lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        //特別に「メニューアイテム：キャンセル」にカーソルがある場合でかつ、VV_VB_UI_CANCEL ボタンの場合は、
        //「メニューアイテム：キャンセル」を「決定」したことにする。
        //現カーソルが「メニューアイテム：キャンセル」にあるかどうかの判断は、
        //relateAllItemToCancel() で定義されたアイテムのインデックスかどうかで判断。
        getSeXmtr()->play(SE_CANCEL);
        return true;
    } else if (pMousePointer_ && pMousePointer_->isReleasedUpButton(0)) {
        GgafCore::Actor* pHitActor = pMousePointer_->getHitActor();
        if (_lstItems.getCurrent() == pHitActor) {
            getSeXmtr()->play(SE_DECIDED);
            return true;
        } else {
            getSeXmtr()->play(SE_WRONG);
            return false;
        }
    } else {
        return false;
    }
}

bool MenuBoard::condCancel() {
    if (VVB->isPushedDown(0, VV_VB_UI_CANCEL)) {
        //「メニューアイテム：任意」で、VV_VB_UI_CANCEL ボタンの場合は
        //そのアイテムを「キャンセル」した事とする。(当たり前だが)
        getSeXmtr()->play(SE_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoard::condSelectNext() {
    return VVB->isAutoRepeat(0, VV_VB_UI_DOWN);
}

bool MenuBoard::condSelectPrev() {
    return VVB->isAutoRepeat(0, VV_VB_UI_UP);
}

bool MenuBoard::condSelectExNext() {
    return VVB->isAutoRepeat(0, VV_VB_UI_RIGHT);
}

bool MenuBoard::condSelectExPrev() {
    return VVB->isAutoRepeat(0, VV_VB_UI_LEFT);
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
//    DefaultFramedBoardMenu::getSubMenu(prm_index)->setPosition(prm_target_x, prm_target_y); //←によりvoid MenuBoard::riseMe() に来た時にターゲット設定される
//    DefaultFramedBoardMenu::riseSubMenu(prm_index);
//}
//void MenuBoard::riseSubMenu(coord prm_target_x, coord prm_target_y) {
//    riseSubMenu(0, prm_target_x, prm_target_y);
//}

void MenuBoard::moveCursor(bool prm_smooth) {
    DefaultFramedBoardMenu::moveCursor(prm_smooth);
    if (prm_smooth) { //スムーズ移動trueすなわち、活動状態。
        getSeXmtr()->play(SE_MOVE_CURSOR);
    }
}

void MenuBoard::onMoveCursor(int prm_from_index, int prm_selected_index) {
}

void MenuBoard::onSelect(int prm_from_index, int prm_selected_index) {
}

void MenuBoard::initialize() {
    //インデックス作成
    _lstItems.createIndex();
    _lstLabelActors.createIndex();
    _lstSubMenu.createIndex();
    _lstSubCursor.createIndex();
}

void MenuBoard::onRise() {
    //スライドイントランジション
    setPosition(target_x_ + slide_from_offset_x_,
                target_y_ + slide_from_offset_y_);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvAngTwd(target_x_, target_y_);
    pLocusVehicle->asstMv()->slideByDt(UTIL::getDistance(_x, _y, target_x_, target_y_), _fade_frames,
                                 0.2, 0.3, 0, true);
    getSeXmtr()->play(SE_ON_RISEN);
}

void MenuBoard::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    if (pLocusVehicle->asstMv()->hasJustFinishedSliding()) {
        //スライド終了時、目的の座標へ補正
        setPosition(target_x_, target_y_);
    }
    pLocusVehicle->behave();
    DefaultFramedBoardMenu::processBehavior();
    //メニュー選択アイテム、表示アイテム、カーソルは、
    //ボード座標を基にしているため、自身の座標確定後に
    //上位 processBehavior() をコールしたほうが良い。
}

void MenuBoard::processJudgement() {
}

void MenuBoard::onSink() {
    //スライドアウトトランジション
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvAngTwd(target_x_ + slide_from_offset_x_,
                         target_y_ + slide_from_offset_y_);
    pLocusVehicle->asstMv()->slideByDt(
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
        pItem->getViewCollisionChecker()->addCollisionArea(1);
        pItem->getViewCollisionChecker()->setColliAABox(0, 0.95, 1.0); //横95%、縦100%
        pItem->setHitAble(true);
        pItem->setCheckerKind(KIND_2DFIX_MENU_ITEM);
    }
    DefaultFramedBoardMenu::addItem(prm_pItem, prm_x_local, prm_y_local, prm_z_local);
}

MenuBoard::~MenuBoard() {
}
