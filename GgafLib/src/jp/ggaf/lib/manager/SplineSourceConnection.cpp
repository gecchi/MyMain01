#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSourceConnection::SplineSourceConnection(char* prm_idstr, SplineSource* prm_pResource) :
    GgafResourceConnection<SplineSource> (prm_idstr, prm_pResource) {
}

void SplineSourceConnection::processReleaseResource(SplineSource* prm_pResource) {
    _TRACE_("SplineSourceConnection::processReleaseResourceで"<<prm_pResource->_idstr<<"開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

