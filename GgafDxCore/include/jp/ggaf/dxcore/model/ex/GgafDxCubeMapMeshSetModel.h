#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHSETMODEL_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHSETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"

namespace GgafDxCore {

/**
 * 環境マップメッシュセットモデル .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshSetModel : public GgafDxMeshSetModel {
    friend class GgafDxModelManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxCubeMapMeshSetModel(const char* prm_model_name);

    virtual ~GgafDxCubeMapMeshSetModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHSETMODEL_H_*/

