#ifndef GGAF_DX_CUBEMAPMESHSETMODEL_H_
#define GGAF_DX_CUBEMAPMESHSETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"

namespace GgafDx {

/**
 * 環境マップメッシュセットモデル .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetModel : public MeshSetModel {
    friend class ModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    CubeMapMeshSetModel(const char* prm_model_id);

    virtual ~CubeMapMeshSetModel(); //デストラクタ
};

}
#endif /*GGAF_DX_CUBEMAPMESHSETMODEL_H_*/

