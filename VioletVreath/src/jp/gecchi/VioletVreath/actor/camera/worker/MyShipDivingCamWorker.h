#ifndef MYSHIPDIVINGCAMWORKER_H_
#define MYSHIPDIVINGCAMWORKER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * ステージ突入時のカメラマン .
 * @version 1.00
 * @since 2010/11/11
 * @author Masatoshi Tsuge
 */
class MyShipDivingCamWorker : public CameraWorker {

public:
    MyShipDivingCamWorker(const char* prm_name, Camera* prm_pCamera);

    virtual void initialize() override;
    virtual void onActive() override;
    virtual void processBehavior() override;

    virtual ~MyShipDivingCamWorker();
};

}
#endif /*MYSHIPDIVINGCAMWORKER_H_*/
