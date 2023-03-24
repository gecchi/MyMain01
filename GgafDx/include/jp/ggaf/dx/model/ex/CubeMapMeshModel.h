#ifndef GGAF_DX_CUBEMAPMESHMODEL_H_
#define GGAF_DX_CUBEMAPMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MeshModel.h"

namespace GgafDx {

/**
 * 環境マップメッシュモデル .
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMeshModel : public MeshModel {
    friend class ModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    CubeMapMeshModel(const char* prm_model_id);

    virtual ~CubeMapMeshModel();
};

}
#endif /*GGAF_DX_CUBEMAPMESHMODEL_H_*/

