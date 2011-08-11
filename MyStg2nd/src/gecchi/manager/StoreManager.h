#ifndef STOREMANAGER_H_
#define STOREMANAGER_H_
namespace MyStg2nd {

/**
 * Store �Ǘ��N���X .
 * �����ς� Store �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class StoreManager : public GgafCore::GgafResourceManager<GgafCore::GgafActorStore> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    StoreManager(const char* prm_manager_name);

    /**
     * �X�g�A�[�����ʕ����񂩂琶���B
     * �{�A�v���̃X�g�A�[�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return �X�g�A�[
     */
    GgafCore::GgafActorStore* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafCore::GgafActorStore>* processCreateConnection(char* prm_idstr, GgafCore::GgafActorStore* prm_pResource);

    virtual ~StoreManager() {
    }
};

}
#endif /*STOREMANAGER_H_*/
