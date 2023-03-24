#ifndef CAMERA_H_
#define CAMERA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace VioletVreath {

/**
 * ÉJÉÅÉâ.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class Camera : public GgafLib::DefaultCamera {

public:
    Camera(const char* prm_name);

    virtual void processBehavior() override;

    GgafDx::CameraViewPoint* createCameraViewPoint() override;

    GgafDx::CameraUpVector* createCameraUpVector() override;

    virtual ~Camera();
};

}
#endif /*CAMERA_H_*/
