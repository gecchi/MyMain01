#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BgmConnection::GgafDx9BgmConnection(char* prm_idstr, GgafDx9Bgm* prm_pGgafDx9Bgm) :
    GgafResourceConnection<GgafDx9Bgm> (prm_idstr, prm_pGgafDx9Bgm) {
}

void GgafDx9BgmConnection::processReleaseResource(GgafDx9Bgm* prm_pResource) {
    _TRACE_("GgafDx9BgmConnection::processReleaseResource("<<(prm_pResource->_ogg_name)<<")");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

