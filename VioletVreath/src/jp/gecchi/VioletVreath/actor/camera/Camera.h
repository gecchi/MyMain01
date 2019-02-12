#ifndef CAMERA_H_
#define CAMERA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace VioletVreath {

/**
 * �J����.
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

    virtual ~Camera(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
