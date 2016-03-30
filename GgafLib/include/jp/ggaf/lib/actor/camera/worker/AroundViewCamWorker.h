#ifndef GGAFLIB_AROUNDVIEWCAMWORKER_H_
#define GGAFLIB_AROUNDVIEWCAMWORKER_H_
#include "GgafLibCommonHeader.h"
#include "CameraWorker.h"

namespace GgafLib {

/**
 * 一時停止時のカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class AroundViewCamWorker : public CameraWorker {

public:
    int cd_;
    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;

public:
    AroundViewCamWorker(const char* prm_name, DefaultCamera* prm_pCamera);

    virtual void initialize() override;

    virtual void onActive() override;
    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~AroundViewCamWorker(); //デストラクタ
};

}
#endif /*GGAFLIB_AROUNDVIEWCAMWORKER_H_*/
