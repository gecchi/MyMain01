#ifndef VVVCAMERAUPVECTOR_H_
#define VVVCAMERAUPVECTOR_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

namespace VVViewer {

/**
 * 視点.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class VvvCameraUpVector : public GgafLib::DefaultCameraUpVector {

public:
    VvvCameraUpVector(const char* prm_name);

    virtual ~VvvCameraUpVector(); //デストラクタ
};


}
#endif /*VVVCAMERAUPVECTOR_H_*/
