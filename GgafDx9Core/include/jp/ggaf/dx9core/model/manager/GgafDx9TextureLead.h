#ifndef GGAFDX9TEXTURELEAD_H_
#define GGAFDX9TEXTURELEAD_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`���̃R�l�N�V����.
 */
class GgafDx9TextureLead : public GgafCore::GgafResourceLead<IDirect3DTexture9> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
     * @param prm_pIDirect3DTexture9 �e�N�X�`��
     */
    GgafDx9TextureLead(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

    void processReleaseResource(IDirect3DTexture9* prm_pResource);

    virtual ~GgafDx9TextureLead() {
    }
};

}
#endif /*GGAFDX9TEXTURELEAD_H_*/
