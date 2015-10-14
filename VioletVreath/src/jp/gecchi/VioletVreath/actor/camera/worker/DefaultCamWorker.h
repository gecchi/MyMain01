#ifndef DEFAULTCAMWORKER_H_
#define DEFAULTCAMWORKER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * �������Ȃ��J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:
    DefaultCamWorker(const char* prm_name, Camera* prm_pCamera);
    virtual void processBehavior() override;
    virtual ~DefaultCamWorker(); //�f�X�g���N�^
};

}
#endif /*DEFAULTCAMWORKER_H_*/
