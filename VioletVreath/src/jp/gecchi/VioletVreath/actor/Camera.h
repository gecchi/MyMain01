#ifndef CAMERA_H_
#define CAMERA_H_


namespace VioletVreath {

/**
 * �J����.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class Camera : public GgafLib::DefaultCamera {

public:

    Camera(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~Camera(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
