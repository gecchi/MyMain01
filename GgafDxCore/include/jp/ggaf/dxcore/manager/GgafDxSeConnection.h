#ifndef GGAFDXSECONNECTION_H_
#define GGAFDXSECONNECTION_H_
namespace GgafDxCore {

/**
 * GgafDxSe�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDxSeConnection : public GgafCore::GgafResourceConnection<GgafDxSe> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �T�E���h�G�t�F�N�g���ʖ�
     * @param prm_pGgafDxSe �T�E���h�G�t�F�N�g�I�u�W�F�N�g�i���l�̃|�C���^�j
     */
    GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe);

    void processReleaseResource(GgafDxSe* prm_pResource);

    virtual ~GgafDxSeConnection() {
    }
};

}
#endif /*GGAFDXSECONNECTION_H_*/