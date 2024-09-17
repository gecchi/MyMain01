#ifndef GGAF_DX_TEXTURE_H_
#define GGAF_DX_TEXTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


namespace GgafDx {

/**
 * テクスチャクラス.
 * DirectXのテクスチャインターフェースのラッパーです。<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class Texture : public GgafCore::Object {
    friend class TextureManager;

    /**
     * CONFIGのリソースディレクトリを参照し、パス付きテクスチャファイル名を得る .
     * @param prm_file テクスチャファイル名
     * @return パス付きテクスチャファイル名
     */
    static std::string getTextureFilePath(std::string prm_file);

public:
    /** テクスチャファイル名 */
    char* _texture_name;
    /** パス付きテクスチャファイル名 */
    std::string _texture_file_name;
    /** テクスチャの幅(px) */
    UINT _tex_width;
    /** テクスチャの高さ(px) */
    UINT _tex_height;

    D3DXIMAGE_INFO* _pD3DXIMAGE_INFO;

    LPDIRECT3DBASETEXTURE9 _pIDirect3DBaseTexture9;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_texture_name テクスチャファイル名
     */
    explicit Texture(const char* prm_texture_name);

    void restore();

    void release();

    char* getName() {
        return _texture_name;
    }

    /**
     * デストラクタ<BR>
     * deleteするのはTextureManagerである<BR>
     */
    virtual ~Texture();
};

}
#endif /*GGAF_DX_EFFECT_H_*/
