#include "jp/ggaf/lib/actor/MousePointerActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/BoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

using namespace GgafLib;

MousePointerActor::MousePointerActor(const char* prm_name, const char* prm_model)
      : DefaultBoardActor(prm_name, prm_model) {
    DefaultSpacetime* pSpacetime = pCARETAKER->getSpacetime();
    _last_hWnd = pCARETAKER->_pHWndPrimary;
    _point_hWnd = nullptr;
    _pHitActor = nullptr;
    _is_select_able = false;
    _is_game_window = false;
}

void MousePointerActor::processSettlementBehavior() {
    DefaultCaretaker* pCaretaker = pCARETAKER;
    DefaultSpacetime* pSpacetime = pCaretaker->getSpacetime();
    //マウスの座標を取得
    GetCursorPos(&_mouse_point);
    // カーソル位置からウィンドウハンドル取得
    _point_hWnd = WindowFromPoint(_mouse_point);
    _is_game_window = false;
    for (int wno = 0; wno < pCaretaker->_num_window; wno++) {
        if (_point_hWnd == pCaretaker->_paHWnd[wno]) {
            _last_hWnd = _point_hWnd;
            _is_game_window = true;
            break;
        }
    }
    // スクリーン座標をクライアント座標に変換する
    ScreenToClient(_last_hWnd, &_mouse_point);
    int last_pry = pCaretaker->_mapHwndToScreenPriority[_last_hWnd];
    if (last_pry >= 0) {
        RECT& rect_Present = pCaretaker->_aRect_Present[last_pry];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* pSpacetime->_buffer_source[last_pry].width)  / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* pSpacetime->_buffer_source[last_pry].height) / (1.0* cPresent_h));
        _x = PX_C(x) + PX_C(pSpacetime->_buffer_source[last_pry].left);
        _y = PX_C(y) + PX_C(pSpacetime->_buffer_source[last_pry].top);

//        _TRACE_("x,y="<<x<<","<<y<<"");
//        _TRACE_("rect_Present="<<rect_Present.right<<","<<rect_Present.left<<","<<rect_Present.bottom<<","<<rect_Present.top<<"");
//        _TRACE_("cPresent_w,cPresent_h="<<cPresent_w<<","<<cPresent_h<<"");
//        _TRACE_("pSpacetime->_primary_buffer_source_width,_primary_buffer_source_height="<<pSpacetime->_primary_buffer_source_width<<","<<pSpacetime->_primary_buffer_source_height<<"");
//        _TRACE_("rect_Present.left,rect_Present.top="<<rect_Present.left<<","<<rect_Present.top<<"");
//        _TRACE_("_mouse_point.x,_mouse_point.y="<<_mouse_point.x<<","<<_mouse_point.y<<"");
//        _TRACE_("_coord_primary_buffer_source_left,_coord_primary_buffer_source_top="<<_coord_primary_buffer_source_left<<","<<_coord_primary_buffer_source_top<<"");
//        _TRACE_("_x,_y="<<_x<<","<<_y<<"");
    } else {
        //どうしよう
    }
    if (GgafDx::Input::isPushedDownMouseButton(0)) {
        _is_select_able = true;
//        _TRACE_("クリック _is_select_able !!!!!!!!!!!!!!!!");
    } else {
        long dx, dy, dz;
        GgafDx::Input::getMousePointer_REL(&dx, &dy, &dz);
//        _TRACE_("getMousePointer ("<<dx<<","<<dy<<","<<dz<<")");
        if (dx == 0 && dy == 0) {
            _is_select_able = false;
        } else {
//            _TRACE_("移動 _is_select_able !!!!!!!!!!!!!!!!");
            _is_select_able = true;
        }
    }
    DefaultBoardActor::processSettlementBehavior(); //木登録
    _pHitActor = nullptr;
}

void MousePointerActor::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    _pHitActor = prm_pOppHitChecker->_pActor;
}
bool MousePointerActor::isReleasedUpButton(int prm_button_no) {
    if (_is_game_window) {
        bool button = GgafDx::Input::isReleasedUpMouseButton(prm_button_no);
        return button;
    } else {
        return false;
    }

}
bool MousePointerActor::isPushedDownButton(int prm_button_no) {
    if (_is_game_window) {
        bool button = GgafDx::Input::isPushedDownMouseButton(prm_button_no);
        return button;
    } else {
        return false;
    }

}

GgafCore::Actor* MousePointerActor::getSelectedActor() {
    if (_is_select_able ) {
        return _pHitActor;
    } else {
        return nullptr;
    }
}

MousePointerActor::~MousePointerActor() {
}
