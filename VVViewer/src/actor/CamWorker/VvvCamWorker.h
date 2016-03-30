#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

namespace VVViewer {

/**
 * VVViewerのカメラマン .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamWorker : public GgafLib::AroundViewCamWorker {

public:
    VvvCamWorker(const char* prm_name, VvvCamera* prm_pCamera);

    virtual ~VvvCamWorker(); //デストラクタ
};

}
#endif /*VVVCAMWORKER_H_*/
