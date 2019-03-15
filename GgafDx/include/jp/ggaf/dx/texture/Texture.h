#ifndef GGAF_DX_TEXTURE_H_
#define GGAF_DX_TEXTURE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


namespace GgafDx {

/**
 * �e�N�X�`���N���X.
 * DirectX�̃e�N�X�`���C���^�[�t�F�[�X�̃��b�p�[�ł��B<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class Texture : public GgafCore::Object {
    friend class TextureManager;

    static std::string getTextureFileName(std::string prm_file);

public:
    /** ���f����`�̎��ʖ��B(50�����܂�) */
    char* _texture_name;
    /** �e�N�X�`���̕�(px) */
    UINT _tex_width;
    /** �e�N�X�`���̍���(px) */
    UINT _tex_height;
    D3DXIMAGE_INFO* _pD3DXIMAGE_INFO;
    LPDIRECT3DBASETEXTURE9 _pIDirect3DBaseTexture9;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    explicit Texture(const char* prm_texture_name);

    void restore();

    void release();

    char* getName() {
        return _texture_name;
    }

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�TextureManager�ł���<BR>
     */
    virtual ~Texture(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_EFFECT_H_*/