#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace VioletVreath {

/**
 * カメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

public:
    /** カメラ位置番号 */
    int pos_camera_;

    GgafDxCore::GgafDxGeometricActor* pLockOnTarget_;

    /** 原点から初期カメラZ位置の距離 */
    coord dZ_camera_init_;
    //カメラの移動目標座標
    coord move_target_x_CAM_, move_target_y_CAM_, move_target_z_CAM_;
    //カメラのビューポイントの移動目標座標
    coord move_target_x_VP_, move_target_y_VP_, move_target_z_VP_;
    //カメラの目標UPアングル値
    angle move_target_XY_CAM_UP_;
    angle angXY_nowCamUp_;

    /** カメラの最高速度（上限、負数で下限） */
    velo cam_velo_renge_;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
    coord stop_renge_; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超

    /** 等速でブレないスピード */
    velo burenai_speed_;

    frame frame_of_behaving_since_onSwitch_;

public:
    CameraWorker(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void onSwitchCameraWork();

    virtual void onUndoCameraWork();

    virtual void onSwitchToOtherCameraWork();

    virtual void onCameBackFromOtherCameraWork();

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }


    void setMoveTargetCamBy(GgafDxCore::GgafDxGeometricActor* pTarget);
    void setMoveTargetCamVpBy(GgafDxCore::GgafDxGeometricActor* pTarget);
    void setMoveTargetCam(coord X, coord Y, coord Z);
    void setMoveTargetCamVp(coord X, coord Y, coord Z);
    void lockCamVp(GgafDxCore::GgafDxGeometricActor* pTarget);

    void unlockCamVp();

    inline frame getSwitchedFrame() {
        return frame_of_behaving_since_onSwitch_;
    }
    virtual ~CameraWorker(); //デストラクタ
};

}
#endif /*CAMERAWORKER_H_*/
