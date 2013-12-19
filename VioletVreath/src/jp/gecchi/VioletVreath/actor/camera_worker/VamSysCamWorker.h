#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_
#include "jp/gecchi/VioletVreath/actor/camera_worker/CameraWorker.h"

#define VAM_POS_RIGHT 1
#define VAM_POS_LEFT 2
#define VAM_POS_TOP 3
#define VAM_POS_BOTTOM 4
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
    coord lim_CAM_front_;
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
    coord lim_VP_front_;
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
    /** カメラ目標座標に加えられるZ軸座標オフセット補正値 */
    coord stop_dZ_;
    /** カメラ目標座標に加えられるY軸座標オフセット補正値 */
    coord stop_dY_;
    /** カメラはオプション背面中である場合true */
    bool is_cam_pos_option_back_;

    int pos_camera_;
    int pos_camera_prev_;
    coord dZ_camera_init_;
    int target_up_face_no_prev_;

    coord move_target_x_CAM_prev_, move_target_y_CAM_prev_, move_target_z_CAM_prev_;
    //カメラのビューポイントの移動目標座標
    coord move_target_x_VP_prev_, move_target_y_VP_prev_, move_target_z_VP_prev_;
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
