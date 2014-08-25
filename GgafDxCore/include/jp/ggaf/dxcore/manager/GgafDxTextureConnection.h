#ifndef GGAFDXCORE_GGAFDXTEXTURECONNECTION_H_
#define GGAFDXCORE_GGAFDXTEXTURECONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

namespace GgafDxCore {

/**
 * テクスチャのコネクション.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDxTextureConnection : public GgafCore::GgafResourceConnection<GgafDxTexture> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr テクスチャ識別名
     * @param prm_pResource テクスチャ
     */
    GgafDxTextureConnection(char* prm_idstr, GgafDxTexture* prm_pResource);

    void processReleaseResource(GgafDxTexture* prm_pResource);

    virtual ~GgafDxTextureConnection() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXTEXTURECONNECTION_H_*/
