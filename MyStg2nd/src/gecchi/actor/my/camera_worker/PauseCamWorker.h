#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_


namespace MyStg2nd {

/**
 * 一時停止時のカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class PauseCamWorker : public CameraWorker {

public:
    PauseCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void onSwitchedCameraWork() override {
    }

    virtual void onUndoneCameraWork() override {
    }

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    virtual ~PauseCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
