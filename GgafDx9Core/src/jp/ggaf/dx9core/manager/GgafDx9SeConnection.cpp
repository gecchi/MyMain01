#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SeConnection::GgafDx9SeConnection(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se) :
    GgafResourceConnection<GgafDx9Se> (prm_idstr, prm_pGgafDx9Se) {
}

void GgafDx9SeConnection::processReleaseResource(GgafDx9Se* prm_pResource) {
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

