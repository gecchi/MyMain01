#ifndef DEFAULTCAMERA_H_
#define DEFAULTCAMERA_H_
namespace GgafLib {

/**
 * �J����.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCamera : public GgafDxCore::GgafDxCamera {

public:
    DefaultCamera(const char* prm_name, float prm_rad_fovX, float prm_dep);
    DefaultCamera(const char* prm_name, float prm_rad_fovX);
    DefaultCamera(const char* prm_name);

    virtual ~DefaultCamera(); //�f�X�g���N�^
};

}
#endif /*DEFAULTCAMERA_H_*/
