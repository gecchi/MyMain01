#ifndef GGAFDX9MODELLEAD_H_
#define GGAFDX9MODELLEAD_H_
namespace GgafDx9Core {

/**
 * モデルのコネクション.
 */
class GgafDx9ModelLead : public GgafCore::GgafResourceLead<GgafDx9Model> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
     * @param prm_pModel リソースとなるモデル
     */
    GgafDx9ModelLead(char* prm_idstr, GgafDx9Model* prm_pModel);

    void processReleaseResource(GgafDx9Model* prm_pResource);

    virtual ~GgafDx9ModelLead() {
    }
};

}
#endif /*GGAFDX9MODELLEAD_H_*/
