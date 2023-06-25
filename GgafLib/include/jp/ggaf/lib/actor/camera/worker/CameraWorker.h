#ifndef GGAF_LIB_CAMERAWORKER_H_
#define GGAF_LIB_CAMERAWORKER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafLib {

/**
 * カメラマン .
 * カメラ(VioletVreath::Camera)と、視点(VioletVreath::CameraViewPoint)、 UPの方向ベクトル pUp_ を管理します。
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::MainActor {

public:
    /** [r]カメラへの参照 */
    DefaultCamera* _pCam;
    /** [r]視点への参照 */
    DefaultCameraViewPoint* _pVp;
    /** [r]カメラの上方向の位置ベクトル */
    DefaultCameraUpVector*  _pUp;
    /** カメラマンの移動目標座標 */
    coord _t_x_CAM, _t_y_CAM, _t_z_CAM;
    /** カメラマンのビューポイントの移動目標座標 */
    coord _t_x_VP, _t_y_VP, _t_z_VP;
    /** UPベクトル目標 */
    coord _t_x_UP, _t_y_UP, _t_z_UP;

    frame _frame_of_behaving_since_onSwitch;

    frame _slide_frames;
    double _slide_p1;
    double _slide_p2;

public:
    CameraWorker(const char* prm_name, DefaultCamera* prm_pCamera,
                 frame prm_slide_frames, double prm_slide_p1, double prm_slide_p2);

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

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    inline frame getSwitchedFrame() {
        return _frame_of_behaving_since_onSwitch;
    }
    void slideMvCamTo(GgafDx::GeometricActor* pTarget) {
        slideMvCamTo(pTarget, _slide_frames);
    }
    void slideMvCamTo(GgafDx::GeometricActor* pTarget, frame t);
    void slideMvCamTo(GgafDx::GeometricActor* pTarget, frame t,
                      double prm_x_p1, double prm_y_p1, double prm_z_p1);

    void slideMvCamTo(coord tx, coord ty, coord tz) {
        slideMvCamTo(tx,ty,tz,_slide_frames);
    }
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t) {
        slideMvCamTo(tx,ty,tz,t,_slide_p1, _slide_p2);
    }
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2);

    void slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                      double prm_x_p1, double prm_y_p1, double prm_z_p1);

    void mvCamTo(coord tx, coord ty, coord tz);

    bool isCamSliding();

    void slideMvVpTo(GgafDx::GeometricActor* pTarget){
        slideMvVpTo(pTarget, _slide_frames);
    }
    void slideMvVpTo(GgafDx::GeometricActor* pTarget, frame t){
        slideMvVpTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
    }
    void slideMvVpTo(coord tx, coord ty, coord tz) {
        slideMvVpTo(tx, ty, tz, _slide_frames);
    }
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t) {
        slideMvVpTo(tx, ty, tz, t, _slide_p1, _slide_p2);
    }
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2);


    void slideMvUpVecTo(coord tx, coord ty, coord tz) {
        slideMvUpVecTo(tx,ty,tz,_slide_frames);
    }
    void slideMvUpVecTo(coord tx, coord ty, coord tz, frame t) {
        slideMvUpVecTo(tx,ty,tz,t,_slide_p1, _slide_p2);
    }
    void slideMvUpVecTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2);


    void setUpVec(coord tx, coord ty, coord tz);

    void stopMvCam();
    void stopMvVp();

    virtual ~CameraWorker();
};

}
#endif /*CAMERAWORKER_H_*/
