#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SeLead::GgafDx9SeLead(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se) :
    GgafResourceLead<GgafDx9Se> (prm_idstr, prm_pGgafDx9Se) {
}

void GgafDx9SeLead::processReleaseResource(GgafDx9Se* prm_pResource) {
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

