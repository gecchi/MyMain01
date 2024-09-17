#ifndef GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#define GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
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
     * @param prm_model_id スプライト定義の識別名。".modelx"を追加するとモデル定義ファイル名になる。
     */
    CubeMapMorphMeshModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~CubeMapMorphMeshModel();
};

}
#endif /*GGAF_DX_CUBEMAPMORPHMESHMODEL_H_*/

