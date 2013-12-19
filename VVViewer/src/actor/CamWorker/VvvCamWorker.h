#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

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

    int cam_x_, cam_y_, cam_z_, vp_x_, vp_y_, vp_z_;

    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;
    /** 原点から初期カメラZ位置の距離 */
    coord dZ_camera_init_;
    //カメラの移動目標座標
    coord move_target_x_CAM_, move_target_y_CAM_, move_target_z_CAM_;
    //カメラのビューポイントの移動目標座標
    coord move_target_x_VP_, move_target_y_VP_, move_target_z_VP_;
    //カメラの目標UPアングル値
    angle move_target_ZY_CAM_UP_;
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
