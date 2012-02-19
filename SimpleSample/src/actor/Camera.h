#ifndef CAMERA_H_
#define CAMERA_H_
namespace SimpleSample {

/**
 * カメラの雛形 .
 * カメラクラスは本コードのように GgafLib::DefaultCamera を
 * 継承して作成して下さい。<BR>
 * 「この世」を作成する際に、引数でカメラが必要です。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class Camera : public GgafLib::DefaultCamera {

public:
    Camera(const char* prm_name);

    virtual ~Camera();
};

}
#endif /*CAMERA_H_*/
