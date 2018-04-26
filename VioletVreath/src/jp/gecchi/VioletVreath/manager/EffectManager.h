#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/manager/DefaultEffectManager.h"

namespace VioletVreath {

/**
 * EffectManager .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class EffectManager : public GgafLib::DefaultEffectManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    EffectManager(const char* prm_manager_name);

    GgafDxCore::GgafDxEffect* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~EffectManager() {
    }
};

}
#endif /*EFFECTMANAGER_H_*/
