#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * 一時停止時のカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class PauseCamWorker : public CameraWorker {

public:
    ViewPointGuide* pVPGuide_;
    int cd_;
    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;

public:
    PauseCamWorker(const char* prm_name, Camera* prm_pCamera);

    virtual void initialize() override;

    virtual void onActive() override;
    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~PauseCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
