#ifndef GGAFDXBGMCONNECTION_H_
#define GGAFDXBGMCONNECTION_H_
namespace GgafDxCore {

/**
 * GgafDxBgmコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDxBgmConnection : public GgafCore::GgafResourceConnection<GgafDxBgm> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr OGG識別名(＝ファイル名)
     * @param prm_pGgafDxBgm OGG
     */
    GgafDxBgmConnection(char* prm_idstr, GgafDxBgm* prm_pGgafDxBgm);

    void processReleaseResource(GgafDxBgm* prm_pResource);

    virtual ~GgafDxBgmConnection() {
    }
};

}
#endif /*GGAFDXBGMCONNECTION_H_*/
