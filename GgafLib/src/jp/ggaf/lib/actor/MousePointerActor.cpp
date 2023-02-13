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

//    _w_r =  1.0 * CONFIG::GAME_BUFFER_WIDTH / CONFIG::RENDER_TARGET_BUFFER_WIDTH;
//    _h_r =  1.0 * CONFIG::GAME_BUFFER_HEIGHT / CONFIG::RENDER_TARGET_BUFFER_HEIGHT;
//
//    _buffer_left1 = CONFIG::RENDER_BUFFER_SOURCE1_LEFT*_w_r;
//    _buffer_top1 = CONFIG::RENDER_BUFFER_SOURCE1_TOP*_h_r;
//    _buffer_width1 = CONFIG::RENDER_BUFFER_SOURCE1_WIDTH*_w_r;
//    _buffer_height1 = CONFIG::RENDER_BUFFER_SOURCE1_HEIGHT*_h_r;
//
//    _buffer_left2 = CONFIG::RENDER_BUFFER_SOURCE2_LEFT*_w_r;
//    _buffer_top2 = CONFIG::RENDER_BUFFER_SOURCE2_TOP*_h_r;
//    _buffer_width2 = CONFIG::RENDER_BUFFER_SOURCE2_WIDTH*_w_r;
//    _buffer_height2 = CONFIG::RENDER_BUFFER_SOURCE2_HEIGHT*_h_r;
    DefaultSpacetime* pSpacetime = pCARETAKER->getSpacetime();

    _coord_buffer_left1 = PX_C(pSpacetime->_buffer_left1);
    _coord_buffer_top1 = PX_C(pSpacetime->_buffer_top1);

    _coord_buffer_left2 = PX_C(pSpacetime->_buffer_left2);
    _coord_buffer_top2 = PX_C(pSpacetime->_buffer_top2);
    _last_hWnd = pCARETAKER->_pHWndPrimary;
//    _pSelectActor_prev = nullptr;
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
    if (_last_hWnd == pCARETAKER->_pHWndSecondary) {
        RECT& rect_Present = pCARETAKER->_aRect_Present[pCARETAKER->_secondary_adapter_no];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* pSpacetime->_buffer_width2) / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* pSpacetime->_buffer_height2) / (1.0* cPresent_h));
        _x = PX_C(x) + _coord_buffer_left2;
        _y = PX_C(y) + _coord_buffer_top2;
    } else if (_last_hWnd == pCARETAKER->_pHWndPrimary) {
        RECT& rect_Present = pCARETAKER->_aRect_Present[pCARETAKER->_primary_adapter_no];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* pSpacetime->_buffer_width1) / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* pSpacetime->_buffer_height1) / (1.0* cPresent_h));
        _x = PX_C(x) + _coord_buffer_left1;
        _y = PX_C(y) + _coord_buffer_top1;
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
