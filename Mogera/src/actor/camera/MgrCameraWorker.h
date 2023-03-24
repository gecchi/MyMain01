#ifndef MGRCAMERAWORKER_H_
#define MGRCAMERAWORKER_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

namespace Mogera {

/**
 * �J�����}�� .
 * �J����(Mogera::MgrCamera)�ƁA���_(Mogera::MgrCameraViewPoint) �𑀂�A
 * ����� UP�̕����x�N�g�� pUp_ ���Ǘ����܂��B
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
