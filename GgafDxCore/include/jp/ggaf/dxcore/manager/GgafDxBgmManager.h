#ifndef GGAFDXBGMMANAGER_H_
#define GGAFDXBGMMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxBgm �Ǘ��N���X .
 * �����ς� GgafDxBgm �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxBgmManager : public GgafCore::GgafResourceManager<GgafDxBgm> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxBgmManager(const char* prm_manager_name);

    GgafDxBgm* processCreateResource(char* prm_idstr, void* prm_p) override;

    GgafCore::GgafResourceConnection<GgafDxBgm>* processCreateConnection(char* prm_idstr, GgafDxBgm* prm_pResource) override;

    virtual ~GgafDxBgmManager() {
    }
};

}
#endif /*GGAFDXBGMMANAGER_H_*/
