#ifndef GGAF_DX_MODELCONNECTION_H_
#define GGAF_DX_MODELCONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * モデル資源のコネクション.
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class ModelConnection : public GgafCore::ResourceConnection<Model> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr モデル識別名
     * @param prm_pModel リソースとなるモデル
     */
    ModelConnection(const char* prm_idstr, Model* prm_pModel);

    void processReleaseResource(Model* prm_pResource);

    virtual ~ModelConnection() {
    }
};

}
#endif /*GGAF_DX_MODELCONNECTION_H_*/
