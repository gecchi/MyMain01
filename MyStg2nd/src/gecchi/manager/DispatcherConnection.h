#ifndef DISPATCHERCONNECTION_H_
#define DISPATCHERCONNECTION_H_
namespace MyStg2nd {

/**
 * Dispatcher�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DispatcherConnection : public GgafCore::GgafResourceConnection<GgafDx9LibStg::ActorDispatcher> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name OGG���ʖ�(���t�@�C����)
     * @param prm_pDispatcher OGG
     */
    DispatcherConnection(char* prm_idstr, GgafDx9LibStg::ActorDispatcher* prm_pDispatcher);

    void processReleaseResource(GgafDx9LibStg::ActorDispatcher* prm_pResource);

    virtual ~DispatcherConnection() {
    }
};

}
#endif /*DISPATCHERCONNECTION_H_*/
