#ifndef CAMERAWORKERCONNECTION_H_
#define CAMERAWORKERCONNECTION_H_
namespace VioletVreath {

/**
 * CameraWorkerコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class CameraWorkerConnection : public GgafCore::GgafResourceConnection<CameraWorker> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pCamWorker デポジトリ
     */
    CameraWorkerConnection(char* prm_idstr, CameraWorker* prm_pCamWorker);

    void processReleaseResource(CameraWorker* prm_pResource);

    virtual ~CameraWorkerConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
