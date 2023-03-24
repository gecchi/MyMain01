#ifndef GGAF_DX_TEXTUREMANAGER_H_
#define GGAF_DX_TEXTUREMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/texture/Texture.h"

namespace GgafDx {

/**
 * TextureConnection �Ǘ��N���X .
 * �����ς� TextureConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class TextureManager : public GgafCore::ResourceManager<Texture> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
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
