#ifndef GGAF_LIB_DEFAULTEFFECTMANAGER_H_
#define GGAF_LIB_DEFAULTEFFECTMANAGER_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dx/manager/EffectManager.h"

#define TYPE_MASSWALL_EFFECT      '@'
#define TYPE_SINGLELASER_EFFECT   '-'

namespace GgafLib {

/**
 * DefaultEffectManager .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class DefaultEffectManager : public GgafDx::EffectManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DefaultEffectManager(const char* prm_manager_name);

    GgafDx::Effect* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~DefaultEffectManager() {
    }
};

}
#endif /*GGAF_LIB_DEFAULTEFFECTMANAGER_H_*/
