#ifndef GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#define GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"

namespace GgafDx {

/**
 * 環境マップモーフメッシュモデル .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshModel : public MorphMeshModel {
    friend class ModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    CubeMapMorphMeshModel(const char* prm_model_name);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~CubeMapMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAF_DX_CUBEMAPMORPHMESHMODEL_H_*/

