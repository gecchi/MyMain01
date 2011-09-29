#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9ModelConnection::GgafDx9ModelConnection(char* prm_idstr, GgafDx9Model* prm_pModel) :
    GgafResourceConnection<GgafDx9Model> (prm_idstr, prm_pModel) {
}

void GgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) {
    prm_pResource->release(); //�d�v
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

