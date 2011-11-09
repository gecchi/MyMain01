#ifndef GGAFDXTEXTURE_H_
#define GGAFDXTEXTURE_H_
namespace GgafDxCore {

/**
 * �e�N�X�`�����N���X.
 * �L����(�A�N�^�[)�̃e�N�X�`�������b�v����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxTexture : public GgafCore::GgafObject {
    friend class GgafDxTextureManager;

protected:
public:

    /** ���f����`�̎��ʖ��B(50�����܂�) */
    char* _texture_name;
    /** �e�N�X�`���̕�(px) */
    UINT _tex_width;
    /** �e�N�X�`���̍���(px) */
    UINT _tex_height;
    D3DXIMAGE_INFO* _pD3DXIMAGE_INFO;
    LPDIRECT3DBASETEXTURE9 _pIDirect3DBaseTexture9;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxTexture(char* prm_texture_name);

    void restore();

    void release();

    char* getName() {
        return _texture_name;
    }


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxTextureManager�ł���<BR>
     */
    virtual ~GgafDxTexture(); //�f�X�g���N�^
};

}
#endif /*GGAFDXEFFECT_H_*/