#ifndef STOREMANAGER_H_
#define STOREMANAGER_H_
namespace MyStg2nd {

/**
 * Store 管理クラス .
 * 生成済み Store オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class StoreManager : public GgafCore::GgafResourceManager<GgafCore::GgafActorStore> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    StoreManager(const char* prm_manager_name);

    /**
     * ストアーを識別文字列から生成。
     * 本アプリのストアーはココに集約しようと思っている。
     * @param prm_idstr
     * @return ストアー
     */
    GgafCore::GgafActorStore* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafCore::GgafActorStore>* processCreateConnection(char* prm_idstr, GgafCore::GgafActorStore* prm_pResource);

    virtual ~StoreManager() {
    }
};

}
#endif /*STOREMANAGER_H_*/
