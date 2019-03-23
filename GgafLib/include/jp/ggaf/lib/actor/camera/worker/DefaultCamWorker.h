#ifndef GGAF_LIB_DEFAULTCAMWORKER_H_
#define GGAF_LIB_DEFAULTCAMWORKER_H_
#include "GgafLibCommonHeader.h"
#include "CameraWorker.h"

namespace GgafLib {

/**
 * �������Ȃ��J�����}�� .
 * @version 1.00
 * @since 2019/03/22
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:
    DefaultCamWorker(const char* prm_name, DefaultCamera* prm_pCamera);
    virtual void processBehavior() override;
    virtual ~DefaultCamWorker();
};

}
#endif /*GGAF_LIB_DEFAULTCAMWORKER_H_*/
