#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_
#include "Mogera.h"
#include "MgrCameraWorker.h"

namespace Mogera {

/**
 * 一時停止時のカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MgrMouseCamWorker : public MgrCameraWorker {

public:
    int cd_;
    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;

public:
    MgrMouseCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;
    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~MgrMouseCamWorker(); //デストラクタ
};

}
#endif /*MGRCAMERA_H_*/
