#ifndef GGAFDXWORLDMODEL_H_
#define GGAFDXWORLDMODEL_H_
namespace GgafDxCore {

/**
 * 世界境界モデル .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundModel : public GgafDxMorphMeshModel {
    friend class GgafDxModelManager;

public:

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxWorldBoundModel(char* prm_model_name);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDxWorldBoundModel(); //デストラクタ
};

}
#endif /*GGAFDXWORLDMODEL_H_*/

