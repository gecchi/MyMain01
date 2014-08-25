#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHMODEL_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"

namespace GgafDxCore {

/**
 * 環境マップメッシュモデル .
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshModel : public GgafDxMeshModel {
    friend class GgafDxModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxCubeMapMeshModel(char* prm_model_name);

    virtual ~GgafDxCubeMapMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHMODEL_H_*/

