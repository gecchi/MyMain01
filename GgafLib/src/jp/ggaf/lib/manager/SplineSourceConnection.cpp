#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSourceConnection::SplineSourceConnection(char* prm_idstr, SplineSource* prm_pResource) :
    GgafResourceConnection<SplineSource> (prm_idstr, prm_pResource) {
}

void SplineSourceConnection::processReleaseResource(SplineSource* prm_pResource) {
    _TRACE_("SplineSourceConnection::processReleaseResource��"<<prm_pResource->_idstr<<"�J��(�����łԂ���ꂽ��close()�R��̉\������)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

