#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/dx/manager/SplineSourceManager.h"

namespace VioletVreath {

/**
 * VioletVreath用 Spline 管理クラス .
 * @version 1.00
 * @since 2018/08/10
 * @author Masatoshi Tsuge
 */
class SplineSourceManagerEx : public GgafDx::SplineSourceManager {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    SplineSourceManagerEx(const char* prm_manager_name);

    virtual GgafDx::SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~SplineSourceManagerEx() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
