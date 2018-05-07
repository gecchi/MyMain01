#ifndef GGAFLIB_DEFAULTEFFECTMANAGER_H_
#define GGAFLIB_DEFAULTEFFECTMANAGER_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"

#define TYPE_MASSWALL_EFFECT      '@'
#define TYPE_SINGLELASER_EFFECT   '-'

namespace GgafLib {

/**
 * DefaultEffectManager .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class DefaultEffectManager : public GgafDxCore::GgafDxEffectManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DefaultEffectManager(const char* prm_manager_name);

    GgafDxCore::GgafDxEffect* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~DefaultEffectManager() {
    }
};

}
#endif /*GGAFLIB_DEFAULTEFFECTMANAGER_H_*/
