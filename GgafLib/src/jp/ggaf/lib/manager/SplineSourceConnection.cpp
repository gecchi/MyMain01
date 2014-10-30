#include "jp/ggaf/lib/manager/SplineSourceConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSourceConnection::SplineSourceConnection(char* prm_idstr, SplineSource* prm_pResource) :
    GgafResourceConnection<SplineSource> (prm_idstr, prm_pResource) {
}

void SplineSourceConnection::processReleaseResource(SplineSource* prm_pResource) {
    _DTRACE_("SplineSourceConnection::processReleaseResource‚Å"<<prm_pResource->_idstr<<"ŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    GGAF_DELETE(prm_pResource);
}

