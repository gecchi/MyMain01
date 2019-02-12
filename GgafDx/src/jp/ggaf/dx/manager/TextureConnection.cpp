#include "jp/ggaf/dx/manager/TextureConnection.h"


using namespace GgafDx;

TextureConnection::TextureConnection(const char* prm_idstr, Texture* prm_pResource)
    :GgafCore::ResourceConnection<Texture>(prm_idstr, prm_pResource) {
    _TRACE3_("TextureConnection�F�R���X�g���N�^ prm_idstr="<<prm_idstr);
}

void TextureConnection::processReleaseResource(Texture* prm_pResource) {
    _TRACE_("Texture="<<prm_pResource->getName()<<" ���J�����܂��B");
    GGAF_DELETE(prm_pResource);
}

