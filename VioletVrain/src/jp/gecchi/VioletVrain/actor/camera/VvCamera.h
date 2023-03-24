#ifndef VVCAMERA_H_
#define VVCAMERA_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace VioletVrain {

/**
 * カメラの雛形 .
 * カメラクラスは本コードのように GgafLib::DefaultVvCamera を
 * 継承して作成して下さい。<BR>
 * 「この世」を作成する際に、引数でカメラが必要です。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvCamera : public GgafLib::DefaultCamera {

public:

    VvCamera(const char* prm_name);

    virtual ~VvCamera();
};

}
#endif /*VVCAMERA_H_*/
