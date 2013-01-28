#ifndef GGAFDXBGMCONNECTION_H_
#define GGAFDXBGMCONNECTION_H_
namespace GgafDxCore {

/**
 * GgafDxBgm�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDxBgmConnection : public GgafCore::GgafResourceConnection<GgafDxBgm> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr OGG���ʖ�(���t�@�C����)
     * @param prm_pGgafDxBgm OGG
     */
    GgafDxBgmConnection(char* prm_idstr, GgafDxBgm* prm_pGgafDxBgm);

    void processReleaseResource(GgafDxBgm* prm_pResource);

    virtual ~GgafDxBgmConnection() {
    }
};

}
#endif /*GGAFDXBGMCONNECTION_H_*/
