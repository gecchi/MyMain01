#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_



namespace MyStg2nd {

/**
 * カメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

public:
    /** カメラ位置番号 */
    int _pos_camera;

    GgafDx9Core::GgafDx9GeometricActor* _pLockOnTarget;

    /** 原点から初期カメラZ位置の距離 */
    appcoord _dZ_camera_init;
    //カメラの移動目標座標
    appcoord _move_target_X_CAM, _move_target_Y_CAM, _move_target_Z_CAM;
    //カメラのビューポイントの移動目標座標
    appcoord _move_target_X_VP, _move_target_Y_VP, _move_target_Z_VP;
    //カメラの目標UPアングル値
    appangle _move_target_XY_CAM_UP;
    appangle _angXY_nowCamUp;

    /** カメラの最高速度（上限、負数で下限） */
    velo _cam_velo_renge;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
    appcoord _stop_renge; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超

    /** 等速でブレないスピード */
    velo _burenai_speed;

    CameraWorker(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void onSwitchCameraWork();

    virtual void onUndoCameraWork();

    virtual void onSwitchToOherCameraWork();

    virtual void onCameBackFromOtherCameraWork();



    virtual void processBehavior() override;

    virtual void processJudgement() override {

    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }


    void setMoveTargetCamBy(GgafDx9Core::GgafDx9GeometricActor* pTarget);
    void setMoveTargetCamVpBy(GgafDx9Core::GgafDx9GeometricActor* pTarget);
    void setMoveTargetCam(appcoord X, appcoord Y, appcoord Z);
    void setMoveTargetCamVp(appcoord X, appcoord Y, appcoord Z);
    void lockCamVp(GgafDx9Core::GgafDx9GeometricActor* pTarget);

    void unlockCamVp();
    virtual ~CameraWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
