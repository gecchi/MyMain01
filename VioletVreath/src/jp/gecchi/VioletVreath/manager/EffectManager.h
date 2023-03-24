#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/manager/DefaultEffectManager.h"

#define TYPE_HOSHIBOSHI_EFFECT    '*'

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
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    EffectManager(const char* prm_manager_name);

    GgafDx::Effect* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~EffectManager() {
    }
};

}
#endif /*EFFECTMANAGER_H_*/
