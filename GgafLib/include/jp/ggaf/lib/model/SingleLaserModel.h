#ifndef GGAF_LIB_SINGLELASERMODEL_H_
#define GGAF_LIB_SINGLELASERMODEL_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"

namespace GgafLib {

/**
 * @version 1.00
 * @since 2021/01/17
 * @author Masatoshi Tsuge
 */
class SingleLaserModel : public GgafDx::MeshSetModel {
    friend class DefaultEffectManager;
    friend class DefaultModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     */
    SingleLaserModel(const char* prm_model_id);

    virtual ~SingleLaserModel();
};

}
#endif /*GGAF_LIB_SINGLELASERMODEL_H_*/
