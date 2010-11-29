#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9TextureConnection 管理クラス .
 * 生成済み GgafDx9TextureConnection オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<GgafDx9Texture> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9TextureManager(const char* prm_manager_name);

    /**
     * オーバーライド
     */
    GgafDx9Texture* processCreateResource(char* prm_idstr, void* prm_p);

    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDx9Texture>* processCreateConnection(char* prm_idstr, GgafDx9Texture* prm_pResource);

    virtual ~GgafDx9TextureManager() {
    }
};

}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
