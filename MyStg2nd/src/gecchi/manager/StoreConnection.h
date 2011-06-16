#ifndef STORECONNECTION_H_
#define STORECONNECTION_H_
namespace MyStg2nd {

/**
 * Storeコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class StoreConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafActorStore> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pStore ディスパッチャー
     */
    StoreConnection(char* prm_idstr, GgafCore::GgafActorStore* prm_pStore);

    void processReleaseResource(GgafCore::GgafActorStore* prm_pResource);

    virtual ~StoreConnection() {
    }
};

}
#endif /*STORECONNECTION_H_*/
