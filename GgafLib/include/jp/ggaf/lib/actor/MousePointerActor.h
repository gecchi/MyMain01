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

//    coord _coord_primary_buffer_source_left;
//    coord _coord_primary_buffer_source_top;
//    coord _coord_secondary_buffer_source_left;
//    coord _coord_secondary_buffer_source_top;

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

    /**
     * マウスのボタンが離された直後かどうか調べる .
     * @param prm_button_no マウスボタン番号(0~7)
     * 0:左ボタン
     * 1:右ボタン
     * 2:中央ボタン（ホイールボタン）
     * 3:第4ボタン（サイドボタン1）
     * 4:第5ボタン（サイドボタン2）
     * 5~7:未使用
     * @return true：そのボタンは離された直後である／false：そうでは無い
     */
    virtual bool isReleasedUpButton(int prm_button_no);

    /**
     * マウスのボタンが押された直後かどうかを調べる .
     * @param prm_button_no マウスボタン番号(0~7)
     * 0:左ボタン
     * 1:右ボタン
     * 2:中央ボタン（ホイールボタン）
     * 3:第4ボタン（サイドボタン1）
     * 4:第5ボタン（サイドボタン2）
     * 5~7:未使用
     * @return true：そのボタンは離された直後である／false：そうでは無い
     */
    virtual bool isPushedDownButton(int prm_button_no);

    virtual ~MousePointerActor();
};

}
#endif /*GGAF_LIB_MOUSEPOINTERACTOR_H_*/

