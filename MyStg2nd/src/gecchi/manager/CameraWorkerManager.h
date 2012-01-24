#ifndef CAMERAWORKERMANAGER_H_
#define CAMERAWORKERMANAGER_H_
namespace MyStg2nd {

/**
 * CameraWorker �Ǘ��N���X .
 * �����ς� CameraWorker �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CameraWorkerManager : public GgafCore::GgafResourceManager<CameraWorker> {

public:

    CameraWorkerManager(const char* prm_manager_name);

    CameraWorker* processCreateResource(char* prm_idstr, void* prm_p) override;

    GgafCore::GgafResourceConnection<CameraWorker>* processCreateConnection(char* prm_idstr, CameraWorker* prm_pResource) override;

    virtual ~CameraWorkerManager() {
    }
};

}
#endif /*GGAFDXBGMMANAGER_H_*/
