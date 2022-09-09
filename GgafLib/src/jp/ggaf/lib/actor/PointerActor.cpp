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
    HitArea2D<DefaultBoardActor>* pHitArea2D = NEW HitArea2D<DefaultBoardActor>(this);
    appendChild(pHitArea2D);
    CollisionChecker*pHitAreaChecker = pHitArea2D->getCollisionChecker();
    pHitAreaChecker->createCollisionArea(1);
    pHitAreaChecker->setColliAABox_WHD(0, PX_C(200), PX_C(100), PX_C(10));
    pHitArea2D->setHitAble(true);
}

void PointerActor::processSettlementBehavior() {
    //�}�E�X�̍��W���擾
    GetCursorPos(&_mouse_point);
    _TRACE_("��΍��W�F("<<_mouse_point.x<<","<<_mouse_point.y<<")");
    // �X�N���[�����W���N���C�A���g���W�ɕϊ�����
    ScreenToClient(pCARETAKER->_pHWndPrimary, &_mouse_point);
    _TRACE_("�N���C�A���g�F("<<_mouse_point.x<<","<<_mouse_point.y<<")");
    DefaultCaretaker* pCaretaker = pCARETAKER;

    //��ʍ�������߂�
//    _rectRenderTargetBuffer.left   = CONFIG::RENDER_BUFFER_SOURCE1_LEFT;
//    _rectRenderTargetBuffer.top    = CONFIG::RENDER_BUFFER_SOURCE1_TOP;
//    _rectRenderTargetBuffer.right  = _rectRenderTargetBuffer.left + CONFIG::RENDER_BUFFER_SOURCE1_WIDTH;
//    _rectRenderTargetBuffer.bottom = _rectRenderTargetBuffer.top  + CONFIG::RENDER_BUFFER_SOURCE1_HEIGHT;
//    RECT wRect1, cRect1; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
//    pixcoord ww1, wh1; // �E�B���h�E�S�̂̕��A����
//    pixcoord cw1, ch1; // �N���C�A���g�̈�̕��A����
//    pixcoord fw1, fh1; // �t���[���̕��A����
//    // �E�B���h�E�S�̂̕��E�������v�Z
//    GetWindowRect(hWnd, &wRect1);
//    ww1 = wRect1.right - wRect1.left;
//    wh1 = wRect1.bottom - wRect1.top;
//    // �N���C�A���g�̈�̕��E�������v�Z
//    GetClientRect(hWnd, &cRect1);
//    cw1 = cRect1.right - cRect1.left;
//    ch1 = cRect1.bottom - cRect1.top;

//    pixcoord buffer_width = pCaretaker->_rectRenderTargetBuffer.right - pCaretaker->_rectRenderTargetBuffer.left;
//    pixcoord buffer_height = pCaretaker->_rectRenderTargetBuffer.bottom - pCaretaker->_rectRenderTargetBuffer.top;
//double w_r =  1.0 * CONFIG::RENDER_TARGET_BUFFER_WIDTH / CONFIG::RENDER_BUFFER_SOURCE1_WIDTH;
//double h_r =  1.0 * CONFIG::RENDER_TARGET_BUFFER_HEIGHT / CONFIG::RENDER_BUFFER_SOURCE1_HEIGHT;
double w_r =  1.0 * CONFIG::GAME_BUFFER_WIDTH / CONFIG::RENDER_TARGET_BUFFER_WIDTH;
double h_r =  1.0 * CONFIG::GAME_BUFFER_HEIGHT / CONFIG::RENDER_TARGET_BUFFER_HEIGHT;
    pixcoord buffer_width = CONFIG::RENDER_BUFFER_SOURCE1_WIDTH*w_r;
    pixcoord buffer_height = CONFIG::RENDER_BUFFER_SOURCE1_HEIGHT*h_r;

//    GetClientRect(pCARETAKER->_pHWndPrimary, &cRect1);
//    pixcoord cw1 = cRect1.right - cRect1.left;
//    pixcoord ch1 = cRect1.bottom - cRect1.top;

    RECT& rect_Present = pCARETAKER->_aRect_Present[pCARETAKER->_primary_adapter_no];
    pixcoord cPresent_w = rect_Present.right - rect_Present.left;
    pixcoord cPresent_h = rect_Present.bottom - rect_Present.top;

    pixcoord x = (_mouse_point.x - rect_Present.left) * ((1.0* buffer_width) / (1.0* cPresent_w));
    pixcoord y = (_mouse_point.y - rect_Present.top)  * ((1.0* buffer_height) / (1.0* cPresent_h));
    _x = PX_C(x) + PX_C(CONFIG::RENDER_BUFFER_SOURCE1_LEFT*w_r);
    _y = PX_C(y) + PX_C(CONFIG::RENDER_BUFFER_SOURCE1_TOP*h_r);
    if (GgafDx::Input::isPushedDownKey(DIK_Q)) {
    }

}

PointerActor::~PointerActor() {
}
