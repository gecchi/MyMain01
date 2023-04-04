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
    _coord_primary_buffer_source_left = PX_C(pSpacetime->_primary_buffer_source_left);
    _coord_primary_buffer_source_top = PX_C(pSpacetime->_primary_buffer_source_top);
    _coord_secondary_buffer_source_left = PX_C(pSpacetime->_secondary_buffer_source_left);
    _coord_secondary_buffer_source_top = PX_C(pSpacetime->_secondary_buffer_source_top);
    _last_hWnd = pCARETAKER->_pHWndPrimary;
    _pHitActor = nullptr;
    _is_select_able = false;
}

void MousePointerActor::processSettlementBehavior() {
    DefaultSpacetime* pSpacetime = pCARETAKER->getSpacetime();
    //マウスの座標を取得
    GetCursorPos(&_mouse_point);
    // カーソル位置からウィンドウハンドル取得
    HWND hWnd = WindowFromPoint(_mouse_point);
    if (hWnd == pCARETAKER->_pHWndPrimary || hWnd == pCARETAKER->_pHWndSecondary) {
        _last_hWnd = hWnd;
    }
    // スクリーン座標をクライアント座標に変換する
    ScreenToClient(_last_hWnd, &_mouse_point);
//    _TRACE_("_last_hWnd="<<_last_hWnd<<"   _pHWndSecondary="<<pCARETAKER->_pHWndSecondary<<"/_pHWndPrimary="<<pCARETAKER->_pHWndPrimary);
    if (_last_hWnd == pCARETAKER->_pHWndSecondary) {
        RECT& rect_Present = pCARETAKER->_aRect_Present[SECONDARY_VIEW];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* pSpacetime->_secondary_buffer_source_width) / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* pSpacetime->_secondary_buffer_source_height) / (1.0* cPresent_h));
        _x = PX_C(x) + _coord_secondary_buffer_source_left;
        _y = PX_C(y) + _coord_secondary_buffer_source_top;
    } else if (_last_hWnd == pCARETAKER->_pHWndPrimary) {
        RECT& rect_Present = pCARETAKER->_aRect_Present[PRIMARY_VIEW];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* pSpacetime->_primary_buffer_source_width) / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* pSpacetime->_primary_buffer_source_height) / (1.0* cPresent_h));
        _x = PX_C(x) + _coord_primary_buffer_source_left;
        _y = PX_C(y) + _coord_primary_buffer_source_top;
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

bool MousePointerActor::processHitChkLogic(Actor* prm_pOtherActor) {
     return DefaultBoardActor::processHitChkLogic(prm_pOtherActor);
}

void MousePointerActor::onHit(const Actor* prm_pOtherActor) {
    _pHitActor = (Actor*)prm_pOtherActor;
}
bool MousePointerActor::isReleasedUpButton(int prm_button_no) {
    bool button = GgafDx::Input::isReleasedUpMouseButton(prm_button_no);
    return button;
}
bool MousePointerActor::isPushedDownButton(int prm_button_no) {
    bool button = GgafDx::Input::isPushedDownMouseButton(prm_button_no);
    return button;
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
