#ifndef GGAF_DX_IBUMPMAPACTOR_H_
#define GGAF_DX_IBUMPMAPACTOR_H_
#include "GgafDxCommonHeader.h"

#include <d3d9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * バンプマップオブジェクト用インターフェイス。
 * @version 1.00
 * @since 2012/07/06
 * @author Masatoshi Tsuge
 */
class IBumpMapActor {

public:
    /** 環境マップテクスチャ資源 */
    TextureConnection* _pBumpMapTextureConnection;

    char* _bumpmap_tex;

public:
    IBumpMapActor();

    /**
     * バンプマッピングするテクスチャを指定する。 .
     * コンストラクタ以外で実行すると、テクスチャ排他の関係で処理が遅いです。
     * @param prm_cubemap_tex 環境マッップテクスチャファイル名
     */
    void setBumpMapTexture(const char* prm_bumpmap_tex);


    IDirect3DBaseTexture9* getBumpMapTexture();

    virtual ~IBumpMapActor();

};

}
#endif /*GGAF_DX_ICUBEMAPACTOR_H_*/
