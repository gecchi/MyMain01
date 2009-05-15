#ifndef GGAFDX9EFFECTMANAGER_H_
#define GGAFDX9EFFECTMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9EffectConnection 管理クラス .
 * 生成済み GgafDx9EffectConnection オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9EffectManager : public GgafCore::GgafResourceManager<GgafDx9Effect> {

public:

    static GgafDx9Effect* _pEffect_Active;

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9EffectManager(const char* prm_manager_name);

    /**
     * オーバーライド
     */
    GgafDx9Effect* processCreateResource(char* prm_idstr);

    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDx9Effect>* processCreateConnection(char* prm_idstr, GgafDx9Effect* prm_pResource);


    void restoreAll();

    void onDeviceLostAll();

    virtual ~GgafDx9EffectManager() {
    }
};

}
#endif /*GGAFDX9EFFECTMANAGER_H_*/
