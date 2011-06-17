#ifndef GGAFDX9ICUBEMAPACTOR_H_
#define GGAFDX9ICUBEMAPACTOR_H_
namespace GgafDx9Core {

/**
 * キューブ環境マップオブジェクト用インターフェイス。
 * @version 1.00
 * @since 2011/05/27
 * @author Masatoshi Tsuge
 */
class GgafDx9ICubeMapActor {

public:
    /** 環境マップテクスチャ資源 */
    GgafDx9TextureConnection* _pCubeMapTextureCon;
    /** 環境マップテクスチャ */
    IDirect3DBaseTexture9* _pCubeMapTexture;
    /** 環境マップテクスチャ映りこみ率 */
    float _reflectance;

    const char* _cubemap_tex;

    GgafDx9ICubeMapActor();

    /**
     * 環境マッピングするテクスチャを指定する。
     * @param prm_cubemap_tex テクスチャファイル名
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
    void setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance = 1.0);

    IDirect3DBaseTexture9* getCubeMapTexture();

    float getCubeMapReflectance() {
        return _reflectance;
    }

    void releaseCubeMapTex();

    void restoreCubeMapTex();

    virtual ~GgafDx9ICubeMapActor(); //デストラクタ

};

}
#endif /*GGAFDX9ICUBEMAPACTOR_H_*/
