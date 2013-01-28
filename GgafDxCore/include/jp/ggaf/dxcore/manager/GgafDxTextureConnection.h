#ifndef GGAFDXTEXTURECONNECTION_H_
#define GGAFDXTEXTURECONNECTION_H_
namespace GgafDxCore {

/**
 * �e�N�X�`���̃R�l�N�V����.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDxTextureConnection : public GgafCore::GgafResourceConnection<GgafDxTexture> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �e�N�X�`�����ʖ�
     * @param prm_pResource �e�N�X�`��
     */
    GgafDxTextureConnection(char* prm_idstr, GgafDxTexture* prm_pResource);

    void processReleaseResource(GgafDxTexture* prm_pResource);

    virtual ~GgafDxTextureConnection() {
    }
};

}
#endif /*GGAFDXTEXTURECONNECTION_H_*/
