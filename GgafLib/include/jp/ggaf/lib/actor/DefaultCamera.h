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
    DefaultCamera(const char* prm_name, float prm_rad_fovX, float prm_dep);

    virtual ~DefaultCamera(); //デストラクタ
};

}
#endif /*DEFAULTCAMERA_H_*/
