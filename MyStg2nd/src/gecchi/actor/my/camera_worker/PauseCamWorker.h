#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_


namespace MyStg2nd {

/**
 * �ꎞ��~���̃J�����}�� .
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
    virtual ~PauseCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
