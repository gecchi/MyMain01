#ifndef DEPOSITORYMANAGER_H_
#define DEPOSITORYMANAGER_H_
namespace MyStg2nd {

/**
 * Depository 管理クラス .
 * 生成済み Depository オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class DepositoryManager : public GgafCore::GgafResourceManager<GgafCore::GgafActorDepository> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    DepositoryManager(const char* prm_manager_name);

    /**
     * デポジトリを識別文字列から生成。
     * 本アプリのデポジトリはココに集約しようと思っている。
     * @param prm_idstr
     * @return デポジトリ
     */
    GgafCore::GgafActorDepository* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafCore::GgafActorDepository>* processCreateConnection(char* prm_idstr, GgafCore::GgafActorDepository* prm_pResource);

    virtual ~DepositoryManager() {
    }
};

}
#endif /*DEPOSITORYMANAGER_H_*/
