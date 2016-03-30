#ifndef CAMERAUPVECTOR_H_
#define CAMERAUPVECTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

namespace VioletVreath {

/**
 * �J�����̏�̈ʒu�x�N�g�� .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class CameraUpVector : public GgafLib::DefaultCameraUpVector {

public:
    CameraUpVector(const char* prm_name);

    virtual ~CameraUpVector(); //�f�X�g���N�^
};


}
#endif /*CAMERAUPVECTOR_H_*/
