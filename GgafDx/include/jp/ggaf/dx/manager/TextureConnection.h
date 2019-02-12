#ifndef GGAF_DX_TEXTURECONNECTION_H_
#define GGAF_DX_TEXTURECONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/texture/Texture.h"

namespace GgafDx {

/**
 * �e�N�X�`���̃R�l�N�V����.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class TextureConnection : public GgafCore::ResourceConnection<Texture> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �e�N�X�`�����ʖ�
     * @param prm_pResource �e�N�X�`��
     */
    TextureConnection(const char* prm_idstr, Texture* prm_pResource);

    void processReleaseResource(Texture* prm_pResource);

    virtual ~TextureConnection() {
    }
};

}
#endif /*GGAF_DX_TEXTURECONNECTION_H_*/
