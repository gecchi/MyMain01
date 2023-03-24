#ifndef GGAF_DX_CURVEPROGRAMCONNECTION_H_
#define GGAF_DX_CURVEPROGRAMCONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/util/curve/CurveSource.h"

namespace GgafDx {

/**
 * CurveSource資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveSourceConnection : public GgafCore::ResourceConnection<CurveSource> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pResource CurveSourceオブジェクト
     */
    CurveSourceConnection(const char* prm_idstr, CurveSource* prm_pResource);

    void processReleaseResource(CurveSource* prm_pResource);

    virtual ~CurveSourceConnection() {
    }
};

}
#endif /*GGAF_DX_CURVEPROGRAMCONNECTION_H_*/
