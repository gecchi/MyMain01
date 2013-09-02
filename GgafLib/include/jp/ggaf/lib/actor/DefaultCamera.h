#ifndef GGAFLIB_DEFAULTCAMERA_H_
#define GGAFLIB_DEFAULTCAMERA_H_
#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"

namespace GgafLib {

/**
 * カメラ.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCamera : public GgafDxCore::GgafDxCamera {

public:
    DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep);
    DefaultCamera(const char* prm_name, double prm_rad_fovX);
    DefaultCamera(const char* prm_name);

    virtual ~DefaultCamera(); //デストラクタ
};

}
#endif /*GGAFLIB_DEFAULTCAMERA_H_*/
