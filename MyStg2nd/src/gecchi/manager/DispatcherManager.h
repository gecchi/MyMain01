#ifndef DISPATCHERMANAGER_H_
#define DISPATCHERMANAGER_H_
namespace MyStg2nd {

/**
 * Dispatcher �Ǘ��N���X .
 * �����ς� Dispatcher �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class DispatcherManager : public GgafCore::GgafResourceManager<GgafCore::GgafActorDispatcher> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DispatcherManager(const char* prm_manager_name);

    /**
     * �f�B�X�p�b�`���[�����ʕ����񂩂琶���B
     * �{�A�v���̃f�B�X�p�b�`���[�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return �f�B�X�p�b�`���[
     */
    GgafCore::GgafActorDispatcher* processCreateResource(char* prm_idstr);

    GgafCore::GgafResourceConnection<GgafCore::GgafActorDispatcher>* processCreateConnection(char* prm_idstr, GgafCore::GgafActorDispatcher* prm_pResource);

    virtual ~DispatcherManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
