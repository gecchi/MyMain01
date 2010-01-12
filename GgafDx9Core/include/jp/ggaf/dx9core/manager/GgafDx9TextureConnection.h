#ifndef GGAFDX9TEXTURECONNECTION_H_
#define GGAFDX9TEXTURECONNECTION_H_
namespace GgafDx9Core {

/**
 * テクスチャのコネクション.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureConnection : public GgafCore::GgafResourceConnection<IDirect3DTexture9> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr テクスチャ識別名
     * @param prm_pIDirect3DTexture9 テクスチャ
     */
    GgafDx9TextureConnection(char* prm_idstr, IDirect3DTexture9* prm_pIDirect3DTexture9);

    void processReleaseResource(IDirect3DTexture9* prm_pResource);

    virtual ~GgafDx9TextureConnection() {
    }
};

}
#endif /*GGAFDX9TEXTURECONNECTION_H_*/
