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
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    DefaultEffectManager(const char* prm_manager_name);

    GgafDxCore::GgafDxEffect* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~DefaultEffectManager() {
    }
};

}
#endif /*GGAFLIB_DEFAULTEFFECTMANAGER_H_*/
