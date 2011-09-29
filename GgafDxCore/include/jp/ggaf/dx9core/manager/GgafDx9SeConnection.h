#ifndef GGAFDX9SECONNECTION_H_
#define GGAFDX9SECONNECTION_H_
namespace GgafDx9Core {

/**
 * GgafDx9Se�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDx9SeConnection : public GgafCore::GgafResourceConnection<GgafDx9Se> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �T�E���h�G�t�F�N�g���ʖ�
     * @param prm_pGgafDx9Se �T�E���h�G�t�F�N�g�I�u�W�F�N�g�i���l�̃|�C���^�j
     */
    GgafDx9SeConnection(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se);

    void processReleaseResource(GgafDx9Se* prm_pResource);

    virtual ~GgafDx9SeConnection() {
    }
};

}
#endif /*GGAFDX9SECONNECTION_H_*/
