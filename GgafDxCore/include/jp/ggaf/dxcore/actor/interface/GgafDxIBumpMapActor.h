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
    GgafDxTextureConnection* _pBumpMapTextureConnection;

    const char* _bumpmap_tex;

public:
    GgafDxIBumpMapActor();

    /**
     * バンプマッピングするテクスチャを指定する。 .
     * コンストラクタ以外で実行すると、テクスチャ排他の関係で処理が遅いです。
     * @param prm_cubemap_tex 環境マッップテクスチャファイル名
     */
    void setBumpMapTexture(const char* prm_bumpmap_tex);


    IDirect3DBaseTexture9* getBumpMapTexture();

    virtual ~GgafDxIBumpMapActor();

};

}
#endif /*GGAFDXICUBEMAPACTOR_H_*/
