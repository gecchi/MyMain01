#ifndef VVVCAMERA_H_
#define VVVCAMERA_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace VVViewer {

/**
 * VVViewerÇÃÉJÉÅÉâ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamera : public GgafLib::DefaultCamera {
public:
    VvvCamera(const char* prm_name);

    GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;
    GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    virtual ~VvvCamera();
};

}
#endif /*VVVCAMERAH_*/
