#ifndef CAMERA_H_
#define CAMERA_H_
namespace MyStg2nd {

/**
 * �J����.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class Camera : public GgafDx9LibStg::DefaultCamera {

public:
    Camera(const char* prm_name, float prm_rad_fovX, float prm_dep);

    virtual ~Camera(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
