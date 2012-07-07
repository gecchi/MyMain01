#ifndef GGAFDXIBUMPMAPACTOR_H_
#define GGAFDXIBUMPMAPACTOR_H_
namespace GgafDxCore {

/**
 * バンプマップオブジェクト用インターフェイス。
 * @version 1.00
 * @since 2012/07/06
 * @author Masatoshi Tsuge
 */
class GgafDxIBumpMapActor {

public:
    /** 環境マップテクスチャ資源 */
    GgafDxTextureConnection* _pBumpMapTextureCon;

    const char* _cubemap_tex;

    GgafDxIBumpMapActor();


    /**
     * 環境マッピングするテクスチャと映り込み具合を指定する。 .
     * コンストラクタ以外で実行すると、テクスチャ排他の関係で処理が遅いです。
     * @param prm_cubemap_tex テクスチャファイル名
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
//    void setBumpMap(const char* prm_cubemap_tex, float prm_reflectance);

    /**
     * 環境マッピングするテクスチャを指定する。 .
     * コンストラクタ以外で実行すると、テクスチャ排他の関係で処理が遅いです。
     * @param prm_cubemap_tex 環境マッップテクスチャファイル名
     */
    void setBumpMapTexture(const char* prm_cubemap_tex);

    /**
     * 環境マップの映り込み具合 .
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
//    void setBumpMapReflectance(float prm_reflectance);

    IDirect3DBaseTexture9* getBumpMapTexture();

//    float getBumpMapReflectance() {
//        return _reflectance;
//    }

//    void releaseBumpMapTex();
//
//    void restoreBumpMapTex();

    virtual ~GgafDxIBumpMapActor(); //デストラクタ

};

}
#endif /*GGAFDXICUBEMAPACTOR_H_*/
