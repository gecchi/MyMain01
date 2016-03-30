#ifndef CAMERAVIEWPOINT_H_
#define CAMERAVIEWPOINT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

namespace VioletVreath {

/**
 * 視点.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class CameraViewPoint : public GgafLib::DefaultCameraViewPoint {

public:
    CameraViewPoint(const char* prm_name);

    virtual ~CameraViewPoint(); //デストラクタ
};

}
#endif /*CAMERAVIEWPOINT_H_*/
