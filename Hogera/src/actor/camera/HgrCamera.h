#ifndef HGRCAMERA_H_
#define HGRCAMERA_H_
#include "Hogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace Hogera {

/**
 * カメラの雛形 .
 * カメラクラスは本コードのように GgafLib::DefaultHgrCamera を
 * 継承して作成して下さい。<BR>
 * 「この世」を作成する際に、引数でカメラが必要です。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrCamera : public GgafLib::DefaultCamera {

public:

    HgrCamera(const char* prm_name);

    virtual ~HgrCamera();
};

}
#endif /*HGRCAMERA_H_*/
