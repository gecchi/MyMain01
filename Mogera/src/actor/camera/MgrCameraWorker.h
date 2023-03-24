#ifndef MGRCAMERAWORKER_H_
#define MGRCAMERAWORKER_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

namespace Mogera {

/**
 * カメラマン .
 * カメラ(Mogera::MgrCamera)と、視点(Mogera::MgrCameraViewPoint) を操り、
 * さらに UPの方向ベクトル pUp_ を管理します。
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MgrCameraWorker : public GgafLib::AroundViewCamWorker {

public:
    MgrCameraWorker(const char* prm_name, MgrCamera* prm_pCamera);

    virtual ~MgrCameraWorker();
};

}
#endif /*MGRCAMERAWORKER_H_*/
