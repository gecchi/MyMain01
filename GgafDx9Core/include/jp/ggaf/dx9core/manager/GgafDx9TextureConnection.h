#ifndef GGAFDX9TEXTURECONNECTION_H_
#define GGAFDX9TEXTURECONNECTION_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`���̃R�l�N�V����.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureConnection : public GgafCore::GgafResourceConnection<IDirect3DTexture9> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �e�N�X�`�����ʖ�
     * @param prm_pIDirect3DTexture9 �e�N�X�`��
     */
    GgafDx9TextureConnection(char* prm_idstr, IDirect3DTexture9* prm_pIDirect3DTexture9);

    void processReleaseResource(IDirect3DTexture9* prm_pResource);

    virtual ~GgafDx9TextureConnection() {
    }
};

}
#endif /*GGAFDX9TEXTURECONNECTION_H_*/
