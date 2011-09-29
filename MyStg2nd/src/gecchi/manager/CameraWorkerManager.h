#ifndef CAMERAWORKERMANAGER_H_
#define CAMERAWORKERMANAGER_H_
namespace MyStg2nd {

/**
 * CameraWorker 管理クラス .
 * 生成済み CameraWorker オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CameraWorkerManager : public GgafCore::GgafResourceManager<CameraWorker> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    CameraWorkerManager(const char* prm_manager_name);

    /**
     * CameraWorker を識別文字列から生成。
     * 本アプリのCameraWorker はココに集約しようと思っている。
     * @param prm_idstr
     * @return CameraWorker
     */
    CameraWorker* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<CameraWorker>* processCreateConnection(char* prm_idstr, CameraWorker* prm_pResource);

    virtual ~CameraWorkerManager() {
    }
};

}
#endif /*GGAFDXBGMMANAGER_H_*/
