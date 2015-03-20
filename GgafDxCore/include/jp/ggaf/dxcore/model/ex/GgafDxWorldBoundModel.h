#ifndef GGAFDXCORE_GGAFDXWORLDMODEL_H_
#define GGAFDXCORE_GGAFDXWORLDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

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

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual ~GgafDxWorldBoundModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXWORLDMODEL_H_*/

