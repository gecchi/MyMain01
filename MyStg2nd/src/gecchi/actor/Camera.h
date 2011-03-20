#ifndef CAMERA_H_
#define CAMERA_H_


namespace MyStg2nd {

/**
 * カメラ.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class Camera : public GgafDx9LibStg::DefaultCamera {

public:

    Camera(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~Camera(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
