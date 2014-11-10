#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTextureConnection::GgafDxTextureConnection(char* prm_idstr, GgafDxTexture* prm_pResource)
    :GgafResourceConnection<GgafDxTexture>(prm_idstr, prm_pResource) {
    _TRACE3_("GgafDxTextureConnection：コンストラクタ prm_idstr="<<prm_idstr);
}

void GgafDxTextureConnection::processReleaseResource(GgafDxTexture* prm_pResource) {
    _TRACE_("GgafDxTexture="<<prm_pResource->getName()<<" を開放します。");
    GGAF_DELETE(prm_pResource);
}

