#ifndef GGAF_DX_BGMCONNECTION_H_
#define GGAF_DX_BGMCONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/sound/Bgm.h"

namespace GgafDx {

/**
 * Bgmコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class BgmConnection : public GgafCore::ResourceConnection<Bgm> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr OGG識別名(＝ファイル名)
     * @param prm_pBgm OGG
     */
    BgmConnection(const char* prm_idstr, Bgm* prm_pBgm);

    void processReleaseResource(Bgm* prm_pResource);

    virtual ~BgmConnection() {
    }
};

}
#endif /*GGAF_DX_BGMCONNECTION_H_*/
