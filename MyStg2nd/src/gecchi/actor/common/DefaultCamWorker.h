#ifndef DEFAULTCAMWORKER_H_
#define DEFAULTCAMWORKER_H_


namespace MyStg2nd {

/**
 * 何もしないカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:

    DefaultCamWorker(const char* prm_name);

    virtual void onSwitchedCameraWork() override {
    }

    virtual void onUndoneCameraWork() override {
    }

    virtual ~DefaultCamWorker(); //デストラクタ
};

}
#endif /*DEFAULTCAMWORKER_H_*/
