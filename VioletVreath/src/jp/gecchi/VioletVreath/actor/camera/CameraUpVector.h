#ifndef CAMERAUPVECTOR_H_
#define CAMERAUPVECTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

namespace VioletVreath {

/**
 * カメラの上の位置ベクトル .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class CameraUpVector : public GgafLib::DefaultCameraUpVector {

public:
    CameraUpVector(const char* prm_name);

    virtual ~CameraUpVector();
};


}
#endif /*CAMERAUPVECTOR_H_*/
