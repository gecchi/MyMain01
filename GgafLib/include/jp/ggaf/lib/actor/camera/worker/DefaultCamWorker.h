#ifndef GGAF_LIB_DEFAULTCAMWORKER_H_
#define GGAF_LIB_DEFAULTCAMWORKER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "CameraWorker.h"

namespace GgafLib {

/**
 * âΩÇ‡ÇµÇ»Ç¢ÉJÉÅÉâÉ}Éì .
 * @version 1.00
 * @since 2019/03/22
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:
    DefaultCamWorker(const char* prm_name, DefaultCamera* prm_pCamera,
            frame prm_slide_frames = 60, double prm_slide_p1 = 0.3, double prm_slide_p2 = 0.7);

    virtual void processBehavior() override;
    virtual ~DefaultCamWorker();
};

}
#endif /*GGAF_LIB_DEFAULTCAMWORKER_H_*/
