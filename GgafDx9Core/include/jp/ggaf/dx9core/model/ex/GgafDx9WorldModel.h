#ifndef GGAFDX9WORLDMODEL_H_
#define GGAFDX9WORLDMODEL_H_
namespace GgafDx9Core {

/**
 * 世界境界モデル .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class GgafDx9WorldBoundModel : public GgafDx9MorphMeshModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9WorldBoundModel(char* prm_model_name);

    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDx9WorldBoundModel(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHMODEL_H_*/

