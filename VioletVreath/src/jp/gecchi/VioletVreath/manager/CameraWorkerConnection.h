#ifndef CAMERAWORKERCONNECTION_H_
#define CAMERAWORKERCONNECTION_H_
namespace VioletVreath {

/**
 * CameraWorker�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class CameraWorkerConnection : public GgafCore::GgafResourceConnection<CameraWorker> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pCamWorker �f�|�W�g��
     */
    CameraWorkerConnection(char* prm_idstr, CameraWorker* prm_pCamWorker);

    void processReleaseResource(CameraWorker* prm_pResource);

    virtual ~CameraWorkerConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
