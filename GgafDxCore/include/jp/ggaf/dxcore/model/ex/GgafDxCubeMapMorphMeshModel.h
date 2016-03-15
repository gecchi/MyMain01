#ifndef GGAFDXCORE_GGAFDXCUBEMAPMORPHMESHMODEL_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

namespace GgafDxCore {

/**
 * 環境マップモーフメッシュモデル .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMorphMeshModel : public GgafDxMorphMeshModel {
    friend class GgafDxModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxCubeMapMorphMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~GgafDxCubeMapMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMORPHMESHMODEL_H_*/

