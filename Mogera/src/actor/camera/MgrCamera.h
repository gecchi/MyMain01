#ifndef MGRCAMERA_H_
#define MGRCAMERA_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace Mogera {

/**
 * カメラの雛形 .
 * カメラクラスは本コードのように GgafLib::DefaultMgrCamera を
 * 継承して作成して下さい。<BR>
 * 「この世」を作成する際に、引数でカメラが必要です。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrCamera : public GgafLib::DefaultCamera {

public:

    MgrCamera(const char* prm_name);

    GgafDx::CameraViewPoint* createCameraViewPoint() override;

    GgafDx::CameraUpVector* createCameraUpVector() override;

    virtual ~MgrCamera();
};

}
#endif /*MGRCAMERA_H_*/
