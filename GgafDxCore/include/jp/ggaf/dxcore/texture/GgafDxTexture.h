#ifndef GGAFDXCORE_GGAFDXTEXTURE_H_
#define GGAFDXCORE_GGAFDXTEXTURE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <string>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


namespace GgafDxCore {

/**
 * テクスチャクラス.
 * DirectXのテクスチャインターフェースのラッパーです。<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxTexture : public GgafCore::GgafObject {
    friend class GgafDxTextureManager;

    static std::string getTextureFileName(std::string prm_file);

public:
    /** モデル定義の識別名。(50文字まで) */
    char* _texture_name;
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
    explicit GgafDxTexture(const char* prm_texture_name);

    void restore();

    void release();

    char* getName() {
        return _texture_name;
    }

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxTextureManagerである<BR>
     */
    virtual ~GgafDxTexture(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXEFFECT_H_*/
