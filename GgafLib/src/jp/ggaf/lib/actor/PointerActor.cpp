#include "jp/ggaf/lib/actor/PointerActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/BoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/actor/HitArea2D.hpp"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

using namespace GgafLib;

PointerActor::PointerActor(const char* prm_name, const char* prm_model)
      : DefaultBoardActor(prm_name, prm_model) {

    _w_r =  1.0 * CONFIG::GAME_BUFFER_WIDTH / CONFIG::RENDER_TARGET_BUFFER_WIDTH;
    _h_r =  1.0 * CONFIG::GAME_BUFFER_HEIGHT / CONFIG::RENDER_TARGET_BUFFER_HEIGHT;

    _buffer_left1 = CONFIG::RENDER_BUFFER_SOURCE1_LEFT*_w_r;
    _buffer_top1 = CONFIG::RENDER_BUFFER_SOURCE1_TOP*_h_r;
    _buffer_width1 = CONFIG::RENDER_BUFFER_SOURCE1_WIDTH*_w_r;
    _buffer_height1 = CONFIG::RENDER_BUFFER_SOURCE1_HEIGHT*_h_r;

    _buffer_left2 = CONFIG::RENDER_BUFFER_SOURCE2_LEFT*_w_r;
    _buffer_top2 = CONFIG::RENDER_BUFFER_SOURCE2_TOP*_h_r;
    _buffer_width2 = CONFIG::RENDER_BUFFER_SOURCE2_WIDTH*_w_r;
    _buffer_height2 = CONFIG::RENDER_BUFFER_SOURCE2_HEIGHT*_h_r;

    _coord_buffer_left1 = PX_C(_buffer_left1);
    _coord_buffer_top1 = PX_C(_buffer_top1);

    _coord_buffer_left2 = PX_C(_buffer_left2);
    _coord_buffer_top2 = PX_C(_buffer_top2);

//    HitArea2D<DefaultBoardActor>* pHitArea2D = NEW HitArea2D<DefaultBoardActor>(this);
//    appendChild(pHitArea2D);
//    CollisionChecker*pHitAreaChecker = pHitArea2D->getCollisionChecker();
//    pHitAreaChecker->createCollisionArea(1);
//    pHitAreaChecker->setColliAABox_WHD(0, PX_C(200), PX_C(100), PX_C(10));
//    pHitArea2D->setHitAble(true);
}

void PointerActor::processSettlementBehavior() {
    //マウスの座標を取得
    GetCursorPos(&_mouse_point);
//    _TRACE_("絶対座標：("<<_mouse_point.x<<","<<_mouse_point.y<<")");
    // カーソル位置からウィンドウハンドル取得
    HWND hWnd = WindowFromPoint(_mouse_point);
    // スクリーン座標をクライアント座標に変換する
    ScreenToClient(hWnd, &_mouse_point);
//    _TRACE_("クライアント：("<<_mouse_point.x<<","<<_mouse_point.y<<")");
    if (hWnd == pCARETAKER->_pHWndSecondary) {
        RECT& rect_Present = pCARETAKER->_aRect_Present[pCARETAKER->_secondary_adapter_no];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* _buffer_width2) / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* _buffer_height2) / (1.0* cPresent_h));
        _x = PX_C(x) + _coord_buffer_left2;
        _y = PX_C(y) + _coord_buffer_top2;
    } else {
        RECT& rect_Present = pCARETAKER->_aRect_Present[pCARETAKER->_primary_adapter_no];
        pixcoord cPresent_w = rect_Present.right - rect_Present.left;
        pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;
        pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* _buffer_width1) / (1.0* cPresent_w));
        pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* _buffer_height1) / (1.0* cPresent_h));
        _x = PX_C(x) + _coord_buffer_left1;
        _y = PX_C(y) + _coord_buffer_top1;
    }
    if (GgafDx::Input::isPushedDownKey(DIK_Q)) {
    }

}

PointerActor::~PointerActor() {
}
