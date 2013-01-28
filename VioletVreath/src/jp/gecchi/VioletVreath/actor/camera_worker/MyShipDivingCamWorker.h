#ifndef MYSHIPDIVINGCAMWORKER_H_
#define MYSHIPDIVINGCAMWORKER_H_

namespace VioletVreath {

/**
 * ステージ突入時のカメラマン .
 * @version 1.00
 * @since 2010/11/11
 * @author Masatoshi Tsuge
 */
class MyShipDivingCamWorker : public CameraWorker {

public:
    MyShipDivingCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual ~MyShipDivingCamWorker();
};

}
#endif /*MYSHIPDIVINGCAMWORKER_H_*/
