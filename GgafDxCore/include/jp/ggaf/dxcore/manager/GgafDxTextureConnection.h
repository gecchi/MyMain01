#ifndef GGAFDXTEXTURECONNECTION_H_
#define GGAFDXTEXTURECONNECTION_H_
namespace GgafDxCore {

/**
 * テクスチャのコネクション.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDxTextureConnection : public GgafCore::GgafResourceConnection<GgafDxTexture> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr テクスチャ識別名
     * @param prm_pResource テクスチャ
     */
    GgafDxTextureConnection(char* prm_idstr, GgafDxTexture* prm_pResource);

    void processReleaseResource(GgafDxTexture* prm_pResource);

    virtual ~GgafDxTextureConnection() {
    }
};

}
#endif /*GGAFDXTEXTURECONNECTION_H_*/
