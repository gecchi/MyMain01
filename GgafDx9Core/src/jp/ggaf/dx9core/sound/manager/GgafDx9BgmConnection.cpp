#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9BgmConnection::GgafDx9BgmConnection(char* prm_idstr, GgafDx9Bgm* prm_pGgafDx9Bgm)
	:GgafResourceConnection<GgafDx9Bgm>(prm_idstr, prm_pGgafDx9Bgm) {
}

void GgafDx9BgmConnection::processReleaseResource(GgafDx9Bgm* prm_pResource) {
	DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

