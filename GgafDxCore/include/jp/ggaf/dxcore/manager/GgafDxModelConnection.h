#ifndef GGAFDXMODELCONNECTION_H_
#define GGAFDXMODELCONNECTION_H_
namespace GgafDxCore {

/**
 * モデル資源のコネクション.
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDxModelConnection : public GgafCore::GgafResourceConnection<GgafDxModel> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr モデル識別名
     * @param prm_pModel リソースとなるモデル
     */
    GgafDxModelConnection(char* prm_idstr, GgafDxModel* prm_pModel);

    void processReleaseResource(GgafDxModel* prm_pResource);

    virtual ~GgafDxModelConnection() {
    }
};

}
#endif /*GGAFDXMODELCONNECTION_H_*/
