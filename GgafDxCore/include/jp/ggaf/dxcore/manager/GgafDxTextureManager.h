#ifndef GGAFDXTEXTUREMANAGER_H_
#define GGAFDXTEXTUREMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxTextureConnection 管理クラス .
 * 生成済み GgafDxTextureConnection オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class GgafDxTextureManager : public GgafCore::GgafResourceManager<GgafDxTexture> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxTextureManager(const char* prm_manager_name);

    /**
     * オーバーライド
     */
    GgafDxTexture* processCreateResource(char* prm_idstr, void* prm_p);

    void releaseAll();

    void restoreAll();



    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDxTexture>* processCreateConnection(char* prm_idstr, GgafDxTexture* prm_pResource);

    virtual ~GgafDxTextureManager() {
    }
};

}
#endif /*GGAFDXTEXTUREMANAGER_H_*/
