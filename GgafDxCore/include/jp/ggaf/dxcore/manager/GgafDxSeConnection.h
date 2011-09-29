#ifndef GGAFDXSECONNECTION_H_
#define GGAFDXSECONNECTION_H_
namespace GgafDxCore {

/**
 * GgafDxSeコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDxSeConnection : public GgafCore::GgafResourceConnection<GgafDxSe> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr サウンドエフェクト識別名
     * @param prm_pGgafDxSe サウンドエフェクトオブジェクト（実値のポインタ）
     */
    GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe);

    void processReleaseResource(GgafDxSe* prm_pResource);

    virtual ~GgafDxSeConnection() {
    }
};

}
#endif /*GGAFDXSECONNECTION_H_*/
