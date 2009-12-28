#ifndef DISPATCHERMANAGER_H_
#define DISPATCHERMANAGER_H_
namespace MyStg2nd {

/**
 * Dispatcher 管理クラス .
 * 生成済み Dispatcher オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class DispatcherManager : public GgafCore::GgafResourceManager<GgafDx9LibStg::ActorDispatcher> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    DispatcherManager(const char* prm_manager_name);

    GgafDx9LibStg::ActorDispatcher* processCreateResource(char* prm_idstr);

    GgafCore::GgafResourceConnection<GgafDx9LibStg::ActorDispatcher>* processCreateConnection(char* prm_idstr, GgafDx9LibStg::ActorDispatcher* prm_pResource);

    virtual ~DispatcherManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
