#ifndef DEPOSITORYMANAGER_H_
#define DEPOSITORYMANAGER_H_
namespace MyStg2nd {

/**
 * Depository �Ǘ��N���X .
 * �����ς� Depository �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class DepositoryManager : public GgafCore::GgafResourceManager<GgafCore::GgafActorDepository> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DepositoryManager(const char* prm_manager_name);

    /**
     * �f�|�W�g�������ʕ����񂩂琶���B
     * �{�A�v���̃f�|�W�g���̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return �f�|�W�g��
     */
    GgafCore::GgafActorDepository* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafCore::GgafActorDepository>* processCreateConnection(char* prm_idstr, GgafCore::GgafActorDepository* prm_pResource);

    virtual ~DepositoryManager() {
    }
};

}
#endif /*DEPOSITORYMANAGER_H_*/
