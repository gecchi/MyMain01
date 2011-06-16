#ifndef STORECONNECTION_H_
#define STORECONNECTION_H_
namespace MyStg2nd {

/**
 * Store�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class StoreConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafActorStore> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pStore �f�B�X�p�b�`���[
     */
    StoreConnection(char* prm_idstr, GgafCore::GgafActorStore* prm_pStore);

    void processReleaseResource(GgafCore::GgafActorStore* prm_pResource);

    virtual ~StoreConnection() {
    }
};

}
#endif /*STORECONNECTION_H_*/
