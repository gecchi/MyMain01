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
 * テクスチャクラス.
 * DirectXのテクスチャインターフェースのラッパーです。<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class Texture : public GgafCore::Object {
    friend class TextureManager;

    static std::string getTextureFilePath(std::string prm_file);

public:
    /** モデル定義の識別名。(50文字まで) */
    char* _texture_name;
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
     * @param prm_texture_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
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
    virtual ~Texture(); //デストラクタ
};

}
#endif /*GGAF_DX_EFFECT_H_*/
