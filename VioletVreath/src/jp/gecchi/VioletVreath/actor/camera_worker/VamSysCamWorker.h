#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_

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
    /** 原点から初期カメラZ位置の距離 */
//    int dZ_camera_init_;

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

//    /** 現在のカメラのUPのアングル値 */
//    angle angXY_nowCamUp_;
    /** 画面背後時用Z軸補正範囲差分 */
    coord correction_width_;
    /** 画面背後時用Y軸補正範囲差分 */
    coord correction_height_;
    /** カメラの最高速度（上限、負数で下限） */
//    int cam_velo_renge_;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
//    int stop_renge_; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
//                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超
    /** カメラ目標座標に加えられるZ軸座標オフセット補正値 */
    coord stop_dZ_;
    /** カメラ目標座標に加えられるY軸座標オフセット補正値 */
    coord stop_dY_;
    /** カメラはオプション背面中である場合true */
    bool is_cam_pos_option_back_;

public:
    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual ~VamSysCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
