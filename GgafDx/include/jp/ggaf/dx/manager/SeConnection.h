#ifndef GGAF_DX_SECONNECTION_H_
#define GGAF_DX_SECONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/sound/Se.h"

namespace GgafDx {

/**
 * Seコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class SeConnection : public GgafCore::ResourceConnection<Se> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr サウンドエフェクト識別名
     * @param prm_pSe サウンドエフェクトオブジェクト（実値のポインタ）
     */
    SeConnection(const char* prm_idstr, Se* prm_pSe);

    void processReleaseResource(Se* prm_pResource);

    virtual ~SeConnection() {
    }
};

}
#endif /*GGAF_DX_SECONNECTION_H_*/
