#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"


#define VAM_POS_BEHIND              DIR26(-1, 0, 0)
#define VAM_POS_BEHIND_ZRIGHT       DIR26(-1, 0,-1)
#define VAM_POS_BEHIND_ZRIGHT_UP    DIR26(-1,+1,-1)
#define VAM_POS_BEHIND_UP           DIR26(-1,+1, 0)
#define VAM_POS_BEHIND_ZLEFT_UP     DIR26(-1,+1,+1)
#define VAM_POS_BEHIND_ZLEFT        DIR26(-1, 0,+1)
#define VAM_POS_BEHIND_ZLEFT_DOWN   DIR26(-1,-1,+1)
#define VAM_POS_BEHIND_DOWN         DIR26(-1,-1, 0)
#define VAM_POS_BEHIND_ZRIGHT_DOWN  DIR26(-1,-1,-1)

#define VAM_POS_NON                 DIR26( 0, 0, 0)
#define VAM_POS_ZRIGHT              DIR26( 0, 0,-1)
#define VAM_POS_ZRIGHT_UP           DIR26( 0,+1,-1)
#define VAM_POS_UP                  DIR26( 0,+1, 0)
#define VAM_POS_ZLEFT_UP            DIR26( 0,+1,+1)
#define VAM_POS_ZLEFT               DIR26( 0, 0,+1)
#define VAM_POS_ZLEFT_DOWN          DIR26( 0,-1,+1)
#define VAM_POS_DOWN                DIR26( 0,-1, 0)
#define VAM_POS_ZRIGHT_DOWN         DIR26( 0,-1,-1)

#define VAM_POS_FRONT               DIR26(+1, 0, 0)
#define VAM_POS_FRONT_ZRIGHT        DIR26(+1, 0,-1)
#define VAM_POS_FRONT_ZRIGHT_UP     DIR26(+1,+1,-1)
#define VAM_POS_FRONT_UP            DIR26(+1,+1, 0)
#define VAM_POS_FRONT_ZLEFT_UP      DIR26(+1,+1,+1)
#define VAM_POS_FRONT_ZLEFT         DIR26(+1, 0,+1)
#define VAM_POS_FRONT_ZLEFT_DOWN    DIR26(+1,-1,+1)
#define VAM_POS_FRONT_DOWN          DIR26(+1,-1, 0)
#define VAM_POS_FRONT_ZRIGHT_DOWN   DIR26(+1,-1,-1)

namespace VioletVreath {

/**
 * VamSystemのカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public GgafLib::CameraWorker {

    /** [r/w]自機に対してYZ平面に平行で回っているカメラのアングル位置 */
    angle ang_cam_around_;
    /** [r]ang_cam_around_ の初期アングル位置 */
    angle ang_cam_around_base_;
    /** [r]ang_cam_around_が、元のang_cam_around_base_に自動戻り中に、true */
    bool returning_cam_pos_;
    /** [r]ang_cam_around_が、元のang_cam_around_base_に自動戻り費やす時間(フレーム) */
    frame returning_cam_pos_frames_;
    /** [r]ang_cam_around_ を８方向の定数で表した方向値(VAM_POS_XXXXX が入る) */
    dir26 pos_camera_;
    /** [r]pos_camera_の１フレーム前の方向値(VAM_POS_XXXXX) */
    dir26 pos_camera_prev_;
    /** [r]カメラの８方向位置が切り替わった（pos_camera_の値が変化した）ならばtrue */
    bool is_just_changed_pos_cam_;
    /** [r/w]カメラがなめらか移動に費やすフレーム数 */
    frame cam_mv_frame_;
    /** [r]カメラがなめらか移動に費やすフレーム数の標準値 */
    frame cam_mv_frame_base_;

    coord DZC_;
    coord DXC_;
    coord DX2_C_;
    coord X_P_C_;

public:
    MyShip* pMyShip_;
    GgafDxCore::GgafDxSeTransmitter* pSe_;

public:
    VamSysCamWorker(const char* prm_name, Camera* prm_pCamera);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    inline dir26 getPosCam() {
        return pos_camera_;
    }
    inline bool isJustChangedPosCam() {
        return is_just_changed_pos_cam_;
    }
    virtual void onSwitchCameraWork() override;


    virtual ~VamSysCamWorker(); //デストラクタ
};

}
#endif /*VAMSYSCAMWORKER_H_*/

