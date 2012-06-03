#ifndef DEFAULTCAMERA_H_
#define DEFAULTCAMERA_H_
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
#endif /*DEFAULTCAMERA_H_*/
