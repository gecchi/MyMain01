#ifndef MYSHIPDIVINGCAMWORKER_H_
#define MYSHIPDIVINGCAMWORKER_H_

namespace MyStg2nd {

/**
 * ステージ突入時のカメラマン .
 * @version 1.00
 * @since 2010/11/11
 * @author Masatoshi Tsuge
 */
class MyShipDivingCamWorker : public CameraWorker {

public:
    MyShip* _pMyShip;

    /** 原点から初期カメラZ位置の距離 */
    int _dZ_camera_init;
    //カメラの移動目標座標
    int _move_target_X_CAM, _move_target_Y_CAM, _move_target_Z_CAM;
    //カメラのビューポイントの移動目標座標
    int _move_target_X_VP, _move_target_Y_VP, _move_target_Z_VP;
    //カメラの目標UPアングル値
    angle _move_target_XY_CAM_UP;
    angle _angXY_nowCamUp;

    /** カメラの最高速度（上限、負数で下限） */
    int _cam_velo_renge;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
    int _stop_renge; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超


    MyShipDivingCamWorker(const char* prm_name);

    virtual void initialize() override;



    virtual void onPushed() override {
    }

    virtual void onPoped() override {
    }

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    void setMoveTargetCamBy(GgafDx9Core::GgafDx9GeometricActor* pTarget);
    void setMoveTargetCamVpBy(GgafDx9Core::GgafDx9GeometricActor* pTarget);
    void setMoveTargetCam(int X, int Y, int Z);
    void setMoveTargetCamVp(int X, int Y, int Z);

    virtual ~MyShipDivingCamWorker(); //デストラクタ
};

}
#endif /*MYSHIPDIVINGCAMWORKER_H_*/
