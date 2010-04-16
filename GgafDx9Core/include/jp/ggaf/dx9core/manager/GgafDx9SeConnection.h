#ifndef GGAFDX9SECONNECTION_H_
#define GGAFDX9SECONNECTION_H_
namespace GgafDx9Core {

/**
 * GgafDx9Seコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDx9SeConnection : public GgafCore::GgafResourceConnection<GgafDx9Se> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr サウンドエフェクト識別名
     * @param prm_pGgafDx9Se サウンドエフェクトオブジェクト（実値のポインタ）
     */
    GgafDx9SeConnection(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se);

    void processReleaseResource(GgafDx9Se* prm_pResource);

    virtual ~GgafDx9SeConnection() {
    }
};

}
#endif /*GGAFDX9SECONNECTION_H_*/
