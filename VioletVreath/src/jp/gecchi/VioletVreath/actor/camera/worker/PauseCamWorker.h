#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

namespace VioletVreath {

/**
 * �ꎞ��~���̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class PauseCamWorker : public GgafLib::AroundViewCamWorker {

public:
//    ViewPointGuide* pVPGuide_;

public:
    PauseCamWorker(const char* prm_name, Camera* prm_pCamera);

    virtual ~PauseCamWorker(); //�f�X�g���N�^
};

}
#endif /*PAUSECAMWORKER_H_*/
