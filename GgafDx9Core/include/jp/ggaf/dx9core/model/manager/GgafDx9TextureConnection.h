#ifndef GGAFDX9TEXTURECONNECTION_H_
#define GGAFDX9TEXTURECONNECTION_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`���̃R�l�N�V����.
 */
class GgafDx9TextureConnection : public GgafCore::GgafResourceConnection<IDirect3DTexture9> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
     * @param prm_pIDirect3DTexture9 �e�N�X�`��
     */
    GgafDx9TextureConnection(char* prm_idstr, IDirect3DTexture9* prm_pIDirect3DTexture9);

    void processReleaseResource(IDirect3DTexture9* prm_pResource);


    IDirect3DTexture9* view() {

        _pResource->AddRef();
        ULONG refcnt = _pResource->Release();
        _TRACE_("GgafDx9TextureConnection::view "<<_idstr<<" _pResource�̎Q�ƃJ�E���^��" << refcnt);
        return _pResource;
    }


    virtual ~GgafDx9TextureConnection();
};

}
#endif /*GGAFDX9TEXTURECONNECTION_H_*/
