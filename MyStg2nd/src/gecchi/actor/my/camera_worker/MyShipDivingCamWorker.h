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
//    MyShip* _pMyShip;


    MyShipDivingCamWorker(const char* prm_name);

    virtual void initialize() override;




    virtual void onSwitchedCameraWork() override;

    virtual void onUndoneCameraWork() override;



    virtual ~MyShipDivingCamWorker(); //デストラクタ
};

}
#endif /*MYSHIPDIVINGCAMWORKER_H_*/
