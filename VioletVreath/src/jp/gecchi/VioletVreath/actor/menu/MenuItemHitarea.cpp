#include  "MenuItemHitarea.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

using namespace GgafLib;
using namespace VioletVreath;

MenuItemHitarea::MenuItemHitarea(GgafDx::FigureActor* prm_pItem) : DefaultGeometricActor("MenuItemHitarea", UTIL::createChecker(this)) {
    _class_name = "MenuItemHitarea";
    _pItem = prm_pItem;
}
void MenuItemHitarea::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);

    GgafLib::FontBoardActor* pItem = (GgafLib::FontBoardActor*)_pItem;
    pixcoord px_total_width = pItem->getTotalWidth();
    pixcoord px_total_height = pItem->getTotalHeight();
    pixcoord cx = 0;
    pixcoord cy = 0;
    Align _align =  pItem->_align;
    Valign _valign =  pItem->_valign;
    if (_align == ALIGN_LEFT) {
        cx = +(px_total_width/2);
        if (_valign == VALIGN_TOP) {
            cy = -(px_total_height/2);
        } else if (_valign == VALIGN_MIDDLE) {
            cy = 0;
        } else if (_valign == VALIGN_BOTTOM) {
            cy = +(px_total_height/2);
        }
    } else if (_align == ALIGN_CENTER) {
        cx = 0;
        if (_valign == VALIGN_TOP) {
            cy = -(px_total_height/2);
        } else if (_valign == VALIGN_MIDDLE) {
            cy = 0;
        } else if (_valign == VALIGN_BOTTOM) {
            cy = +(px_total_height/2);
        }
    } else if (_align == ALIGN_RIGHT) {
        cx = -(px_total_width/2);
        if (_valign == VALIGN_TOP) {
            cy = -(px_total_height/2);
        } else if (_valign == VALIGN_MIDDLE) {
            cy = 0;
        } else if (_valign == VALIGN_BOTTOM) {
            cy = +(px_total_height/2);
        }
    }

    pChecker->setColliAABox_WHD(0, PX_C(cx), PX_C(cy), 0, PX_C(px_total_width), PX_C(px_total_height), PX_C(1));
}
void MenuItemHitarea::processSettlementBehavior() {
}

void MenuItemHitarea::processPreJudgement() {
    //–Ø“o˜^
    coord w = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH);
    coord h = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT);
    coord left = -(w/2);
    coord top =  h/2;


    _x = left + _pItem->_x;
    _y = top  + (-1 * _pItem->_y);
    _pChecker->updateHitArea();
}


MenuItemHitarea::~MenuItemHitarea() {
}
