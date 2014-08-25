#ifndef GGAFDXCORE_GGAFDXSECONNECTION_H_
#define GGAFDXCORE_GGAFDXSECONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/dxcore/sound/GgafDxSe.h"

namespace GgafDxCore {

/**
 * GgafDxSeコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDxSeConnection : public GgafCore::GgafResourceConnection<GgafDxSe> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr サウンドエフェクト識別名
     * @param prm_pGgafDxSe サウンドエフェクトオブジェクト（実値のポインタ）
     */
    GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe);

    void processReleaseResource(GgafDxSe* prm_pResource);

    virtual ~GgafDxSeConnection() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXSECONNECTION_H_*/
