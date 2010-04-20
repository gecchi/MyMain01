#ifndef GGAFDX9TEXTURE_H_
#define GGAFDX9TEXTURE_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`�����N���X.
 * �L����(�A�N�^�[)�̃e�N�X�`�������b�v����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9Texture : public GgafCore::GgafObject {
    friend class GgafDx9TextureManager;

protected:
public:

    /** ���f����`�̎��ʖ��B(50�����܂�) */
    char* _texture_name;
    D3DXIMAGE_INFO* _pD3DXIMAGE_INFO;
    LPDIRECT3DTEXTURE9 _pIDirect3DTexture9;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9Texture(char* prm_texture_name);

    char* getName() {
        return _texture_name;
    }


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9TextureManager�ł���<BR>
     */
    virtual ~GgafDx9Texture(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9EFFECT_H_*/
