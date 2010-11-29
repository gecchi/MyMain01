#ifndef GGAFDX9BGMMANAGER_H_
#define GGAFDX9BGMMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9Bgm �Ǘ��N���X .
 * �����ς� GgafDx9Bgm �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9BgmManager : public GgafCore::GgafResourceManager<GgafDx9Bgm> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9BgmManager(const char* prm_manager_name);

    GgafDx9Bgm* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Bgm>* processCreateConnection(char* prm_idstr, GgafDx9Bgm* prm_pResource);

    virtual ~GgafDx9BgmManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
