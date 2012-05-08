#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxTextureConnection::GgafDxTextureConnection(char* prm_idstr, GgafDxTexture* prm_pResource)
    :GgafResourceConnection<GgafDxTexture>(prm_idstr, prm_pResource) {
    TRACE3("GgafDxTextureConnection：コンストラクタ prm_idstr="<<prm_idstr);
}

void GgafDxTextureConnection::processReleaseResource(GgafDxTexture* prm_pResource) {
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

