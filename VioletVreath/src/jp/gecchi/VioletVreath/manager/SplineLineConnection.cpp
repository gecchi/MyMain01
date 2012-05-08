#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SplineLineConnection::SplineLineConnection(char* prm_idstr, GgafLib::SplineLine* prm_pResource) :
    GgafResourceConnection<GgafLib::SplineLine> (prm_idstr, prm_pResource) {
}

void SplineLineConnection::processReleaseResource(GgafLib::SplineLine* prm_pResource) {
    _TRACE_("SplineLineConnection::processReleaseResource‚Å num_basepoint_="<<prm_pResource->_num_basepoint<<"‚Ì‚ðŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
