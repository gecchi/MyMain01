#ifndef GGAFDX9CUBEMAPMORPHMESHMODEL_H_
#define GGAFDX9CUBEMAPMORPHMESHMODEL_H_
namespace GgafDx9Core {

/**
 * 環境マップモーフメッシュモデル .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMorphMeshModel : public GgafDx9MorphMeshModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9CubeMapMorphMeshModel(char* prm_model_name);

    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDx9CubeMapMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHMODEL_H_*/

