#ifndef GGAFDXCORE_GGAFDXTEXTUREMANAGER_H_
#define GGAFDXCORE_GGAFDXTEXTUREMANAGER_H_
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

namespace GgafDxCore {

/**
 * GgafDxTextureConnection 管理クラス .
 * 生成済み GgafDxTextureConnection オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class GgafDxTextureManager : public GgafCore::GgafResourceManager<GgafDxTexture> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxTextureManager(const char* prm_manager_name);

    GgafCore::GgafResourceConnection<GgafDxTexture>* processCreateConnection(char* prm_idstr, GgafDxTexture* prm_pResource) override;

    GgafDxTexture* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    void releaseAll();

    void restoreAll();

    virtual ~GgafDxTextureManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXTEXTUREMANAGER_H_*/
