#ifndef GGAF_DX_SPLINEMANUFACTURECONNECTION_H_
#define GGAF_DX_SPLINEMANUFACTURECONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/util/spline/SplineManufacture.h"

namespace GgafDx {

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
#endif /*GGAF_DX_SPLINEMANUFACTURECONNECTION_H_*/
