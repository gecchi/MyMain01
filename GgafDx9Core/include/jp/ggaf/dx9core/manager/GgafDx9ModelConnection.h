#ifndef GGAFDX9MODELCONNECTION_H_
#define GGAFDX9MODELCONNECTION_H_
namespace GgafDx9Core {

/**
 * モデルのコネクション.
 */
class GgafDx9ModelConnection : public GgafCore::GgafResourceConnection<GgafDx9Model> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
     * @param prm_pModel リソースとなるモデル
     */
    GgafDx9ModelConnection(char* prm_idstr, GgafDx9Model* prm_pModel);

    void processReleaseResource(GgafDx9Model* prm_pResource);

    virtual ~GgafDx9ModelConnection() {
    }
};

}
#endif /*GGAFDX9MODELCONNECTION_H_*/
