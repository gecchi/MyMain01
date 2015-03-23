#ifndef GGAFLIB_SPLINEPROGRAMCONNECTION_H_
#define GGAFLIB_SPLINEPROGRAMCONNECTION_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/lib/util/spline/SplineSource.h"

namespace GgafLib {

/**
 * SplineSource資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceConnection : public GgafCore::GgafResourceConnection<SplineSource> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pResource SplineSourceオブジェクト
     */
    SplineSourceConnection(const char* prm_idstr, SplineSource* prm_pResource);

    void processReleaseResource(SplineSource* prm_pResource);

    virtual ~SplineSourceConnection() {
    }
};

}
#endif /*GGAFLIB_SPLINEPROGRAMCONNECTION_H_*/
