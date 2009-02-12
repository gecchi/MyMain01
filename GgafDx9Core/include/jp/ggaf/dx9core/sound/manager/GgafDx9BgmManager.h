#ifndef GGAFDX9BGMMANAGER_H_
#define GGAFDX9BGMMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9Bgm 管理クラス .
 * 生成済み GgafDx9Bgm オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9BgmManager : public GgafCore::GgafResourceManager<GgafDx9Bgm> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9BgmManager(const char* prm_manager_name);

    GgafDx9Bgm* processCreateResource(char* prm_idstr);

    GgafCore::GgafResourceLead<GgafDx9Bgm>* processCreateLead(char* prm_idstr, GgafDx9Bgm* prm_pResource);

    virtual ~GgafDx9BgmManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
