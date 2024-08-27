#ifndef GGAF_LIB_MOUSEPOINTERACTOR_H_
#define GGAF_LIB_MOUSEPOINTERACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace GgafLib {


/**
 * �}�E�X�|�C���^�i�쐬���j .
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
     * �}�E�X�̃{�^���������ꂽ���ォ�ǂ������ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�(0~7)
     * 0:���{�^��
     * 1:�E�{�^��
     * 2:�����{�^���i�z�C�[���{�^���j
     * 3:��4�{�^���i�T�C�h�{�^��1�j
     * 4:��5�{�^���i�T�C�h�{�^��2�j
     * 5~7:���g�p
     * @return true�F���̃{�^���͗����ꂽ����ł���^false�F�����ł͖���
     */
    virtual bool isReleasedUpButton(int prm_button_no);

    /**
     * �}�E�X�̃{�^���������ꂽ���ォ�ǂ����𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�(0~7)
     * 0:���{�^��
     * 1:�E�{�^��
     * 2:�����{�^���i�z�C�[���{�^���j
     * 3:��4�{�^���i�T�C�h�{�^��1�j
     * 4:��5�{�^���i�T�C�h�{�^��2�j
     * 5~7:���g�p
     * @return true�F���̃{�^���͗����ꂽ����ł���^false�F�����ł͖���
     */
    virtual bool isPushedDownButton(int prm_button_no);

    virtual ~MousePointerActor();
};

}
#endif /*GGAF_LIB_MOUSEPOINTERACTOR_H_*/

