#ifndef GGAF_LIB_DEFAULTMODELMANAGER_H_
#define GGAF_LIB_DEFAULTMODELMANAGER_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dx/manager/ModelManager.h"

#define TYPE_SINGLELASER_MODEL  '-'

namespace GgafLib {

/**
 * DefaultModelManager .
 * @version 1.00
 * @since 2022/01/17
 * @author Masatoshi Tsuge
 */
class DefaultModelManager : public GgafDx::ModelManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DefaultModelManager(const char* prm_manager_name);

    GgafDx::Model* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~DefaultModelManager() {
    }
};

}
#endif /*GGAF_LIB_DEFAULTMODELMANAGER_H_*/
