#ifndef CAMERAWORKERCONNECTION_H_
#define CAMERAWORKERCONNECTION_H_
namespace MyStg2nd {

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
     * @param prm_pCameraWorker ディスパッチャー
     */
    CameraWorkerConnection(char* prm_idstr, CameraWorker* prm_pCameraWorker);

    void processReleaseResource(CameraWorker* prm_pResource);

    virtual ~CameraWorkerConnection() {
    }
};

}
#endif /*STORECONNECTION_H_*/
