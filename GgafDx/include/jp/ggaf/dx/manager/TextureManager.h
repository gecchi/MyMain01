#ifndef GGAF_DX_TEXTUREMANAGER_H_
#define GGAF_DX_TEXTUREMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/texture/Texture.h"

namespace GgafDx {

/**
 * TextureConnection 管理クラス .
 * 生成済み TextureConnection オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class TextureManager : public GgafCore::ResourceManager<Texture> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    TextureManager(const char* prm_manager_name);

    GgafCore::ResourceConnection<Texture>* processCreateConnection(const char* prm_idstr, Texture* prm_pResource) override;

    Texture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    void releaseAll();

    void restoreAll();

    virtual ~TextureManager() {
    }
};

}
#endif /*GGAF_DX_TEXTUREMANAGER_H_*/
