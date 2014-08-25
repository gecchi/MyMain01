#ifndef GGAFDXCORE_GGAFDXTEXTURECONNECTION_H_
#define GGAFDXCORE_GGAFDXTEXTURECONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

namespace GgafDxCore {

/**
 * �e�N�X�`���̃R�l�N�V����.
 * @version 1.00
 * @since 2009/01/27
 * @author Masatoshi Tsuge
 */
class GgafDxTextureConnection : public GgafCore::GgafResourceConnection<GgafDxTexture> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �e�N�X�`�����ʖ�
     * @param prm_pResource �e�N�X�`��
     */
    GgafDxTextureConnection(char* prm_idstr, GgafDxTexture* prm_pResource);

    void processReleaseResource(GgafDxTexture* prm_pResource);

    virtual ~GgafDxTextureConnection() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXTEXTURECONNECTION_H_*/
