#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureConnection::GgafDx9TextureConnection(char* prm_idstr, GgafDx9Texture* prm_pResource)
    :GgafResourceConnection<GgafDx9Texture>(prm_idstr, prm_pResource) {
    TRACE3("GgafDx9TextureConnection：コンストラクタ prm_idstr="<<prm_idstr);
}

void GgafDx9TextureConnection::processReleaseResource(GgafDx9Texture* prm_pResource) {
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

