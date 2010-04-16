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
class DispatcherManager : public GgafCore::GgafResourceManager<GgafCore::GgafActorDispatcher> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    DispatcherManager(const char* prm_manager_name);

    /**
     * ディスパッチャーを識別文字列から生成。
     * 本アプリのディスパッチャーはココに集約しようと思っている。
     * @param prm_idstr
     * @return ディスパッチャー
     */
    GgafCore::GgafActorDispatcher* processCreateResource(char* prm_idstr);

    GgafCore::GgafResourceConnection<GgafCore::GgafActorDispatcher>* processCreateConnection(char* prm_idstr, GgafCore::GgafActorDispatcher* prm_pResource);

    virtual ~DispatcherManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
