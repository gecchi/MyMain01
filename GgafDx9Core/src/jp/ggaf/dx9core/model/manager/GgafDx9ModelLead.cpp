#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9ModelLead::GgafDx9ModelLead(char* prm_idstr, GgafDx9Model* prm_pModel) :
    GgafResourceLead<GgafDx9Model> (prm_idstr, prm_pModel) {
}

void GgafDx9ModelLead::processReleaseResource(GgafDx9Model* prm_pResource) {
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

