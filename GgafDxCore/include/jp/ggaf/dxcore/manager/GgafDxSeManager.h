#ifndef GGAFDXSEMANAGER_H_
#define GGAFDXSEMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxSe �Ǘ��N���X .
 * �����ς� GgafDxSe �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxSeManager : public GgafCore::GgafResourceManager<GgafDxSe> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxSeManager(const char* prm_manager_name);

    GgafDxSe* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDxSe>* processCreateConnection(char* prm_idstr, GgafDxSe* prm_pResource);

    virtual ~GgafDxSeManager() {
    }
};

}
#endif /*GGAFDXSEMANAGER_H_*/
