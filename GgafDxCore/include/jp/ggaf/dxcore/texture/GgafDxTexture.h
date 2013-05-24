#ifndef GGAFDXTEXTURE_H_
#define GGAFDXTEXTURE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <string>
#include <d3dx9.h>

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
    GgafDxTexture(char* prm_texture_name);

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
#endif /*GGAFDXEFFECT_H_*/
