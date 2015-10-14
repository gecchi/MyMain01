#ifndef TESTCAMWORKER_H_
#define TESTCAMWORKER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * 何もしないカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class TestCamWorker : public CameraWorker {

public:
    TestCamWorker(const char* prm_name, Camera* prm_pCamera);
    virtual void initialize() override {
    }

    void onSwitchCameraWork() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~TestCamWorker(); //デストラクタ
};

}
#endif /*TESTCAMWORKER_H_*/
