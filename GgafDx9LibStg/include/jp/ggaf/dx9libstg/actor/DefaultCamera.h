#ifndef DEFAULTCAMERA_H_
#define DEFAULTCAMERA_H_
namespace GgafDx9LibStg {

/**
 * �J����.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class DefaultCamera : public GgafDx9Core::GgafDx9Camera {

public:
    DefaultCamera(const char* prm_name, float prm_rad_fovX, float prm_dep);

    virtual ~DefaultCamera(); //�f�X�g���N�^
};

}
#endif /*DEFAULTCAMERA_H_*/
