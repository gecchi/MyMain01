#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_


namespace VVViewer {

/**
 * VVViewerのカメラマン .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamWorker : public GgafLib::DefaultGeometricActor {

public:
    int cd_;

    int cam_X_, cam_Y_, cam_Z_, vp_X_, vp_Y_, vp_Z_;

    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;
    /** 原点から初期カメラZ位置の距離 */
    coord dZ_camera_init_;
    //カメラの移動目標座標
    coord move_target_X_CAM_, move_target_Y_CAM_, move_target_Z_CAM_;
    //カメラのビューポイントの移動目標座標
    coord move_target_X_VP_, move_target_Y_VP_, move_target_Z_VP_;
    //カメラの目標UPアングル値
    angle move_target_XY_CAM_UP_;
    angle angXY_nowCamUp_;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
    coord stop_renge_; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超
public:
    VvvCamWorker(const char* prm_name);

    virtual void initialize() override;


    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~VvvCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
