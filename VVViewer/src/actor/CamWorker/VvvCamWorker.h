#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

namespace VVViewer {

/**
 * VVViewer�̃J�����}�� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamWorker : public GgafLib::AroundViewCamWorker {

public:
    VvvCamWorker(const char* prm_name, VvvCamera* prm_pCamera);

    virtual ~VvvCamWorker(); //�f�X�g���N�^
};

}
#endif /*VVVCAMWORKER_H_*/
