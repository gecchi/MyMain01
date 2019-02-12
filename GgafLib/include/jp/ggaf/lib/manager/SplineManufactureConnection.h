#ifndef GGAF_LIB_SPLINEMANUFACTURECONNECTION_H_
#define GGAF_LIB_SPLINEMANUFACTURECONNECTION_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * SplineManufacture資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureConnection : public GgafCore::ResourceConnection<SplineManufacture> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pResource SplineManufactureオブジェクト
     */
    SplineManufactureConnection(const char* prm_idstr, SplineManufacture* prm_pResource);

    void processReleaseResource(SplineManufacture* prm_pResource);

    virtual ~SplineManufactureConnection() {
    }
};

}
#endif /*GGAF_LIB_SPLINEMANUFACTURECONNECTION_H_*/
