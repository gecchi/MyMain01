#ifndef GGAFDXSEMANAGER_H_
#define GGAFDXSEMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxSe 管理クラス .
 * 生成済み GgafDxSe オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxSeManager : public GgafCore::GgafResourceManager<GgafDxSe> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxSeManager(const char* prm_manager_name);

    GgafDxSe* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDxSe>* processCreateConnection(char* prm_idstr, GgafDxSe* prm_pResource);

    virtual ~GgafDxSeManager() {
    }
};

}
#endif /*GGAFDXSEMANAGER_H_*/
