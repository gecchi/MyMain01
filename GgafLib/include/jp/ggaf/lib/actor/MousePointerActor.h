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
//    pixcoord _primary_buffer_source_left;
//    pixcoord _primary_buffer_source_top;
//    pixcoord _primary_buffer_source_width;
//    pixcoord _primary_buffer_source_height;
//
//    pixcoord _secondary_buffer_source_left;
//    pixcoord _secondary_buffer_source_top;
//    pixcoord _secondary_buffer_source_width;
//    pixcoord _secondary_buffer_source_height;

    coord _coord_primary_buffer_source_left;
    coord _coord_primary_buffer_source_top;
    coord _coord_secondary_buffer_source_left;
    coord _coord_secondary_buffer_source_top;

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

