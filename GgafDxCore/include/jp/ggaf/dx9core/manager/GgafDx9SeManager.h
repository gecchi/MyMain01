#ifndef GGAFDX9SEMANAGER_H_
#define GGAFDX9SEMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9Se �Ǘ��N���X .
 * �����ς� GgafDx9Se �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9SeManager : public GgafCore::GgafResourceManager<GgafDx9Se> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9SeManager(const char* prm_manager_name);

    GgafDx9Se* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Se>* processCreateConnection(char* prm_idstr, GgafDx9Se* prm_pResource);

    virtual ~GgafDx9SeManager() {
    }
};

}
#endif /*GGAFDX9SEMANAGER_H_*/
