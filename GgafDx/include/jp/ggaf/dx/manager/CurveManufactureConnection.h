#ifndef GGAF_DX_CURVEMANUFACTURECONNECTION_H_
#define GGAF_DX_CURVEMANUFACTURECONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * CurveManufacture資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveManufactureConnection : public GgafCore::ResourceConnection<CurveManufacture> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pResource CurveManufactureオブジェクト
     */
    CurveManufactureConnection(const char* prm_idstr, CurveManufacture* prm_pResource);

    void processReleaseResource(CurveManufacture* prm_pResource);

    virtual ~CurveManufactureConnection() {
    }
};

}
#endif /*GGAF_DX_CURVEMANUFACTURECONNECTION_H_*/
