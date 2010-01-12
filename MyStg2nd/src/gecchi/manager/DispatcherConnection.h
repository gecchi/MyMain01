#ifndef DISPATCHERCONNECTION_H_
#define DISPATCHERCONNECTION_H_
namespace MyStg2nd {

/**
 * Dispatcherコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DispatcherConnection : public GgafCore::GgafResourceConnection<GgafDx9LibStg::ActorDispatcher> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pDispatcher ディスパッチャー
     */
    DispatcherConnection(char* prm_idstr, GgafDx9LibStg::ActorDispatcher* prm_pDispatcher);

    void processReleaseResource(GgafDx9LibStg::ActorDispatcher* prm_pResource);

    virtual ~DispatcherConnection() {
    }
};

}
#endif /*DISPATCHERCONNECTION_H_*/
