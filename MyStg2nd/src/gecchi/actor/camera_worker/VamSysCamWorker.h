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

namespace MyStg2nd {

/**
 * VamSystemのカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

public:
    MyShip* _pMyShip;

    /** 原点から初期カメラZ位置の距離 */
//    int _dZ_camera_init;

    /** カメラY座標上限 */
    appcoord _lim_CAM_top;
    /** カメラY座標下限 */
    appcoord _lim_CAM_bottom;
    /** カメラX座標上限 */
    appcoord _lim_CAM_front;
    /** カメラX座標下限 */
    appcoord _lim_CAM_behaind;
    /** カメラZ座標上限 */
    appcoord _lim_CAM_zleft;
    /** カメラZ座標下限 */
    appcoord _lim_CAM_zright;
    /** ビューポイントY座標上限 */
    appcoord _lim_VP_top;
    /** ビューポイントY座標下限 */
    appcoord _lim_VP_bottom;
    /** ビューポイントX座標上限 */
    appcoord _lim_VP_front;
    /** ビューポイントX座標下限 */
    appcoord _lim_VP_behaind;
    /** ビューポイントZ座標上限 */
    appcoord _lim_VP_zleft;
    /** ビューポイントZ座標下限 */
    appcoord _lim_VP_zright;

//    /** 現在のカメラのUPのアングル値 */
//    appangle _angXY_nowCamUp;
    /** 画面背後時用Z軸補正範囲差分 */
    appcoord _correction_width;
    /** 画面背後時用Y軸補正範囲差分 */
    appcoord _correction_height;
    /** カメラの最高速度（上限、負数で下限） */
//    int _cam_velo_renge;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
//    int _stop_renge; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
//                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超
    /** カメラ目標座標に加えられるZ軸座標オフセット補正値 */
    appcoord _stop_dZ;
    /** カメラ目標座標に加えられるY軸座標オフセット補正値 */
    appcoord _stop_dY;


    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual ~VamSysCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
