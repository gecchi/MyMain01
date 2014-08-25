#ifndef SPLINELINECONNECTION_H_
#define SPLINELINECONNECTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/lib/util/spline/SplineLine.h"

namespace VioletVreath {

/**
 * SplineLine資源コネクション.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineLineConnection : public GgafCore::GgafResourceConnection<GgafLib::SplineLine> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSpl3D SplineLineオブジェクト
     */
    SplineLineConnection(char* prm_idstr, GgafLib::SplineLine* prm_pSpl3D);

    void processReleaseResource(GgafLib::SplineLine* prm_pResource);

    virtual ~SplineLineConnection() {
    }
};

}
#endif /*SPLINE3DCONNECTION_H_*/
