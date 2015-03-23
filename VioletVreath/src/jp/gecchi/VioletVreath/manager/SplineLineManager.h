#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/lib/util/spline/SplineLine.h"

namespace VioletVreath {

/**
 * Spline 管理クラス .
 * 生成済み SplineLine オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineLineManager : public GgafCore::GgafResourceManager<GgafLib::SplineLine> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    SplineLineManager(const char* prm_manager_name);

    GgafLib::SplineLine* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafLib::SplineLine>* processCreateConnection(const char* prm_idstr, GgafLib::SplineLine* prm_pResource) override;


    virtual ~SplineLineManager() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
