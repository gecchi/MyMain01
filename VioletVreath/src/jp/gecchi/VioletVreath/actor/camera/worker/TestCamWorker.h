#ifndef TESTCAMWORKER_H_
#define TESTCAMWORKER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * âΩÇ‡ÇµÇ»Ç¢ÉJÉÅÉâÉ}Éì .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class TestCamWorker : public GgafLib::CameraWorker {

public:
    TestCamWorker(const char* prm_name, Camera* prm_pCamera);
    virtual void initialize() override {
    }

    void onSwitchCameraWork() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~TestCamWorker();
};

}
#endif /*TESTCAMWORKER_H_*/
