#ifndef DISPATCHERCONNECTION_H_
#define DISPATCHERCONNECTION_H_
namespace MyStg2nd {

/**
 * Dispatcher�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DispatcherConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafActorDispatcher> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pDispatcher �f�B�X�p�b�`���[
     */
    DispatcherConnection(char* prm_idstr, GgafCore::GgafActorDispatcher* prm_pDispatcher);

    void processReleaseResource(GgafCore::GgafActorDispatcher* prm_pResource);

    virtual ~DispatcherConnection() {
    }
};

}
#endif /*DISPATCHERCONNECTION_H_*/
