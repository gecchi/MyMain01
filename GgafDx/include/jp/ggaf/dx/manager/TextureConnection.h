#ifndef GGAF_DX_TEXTURECONNECTION_H_
#define GGAF_DX_TEXTURECONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/texture/Texture.h"

namespace GgafDx {

/**
 * テクスチャのコネクション.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class TextureConnection : public GgafCore::ResourceConnection<Texture> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr テクスチャ識別名
     * @param prm_pResource テクスチャ
     */
    TextureConnection(const char* prm_idstr, Texture* prm_pResource);

    void processReleaseResource(Texture* prm_pResource);

    virtual ~TextureConnection() {
    }
};

}
#endif /*GGAF_DX_TEXTURECONNECTION_H_*/
