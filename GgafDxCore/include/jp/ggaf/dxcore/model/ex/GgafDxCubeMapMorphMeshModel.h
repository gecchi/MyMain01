#ifndef GGAFDXCUBEMAPMORPHMESHMODEL_H_
#define GGAFDXCUBEMAPMORPHMESHMODEL_H_
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
    GgafDxCubeMapMorphMeshModel(char* prm_model_name);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDxCubeMapMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCUBEMAPMORPHMESHMODEL_H_*/

