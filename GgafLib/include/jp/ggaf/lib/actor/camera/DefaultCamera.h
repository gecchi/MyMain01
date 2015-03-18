#ifndef GGAFLIB_DEFAULTCAMERA_H_
#define GGAFLIB_DEFAULTCAMERA_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"

namespace GgafLib {

/**
 * 標準のカメラ.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCamera : public GgafDxCore::GgafDxCamera {

public:
    DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep);
    DefaultCamera(const char* prm_name, double prm_rad_fovX);
    DefaultCamera(const char* prm_name);

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    virtual GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;

    virtual ~DefaultCamera(); //デストラクタ
};

}
#endif /*GGAFLIB_DEFAULTCAMERA_H_*/
