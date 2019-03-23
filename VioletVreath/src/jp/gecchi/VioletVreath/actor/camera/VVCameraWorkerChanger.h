#ifndef VVCAMERAWORKERCHANGER_H_
#define VVCAMERAWORKERCHANGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/CameraWorkerChanger.h"

namespace VioletVreath {

#define CAM_WORKER_HISTORY_NUM (30)

/**
 * �J�����}���`�F���W���[ .
 * @version 1.00
 * @since 2019/03/2
 * @author Masatoshi Tsuge
 */
class VVCameraWorkerChanger : public GgafLib::CameraWorkerChanger {

public:
    VVCameraWorkerChanger(const char* prm_name, Camera* prm_pCamera);

    virtual GgafLib::CameraWorker* createCameraWorker(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~VVCameraWorkerChanger(); //�f�X�g���N�^
};

}
#endif /*VVCAMERAWORKERCHANGER_H_*/
