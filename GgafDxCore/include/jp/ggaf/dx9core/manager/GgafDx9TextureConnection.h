#ifndef GGAFDX9TEXTURECONNECTION_H_
#define GGAFDX9TEXTURECONNECTION_H_
namespace GgafDx9Core {

/**
 * テクスチャのコネクション.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureConnection : public GgafCore::GgafResourceConnection<GgafDx9Texture> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr テクスチャ識別名
     * @param prm_pResource テクスチャ
     */
    GgafDx9TextureConnection(char* prm_idstr, GgafDx9Texture* prm_pResource);

    void processReleaseResource(GgafDx9Texture* prm_pResource);

    virtual ~GgafDx9TextureConnection() {
    }
};

}
#endif /*GGAFDX9TEXTURECONNECTION_H_*/
