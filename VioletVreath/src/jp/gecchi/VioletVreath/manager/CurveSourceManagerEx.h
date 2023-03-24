#ifndef CURVELINEMANAGER_H_
#define CURVELINEMANAGER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/dx/manager/CurveSourceManager.h"

namespace VioletVreath {

/**
 * VioletVreath用 Curve 管理クラス .
 * @version 1.00
 * @since 2018/08/10
 * @author Masatoshi Tsuge
 */
class CurveSourceManagerEx : public GgafDx::CurveSourceManager {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    CurveSourceManagerEx(const char* prm_manager_name);

    virtual GgafDx::CurveSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~CurveSourceManagerEx() {
    }
};

}
#endif /*CURVELINEMANAGER_H_*/
