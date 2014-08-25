#ifndef SMPCAMERA_H_
#define SMPCAMERA_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

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
class SmpCamera : public GgafLib::DefaultCamera {

public:
    SmpCamera(const char* prm_name);

    virtual ~SmpCamera();
};

}
#endif /*SMPCAMERA_H_*/
