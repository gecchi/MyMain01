#ifndef GGAF_LIB_MOUSEPOINTERACTOR_H_
#define GGAF_LIB_MOUSEPOINTERACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace GgafLib {


/**
 * マウスポインタ（作成中） .
 * @version 1.00
 * @since 2022/08/09
 * @author Masatoshi Tsuge
 */
class MousePointerActor : public DefaultBoardActor {

protected:

    POINT _mouse_point;
//
//    double _w_r;
//    double _h_r;
//    pixcoord _buffer_left1;
//    pixcoord _buffer_top1;
//    pixcoord _buffer_width1;
//    pixcoord _buffer_height1;
//
//    pixcoord _buffer_left2;
//    pixcoord _buffer_top2;
//    pixcoord _buffer_width2;
//    pixcoord _buffer_height2;

    coord _coord_buffer_left1;
    coord _coord_buffer_top1;
    coord _coord_buffer_left2;
    coord _coord_buffer_top2;

    HWND _last_hWnd;
//    GgafCore::Actor* _pSelectActor_prev;
    GgafCore::Actor* _pHitActor;
    bool _is_select_able;
public:

    MousePointerActor(const char* prm_name, const char* prm_model);

    virtual void processSettlementBehavior() override;

    virtual bool processHitChkLogic(Actor* prm_pOtherActor);

    virtual void onHit(const Actor* prm_pOtherActor);

    virtual GgafCore::Actor* getHitActor() {
        return _pHitActor;
    }
    virtual GgafCore::Actor* getSelectedActor();
    virtual bool isReleasedUpButton(int prm_button_no);
    virtual bool isPushedDownButton(int prm_button_no);

    virtual ~MousePointerActor();
};

}
#endif /*GGAF_LIB_MOUSEPOINTERACTOR_H_*/

