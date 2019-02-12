#ifndef GGAF_DX_WORLDMODEL_H_
#define GGAF_DX_WORLDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"

namespace GgafDx {

/**
 * 世界境界モデル .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class WorldBoundModel : public MorphMeshModel {
    friend class ModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    WorldBoundModel(const char* prm_model_name);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~WorldBoundModel(); //デストラクタ
};

}
#endif /*GGAF_DX_WORLDMODEL_H_*/

