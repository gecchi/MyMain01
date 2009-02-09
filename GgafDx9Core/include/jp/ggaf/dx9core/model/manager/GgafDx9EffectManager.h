#ifndef GGAFDX9EFFECTMANAGER_H_
#define GGAFDX9EFFECTMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9EffectLead 管理クラス .
 * 生成済み GgafDx9EffectLead オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9EffectManager : public GgafCore::GgafResourceManager<ID3DXEffect> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9EffectManager(const char* prm_manager_name);

    /**
     * オーバーライド
     */
    ID3DXEffect* processCreateResource(char* prm_idstr);

    /**
     * オーバーライド
     */
    GgafCore::GgafResourceLead<ID3DXEffect>* processCreateLead(char* prm_idstr, ID3DXEffect* prm_pResource);

    virtual ~GgafDx9EffectManager() {
    }
};

}
#endif /*GGAFDX9EFFECTMANAGER_H_*/
