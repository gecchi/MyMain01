#ifndef GGAFDXBGMMANAGER_H_
#define GGAFDXBGMMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxBgm 管理クラス .
 * 生成済み GgafDxBgm オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxBgmManager : public GgafCore::GgafResourceManager<GgafDxBgm> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxBgmManager(const char* prm_manager_name);

    GgafDxBgm* processCreateResource(char* prm_idstr, void* prm_p) override;

    GgafCore::GgafResourceConnection<GgafDxBgm>* processCreateConnection(char* prm_idstr, GgafDxBgm* prm_pResource) override;

    virtual ~GgafDxBgmManager() {
    }
};

}
#endif /*GGAFDXBGMMANAGER_H_*/
