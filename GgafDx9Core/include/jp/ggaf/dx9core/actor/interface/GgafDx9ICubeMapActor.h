#ifndef GGAFDX9ICUBEMAPACTOR_H_
#define GGAFDX9ICUBEMAPACTOR_H_
namespace GgafDx9Core {

/**
 * GgafDx9Core名前空間の基底アクタークラス.
 * GgafMainActorを継承しただけです。<BR>
 * GgafDx9Core名前空間内では、このクラスを基底アクターとします。<BR>
 * @version 1.00
 * @since 2009/09/08
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

    GgafDx9ICubeMapActor();

    /**
     * 環境マッピングするテクスチャを指定する。
     * @param prm_cubemap_tex テクスチャファイル名
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
    void setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance);

    virtual ~GgafDx9ICubeMapActor(); //デストラクタ

};

}
#endif /*GGAFDX9ICUBEMAPACTOR_H_*/
