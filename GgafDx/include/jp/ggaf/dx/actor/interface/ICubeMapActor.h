#ifndef GGAF_DX_ICUBEMAPACTOR_H_
#define GGAF_DX_ICUBEMAPACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include <d3d9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * キューブ環境マップオブジェクト用インターフェイス。
 * @version 1.00
 * @since 2011/05/27
 * @author Masatoshi Tsuge
 */
class ICubeMapActor {

public:
    /** 環境マップテクスチャ資源 */
    TextureConnection* _pCubeMapTextureConnection;
    /** 環境マップテクスチャ映りこみ率 */
    float _reflectance;
    char* _cubemap_tex;

public:
    ICubeMapActor();

    /**
     * 環境マッピングするテクスチャと映り込み具合を指定する。 .
     * コンストラクタ以外で実行すると、テクスチャ排他の関係で処理が遅いです。
     * @param prm_cubemap_tex テクスチャファイル名
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
    void setCubeMap(const char* prm_cubemap_tex, float prm_reflectance);

    /**
     * 環境マッピングするテクスチャを指定する。 .
     * コンストラクタ以外で実行すると、テクスチャ排他の関係で処理が遅いです。
     * @param prm_cubemap_tex 環境マッップテクスチャファイル名
     */
    void setCubeMapTexture(const char* prm_cubemap_tex);

    /**
     * 環境マップの映り込み具合 .
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
    void setCubeMapReflectance(float prm_reflectance);

    IDirect3DBaseTexture9* getCubeMapTexture();

    float getCubeMapReflectance() {
        return _reflectance;
    }

    virtual ~ICubeMapActor();

};

}
#endif /*GGAF_DX_ICUBEMAPACTOR_H_*/
