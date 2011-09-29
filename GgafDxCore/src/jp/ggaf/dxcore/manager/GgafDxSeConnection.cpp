#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeConnection::GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe) :
    GgafResourceConnection<GgafDxSe> (prm_idstr, prm_pGgafDxSe) {
}

void GgafDxSeConnection::processReleaseResource(GgafDxSe* prm_pResource) {
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

