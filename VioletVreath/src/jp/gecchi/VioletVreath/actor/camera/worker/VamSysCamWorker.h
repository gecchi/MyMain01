#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/CameraWorker.h"

#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

#define VAM_POS_ZRIGHT       DIR26( 0, 0,-1)
#define VAM_POS_ZRIGHT_UP    DIR26( 0,+1,-1)
#define VAM_POS_UP           DIR26( 0,+1, 0)
#define VAM_POS_ZLEFT_UP     DIR26( 0,+1,+1)
#define VAM_POS_ZLEFT        DIR26( 0, 0,+1)
#define VAM_POS_ZLEFT_DOWN   DIR26( 0,-1,+1)
#define VAM_POS_DOWN         DIR26( 0,-1, 0)
#define VAM_POS_ZRIGHT_DOWN  DIR26( 0,-1,-1)

#define VAM_POS_TO_BEHIND 10
#define VAM_POS_BEHIND_RIGHT 11
#define VAM_POS_BEHIND_LEFT 12
#define VAM_POS_BEHIND_TOP 13
#define VAM_POS_BEHIND_BOTTOM 14

namespace VioletVreath {

/**
 * VamSystemのカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

public:
    MyShip* pMyShip_;

    /** カメラY座標上限 */
    coord lim_CAM_top_;
    /** カメラY座標下限 */
    coord lim_CAM_bottom_;
    /** カメラX座標上限 */
    coord lim_CAM_infront_;
    /** カメラX座標下限 */
    coord lim_CAM_behaind_;
    /** カメラZ座標上限 */
    coord lim_CAM_zleft_;
    /** カメラZ座標下限 */
    coord lim_CAM_zright_;
    /** ビューポイントY座標上限 */
    coord lim_VP_top_;
    /** ビューポイントY座標下限 */
    coord lim_VP_bottom_;
    /** ビューポイントX座標上限 */
    coord lim_VP_infront_;
    /** ビューポイントX座標下限 */
    coord lim_VP_behaind_;
    /** ビューポイントZ座標上限 */
    coord lim_VP_zleft_;
    /** ビューポイントZ座標下限 */
    coord lim_VP_zright_;

    /** 画面背後時用Z軸補正範囲差分 */
    coord correction_width_;
    /** 画面背後時用Y軸補正範囲差分 */
    coord correction_height_;


    angle pos_cam_around_;
    angle pos_cam_around_base_;
    bool returnning_cam_pos_;
    frame returnning_cam_pos_frames_;
    bool cam_up_regular_;


    int pos_camera_;
    int pos_camera_prev_;
    int pos_camera_pressed_;
    coord dZ_camera_init_;
    coord dZ_camera_init_sqrt2_;
    frame cam_mv_frame_;
    frame cam_mv_frame_base_;
    coord mv_t_x_CAM_prev_, mv_t_y_CAM_prev_, mv_t_z_CAM_prev_;
public:
    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual ~VamSysCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
