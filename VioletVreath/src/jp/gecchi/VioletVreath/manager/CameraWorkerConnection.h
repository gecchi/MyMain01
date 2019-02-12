#ifndef CAMERAWORKERCONNECTION_H_
#define CAMERAWORKERCONNECTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * CameraWorker�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class CameraWorkerConnection : public GgafCore::ResourceConnection<GgafLib::CameraWorker> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pCamWorker �f�|�W�g��
     */
    CameraWorkerConnection(const char* prm_idstr, GgafLib::CameraWorker* prm_pCamWorker);

    void processReleaseResource(GgafLib::CameraWorker* prm_pResource);

    virtual ~CameraWorkerConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
