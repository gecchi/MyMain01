#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace VioletVreath {

/**
 * カメラマン .
 * VioletVreath::Camera, VioletVreath::ViewPoint, さらに UPの方向ベクトル pUp_ を管理。
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

public:
    Camera* pCam_;
    ViewPoint* pVp_;
    GgafLib::DefaultGeometricActor* pUp_;
    GgafDxCore::GgafDxAxesMover* pAxsMver_Up_;
    /** カメラマンの移動目標座標 */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** カメラマンのビューポイントの移動目標座標 */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** カメラマンの頭の方向番号 */
    int t_cam_up_face_;
    frame frame_of_behaving_since_onSwitch_;
public:
    CameraWorker(const char* prm_name);

    virtual void initialize() override;
    virtual void onActive() override;
    /**
     * スイッチされた場合に呼び出されるコールバック
     */
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

//
//    void unlockCamVp();

    inline frame getSwitchedFrame() {
        return frame_of_behaving_since_onSwitch_;
    }

    void slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t);
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t);


    virtual ~CameraWorker(); //デストラクタ
};

}
#endif /*CAMERAWORKER_H_*/
