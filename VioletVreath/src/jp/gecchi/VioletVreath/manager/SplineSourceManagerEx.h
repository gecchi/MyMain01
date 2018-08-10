#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/manager/SplineSourceManager.h"

namespace VioletVreath {

/**
 * Spline 管理クラス .
 * 生成済み SplineLine オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineSourceManagerEx : public GgafLib::SplineSourceManager {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    SplineSourceManagerEx(const char* prm_manager_name);

    virtual GgafLib::SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~SplineSourceManagerEx() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
