#ifndef GGAFLIB_CAMERAWORKER_H_
#define GGAFLIB_CAMERAWORKER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace GgafLib {

/**
 * カメラマン .
 * カメラ(VioletVreath::Camera)と、視点(VioletVreath::CameraViewPoint) を操り、
 * さらに UPの方向ベクトル pUp_ を管理します。
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

    /** [現カメラのUP要素ベクトルの面番号][視線の反対ベクトルの面番号] = 次の妥当なUP要素ベクトルの面番号(但しDIR26_NULLは移動不要を意味する)  関連テーブル */
    static int relation_up_vec_[3*3*3][3*3*3];
    /** relation_up_vec_アクセス用 */
    static int (*relation_up_by_vec_)[3*3*3];

private:
    /** 現在のカメラ→視点の方向番号 */
    dir26 vcv_dir_;
    /** 前回カメラ→視点の方向番号 */
    dir26 vcv_dir_prev_;

public:
    /** [r]カメラへの参照 */
    DefaultCamera* pCam_;
    /** [r]視点への参照 */
    DefaultCameraViewPoint* pVp_;
    /** [r]カメラの上方向の位置ベクトル */
    DefaultCameraUpVector*  pUp_;
    /** カメラマンの移動目標座標 */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** カメラマンのビューポイントの移動目標座標 */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** カメラマンの頭の方向目標番号 */
    dir26 t_cam_up_dir_;

    frame frame_of_behaving_since_onSwitch_;

public:
    CameraWorker(const char* prm_name, DefaultCamera* prm_pCamera);

    static bool initStatic();

    virtual void initialize() override;

    virtual void onActive() override;
    /**
     * スイッチされた場合に呼び出されるコールバック .
     * 今まで自身が非アクティブな CameraWorker だったが、
     * Spacetime::changeCameraWork() によりご指名が入った、
     * 又は Spacetime::undoCameraWork() 実行により復帰した、
     * ことにより、アクティブに切り替わった最初のフレームの
     * Spacetime::processBehavior() 内でコールバックされる。
     */
    virtual void onSwitchCameraWork();

    /**
     * 他の CameraWorker に切り替わる際のコールバック .
     * 今まで自身がアクティブな CameraWorker だったが、
     * Spacetime::changeCameraWork() 又は Spacetime::undoCameraWork() 実行により、
     * 他の CameraWorker に切り替わるので、次フレームから自身が非アクティブと
     * なってしまうという inactivate() が実行される直前に呼び出されるコールバック。
     */
    virtual void onChangedToOtherCameraWork();

    void targetAutoCamup();

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    inline frame getSwitchedFrame() {
        return frame_of_behaving_since_onSwitch_;
    }

    void slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t,
                      float prm_x_p1, float prm_y_p1, float prm_z_p1);
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t);
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                      float prm_x_p1, float prm_y_p1, float prm_z_p1);
    void mvCamTo(coord tx, coord ty, coord tz);

    bool isCamSliding();
    void slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t);

    void slideMvUpVecTo(coord tx, coord ty, coord tz, frame t);
    void slideMvUpVecTo(dir26 prm_up_dir_no, frame t);

    void setUpVec(coord tx, coord ty, coord tz);
//    void stopNaturallyCam(coord distance, frame t);
//    void stopNaturallyVp(coord distance, frame t);

    void stopMvCam();
    void stopMvVp();
//    void behaveAutoCamUp();
    virtual ~CameraWorker(); //デストラクタ
};

}
#endif /*CAMERAWORKER_H_*/
