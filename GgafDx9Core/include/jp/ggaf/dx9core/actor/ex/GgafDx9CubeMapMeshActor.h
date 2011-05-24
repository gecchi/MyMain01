#ifndef GGAFDX9CUBEMAPMESHACTOR_H_
#define GGAFDX9CUBEMAPMESHACTOR_H_
namespace GgafDx9Core {

/**
 * 環境マップメッシュアクター.
 * GgafDx9MeshActor を継承し、環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshActor : public GgafDx9MeshActor {

public:

    /** モデル資源 */
    GgafDx9CubeMapMeshModel* _pCubeMapMeshModel;
    /** エフェクト資源 */
    GgafDx9CubeMapMeshEffect* _pCubeMapMeshEffect;

    /** 環境マップテクスチャ資源 */
    GgafDx9TextureConnection* _pCubeMapTextureCon;
    /** 環境マップテクスチャ */
    IDirect3DBaseTexture9* _pCubeMapTexture;
    /** 環境マップテクスチャ映りこみ率 */
    float _reflectance;
    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDx9CubeMapMeshActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    /**
     * 環境マッピングするテクスチャを指定する。
     * @param prm_cubemap_tex テクスチャファイル名
     * @param prm_reflectance 環境マップテクスチャの映り込み具合(0.0～1.0)。
     *                        prm_cubemap_texの色に引数の率が乗じられ、下地のマテリアル色に加算されます。
     *                        0.0:映り込み無し、0.3:大理石ぐらい、1.0:鏡面
     */
    void setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance);

    virtual void processDraw() override;

    virtual ~GgafDx9CubeMapMeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMESHACTOR_H_*/
